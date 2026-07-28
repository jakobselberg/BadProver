#!/usr/bin/env python

import argparse
import os
import sys
import subprocess
from pathlib import Path
from enum import Enum
from dataclasses import dataclass, fields
import time
import resource
import matplotlib.pyplot as plt
from itertools import accumulate
from collections import defaultdict
from typing import Optional, TypeAlias, Literal, get_args
import textwrap
import json


DemodulationIndex = Literal[
    "none",
    "fingerprint",
    "tree"
]


@dataclass(frozen=True)
class VampireConfig:
    pass

@dataclass(frozen=True)
class SatConfig:
    demodulation_index: DemodulationIndex | None = None
    feature_vector_indexing: bool | None = None
    subsumption: bool | None = None

SolverConfig: TypeAlias = VampireConfig | SatConfig

def configToString(cfg: SolverConfig) -> str:
    match cfg:
        case VampireConfig():
            return f"solver = vampire"
        case SatConfig():
            fields = [
                f"solver = BadProver"
            ]
            if cfg.demodulation_index is not None:
                fields.append(f"demodulation_index = {cfg.demodulation_index}")
            if cfg.feature_vector_indexing is not None:
                fields.append(f"feature_vector_indexing = {cfg.feature_vector_indexing}")
            if cfg.subsumption is not None:
                fields.append(f"subsumption = {cfg.subsumption}")
            return ', '.join(fields)

class Target(Enum):
    SAT = "sat"
    UNSAT = "unsat"

class Result(Enum):
    SAT = "sat"
    UNSAT = "unsat"
    UNKNOWN = "unknown"
    CRASH = "crash"

@dataclass(frozen=True)
class RunResult:
    path: Path
    config: SolverConfig
    target: Target
    result: Result
    returnCode: int
    stdout: str
    stderr: str
    realRuntime: float
    cpuRuntime: float

def runResultToString(res: RunResult) -> str:
    fields = [f"path = {res.path}",
              f"config = {{{configToString(res.config)}}}",
              f"target = {res.target}",
              f"result = {res.result}",
              f"returnCode = {res.returnCode}",
              f"stdout = {res.stdout!r}",
              f"stderr = {res.stderr!r}",
              f"realRuntime = {res.realRuntime:.3f}",
              f"cpuRuntime = {res.cpuRuntime:.3f}"
             ]
    return ', '.join(fields)

def determineResult(returnCode: int, stdout: str) -> Result:
    if "% SZS status Unsatisfiable" in stdout:
        return Result.UNSAT

    if "% SZS status Satisfiable" in stdout:
        return Result.SAT

    if "% SZS status CounterSatisfiable" in stdout:
        return Result.SAT

    if "% SZS status Theorem" in stdout:
        return Result.UNSAT

    if "% SZS status Timeout" in stdout:
        return Result.UNKNOWN

    if returnCode == 10:
        return Result.SAT

    if returnCode == 20:
        return Result.UNSAT

    if returnCode == 0:
        return Result.UNKNOWN

    return Result.CRASH

def prettyPrintResults(results: list[RunResult], timeout: int, overallRealRuntime: float, overallCPURuntime: float) -> str:
    numResults = len(results)
    crashResults = [res for res in results if res.result == Result.CRASH]
    numCrashes = len(crashResults)
    solvedButMisclassifiedResults = [res for res in results if (res.result == Result.SAT and res.target == Target.UNSAT) or (res.result == Result.UNSAT and res.target == Target.SAT)]
    numSolvedButMisclassifiedResults = len(solvedButMisclassifiedResults)
    undecidedResults = [res for res in results if res.result == Result.UNKNOWN]
    numUndecided = len(undecidedResults)
    solvedAndCorrectlyClassifiedResults = sorted([res for res in results if (res.result == Result.SAT and res.target == Target.SAT) or (res.result == Result.UNSAT and res.target == Target.UNSAT)], key=lambda r: r.cpuRuntime, reverse=True)
    numSolvedAndCorrectlyClassified = len(solvedAndCorrectlyClassifiedResults)

    pretty = f"Number of runs: {numResults}\n"
    pretty += f"Individual solver timeout after: {timeout}s\n"
    pretty += f"Overall real runtime: {overallRealRuntime:.3f}s\n"
    pretty += f"Overall CPU runtime: {overallCPURuntime:.3f}s\n"
    pretty += f"Crashes: {numCrashes}\n"
    pretty += f"Solved but misclassified instances: {numSolvedButMisclassifiedResults}\n"
    pretty += f"Undecided instances: {numUndecided}\n"
    pretty += f"Solved and correctly classified instances: {numSolvedAndCorrectlyClassified}\n"
    if numCrashes > 0:
        pretty += f"\nCrashed instances:\n"
        for result in crashResults:
            pretty += f"{runResultToString(result)}\n"
    if numSolvedButMisclassifiedResults > 0:
        pretty += f"\nSolved but misclassified instances:\n"
        for result in solvedButMisclassifiedResults:
            pretty += f"{runResultToString(result)}\n"
    if numUndecided > 0:
        pretty += f"\nUndecided instances (out of time or other constrained resources):\n"
        for result in undecidedResults:
            pretty += f"{runResultToString(result)}\n"
    if numSolvedAndCorrectlyClassified > 0:
        pretty += f"\nSolved and correctly classified instances (sorted in descending CPU runtime order):\n"
        for result in solvedAndCorrectlyClassifiedResults:
            pretty += f"{runResultToString(result)}\n"
    return pretty

def buildCMD(cfg: SolverConfig, instancePath: Path, timeout: int, base_dir: Path) -> list[str]:
    match cfg:
        case VampireConfig():
            return [
                "vampire",
                "--mode", "portfolio",
                "--time_limit", str(timeout),
                str(instancePath),
            ]
        case SatConfig():
            cmd = [
                "./build/atp",
                "-t", str(timeout),
                "-f", str(instancePath),
                "-b", str(base_dir)
            ]
            if cfg.demodulation_index is not None:
                cmd += ["--demodulation-index", str(cfg.demodulation_index)]
            if cfg.feature_vector_indexing is not None:
                cmd += ["--feature-vector-indexing", str(cfg.feature_vector_indexing).lower()]
            if cfg.subsumption is not None:
                cmd += ["--subsumption", str(cfg.subsumption).lower()]

            return cmd

def getMarkerDict(configs: list[SolverConfig], markers: list[str]) -> dict[SolverConfig, str]:
    return {
        config: markers[i % len(markers)]
        for i, config in enumerate(configs)
    }

def parse_config_from_json_object(json_obj: object) -> SolverConfig:
    if not isinstance(json_obj, dict):
        raise ValueError("parse_config_from_json_object: input must be a JSON object")
    
    solver = json_obj.get("solver")
    if solver == "vampire":
        extra = set(json_obj.keys()) - {"solver"}
        if extra:
            raise ValueError(f"parse_config_from_json_object: unknown vampire config options: {sorted(extra)}")
        return VampireConfig()
    elif solver == "atp":
        allowed_sat_keys = {"solver"} | {f.name for f in fields(SatConfig)}
        extra = set(json_obj.keys()) - allowed_sat_keys
        if extra:
            raise ValueError(f"parse_config_from_json_object: unknown sat config options: {sorted(extra)}")

        demodulation_index = json_obj.get("demodulation_index")
        if demodulation_index is not None and demodulation_index not in get_args(DemodulationIndex):
            raise ValueError(f"demodulation_index must be one of {get_args(DemodulationIndex)}")

        feature_vector_indexing = json_obj.get("feature_vector_indexing")
        if feature_vector_indexing is not None and type(feature_vector_indexing) is not bool:
            raise ValueError("feature_vector_indexing needs to be a boolean")

        subsumption = json_obj.get("subsumption")
        if subsumption is not None and type(subsumption) is not bool:
            raise ValueError("subsumption needs to be a boolean")

        return SatConfig(
            demodulation_index = demodulation_index,
            feature_vector_indexing = feature_vector_indexing,
            subsumption = subsumption,)
    else:
        raise ValueError(f"parse_config_from_json_object: unkown solver kind: {solver}")

def parse_config_from_json_string(json_str: str) -> SolverConfig:
    try:
        raw = json.loads(json_str)
    except json.JSONDecodeError as e:
        raise argparse.ArgumentTypeError(f"invalid JSON in --config: {e}")

    try:
        return parse_config_from_json_object(raw)
    except ValueError as e:
        raise argparse.ArgumentTypeError(str(e))

def parse_configs_from_json_file(json_path: Path) -> list[SolverConfig]:
    try:
        raw = json.loads(json_path.read_text())
    except json.JSONDecodeError as e:
        raise ValueError(f"invalid JSON in {json_path}: {e}")

    if not isinstance(raw, list):
        raise ValueError("--config-file must contain a JSON list")

    return [parse_config_from_json_object(entry) for entry in raw]

Jobs = Literal[
    "CASC17",
    "custom",
    "easy100",
    "NNE",
    "HEQ",
    "HNE",
    "NEQ",
    "PEQ"
]

def main():
    # Configure program arguments
    parser = argparse.ArgumentParser(
        prog="benchmark.py",
        formatter_class=argparse.RawTextHelpFormatter,
        description="Creates cactus plot SAT solvers and outputs diagnostic information. See --help for usage instructions."
    )
    parser.add_argument("-t", "--timeout", help = "Wall-clock timeout in seconds to use for individual solver invocations - defaults to 60 seconds per invocation.", type = int, default = 60)
    parser.add_argument("--config", action = "append", default = [], help=(
        "JSON object describing one solver configuration. Repeatable.\n"
        "Required key:\n"
        "  solver\n"
        "Available options for solver='vampire':\n"
        "  solver\n"
        "Available options for solver='atp':\n"
        f"  solver ('atp')\n"
        f"  demodulation_index (one of {get_args(DemodulationIndex)})\n"
        f"  feature_vector_indexing (boolean)\n"
        f"  subsumption (boolean)\n")
    )
    parser.add_argument("--config-file", type = Path, default = None, help = "JSON file containing a list of solver configurations.")
    parser.add_argument("--output-dir", type = Path, default = Path("outputs"), help = "Directory where result.txt and result.pdf should be written.")
    parser.add_argument("-b","--base-dir", type = Path, default = Path("inputs/TPTP-v9.2.1"), help = "Set the base directory for resolving includes in TPTP files. (has to "
                          "include Axiom folder) Default: inputs")
    parser.add_argument("-j","--jobs", type = str, choices = get_args(Jobs), default = "CASC17", help = f"Which benchmark jobs to run. Default: CASC17")
    args = parser.parse_args()

    if args.config == [] and args.config_file is None:
        configs = [SatConfig()]
    else:
        configs = []
    try:
        configs.extend(parse_config_from_json_string(json) for json in args.config)
        if args.config_file is not None:
            configs.extend(parse_configs_from_json_file(args.config_file))
    except (argparse.ArgumentTypeError, ValueError) as e:
        parser.error(str(e))

    # de-duplicate the configs while keeping order same
    configs = list(dict.fromkeys(configs))

    timeout = args.timeout
    base_dir = args.base_dir

    # Prepend build step
    subprocess.run(["./build.sh"], capture_output = False, stdout=subprocess.DEVNULL)

    base = Path(".")
   
    HEQInstancesPath = base / "inputs/CASC17/HEQ"
    HEQInstancePaths = [p.relative_to(base) for p in HEQInstancesPath.iterdir() if p.is_file()]

    HNEInstancesPath = base / "inputs/CASC17/HNE"
    HNEInstancePaths = [p.relative_to(base) for p in HNEInstancesPath.iterdir() if p.is_file()]

    NEQInstancesPath = base / "inputs/CASC17/NEQ"
    NEQInstancePaths = [p.relative_to(base) for p in NEQInstancesPath.iterdir() if p.is_file()]

    NNEInstancesPath = base / "inputs/CASC17/NNE"
    NNEInstancePaths = [p.relative_to(base) for p in NNEInstancesPath.iterdir() if p.is_file()]

    PEQInstancesPath = base / "inputs/CASC17/PEQ"
    PEQInstancePaths = [p.relative_to(base) for p in PEQInstancesPath.iterdir() if p.is_file()]

    customInstancesPath = base / "inputs/custom"
    customInstancePaths = [p.relative_to(base) for p in customInstancesPath.iterdir() if p.is_file()]

    easy100InstancesPath = base / "inputs/easy100"
    easy100InstancePaths = [p.relative_to(base) for p in easy100InstancesPath.iterdir() if p.is_file()]

    results = []

    if args.jobs == "CASC17":
        jobs = [(HEQInstancePaths, Target.UNSAT), (HNEInstancePaths, Target.UNSAT), (NEQInstancePaths, Target.UNSAT), (NNEInstancePaths, Target.UNSAT), (PEQInstancePaths, Target.UNSAT)]
    elif args.jobs == "custom":
        jobs = [(customInstancePaths, Target.UNSAT)]
    elif args.jobs == "easy100":
        jobs = [(easy100InstancePaths, Target.UNSAT)]
    elif args.jobs == "NNE":
        jobs = [(NNEInstancePaths, Target.UNSAT)]
    elif args.jobs == "HEQ":
        jobs = [(HEQInstancePaths, Target.UNSAT)]
    elif args.jobs == "HNE":
        jobs = [(HNEInstancePaths, Target.UNSAT)]
    elif args.jobs == "NEQ":
        jobs = [(NEQInstancePaths, Target.UNSAT)]  
    elif args.jobs == "PEQ":
        jobs = [(PEQInstancePaths, Target.UNSAT)]

    overallTimeBefore = time.perf_counter()
    overallResourcesBefore = resource.getrusage(resource.RUSAGE_CHILDREN)
    # collect result data
    for config in configs:
        print(f"Running benchmark for config: {configToString(config)}")
        for (instancePaths, target) in jobs:
            for instancePath in instancePaths:
                start = time.perf_counter()
                resourcesBefore = resource.getrusage(resource.RUSAGE_CHILDREN)
                cmd = buildCMD(config, instancePath, timeout, base_dir)
                env = None
                # Only needed for Vampire.            
                if isinstance(config, VampireConfig):
                    env = os.environ.copy()
                    env["TPTP"] = str(base_dir)

                result = subprocess.run(cmd, capture_output = True, text = True,env =env)
                resourcesAfter = resource.getrusage(resource.RUSAGE_CHILDREN)
                cpuRuntime = (resourcesAfter.ru_utime - resourcesBefore.ru_utime) + (resourcesAfter.ru_stime - resourcesBefore.ru_stime)
                realRuntime = time.perf_counter() - start
                results.append(
                    RunResult(
                        config = config,
                        path = instancePath,
                        returnCode = result.returncode,
                        stdout = result.stdout,
                        stderr = result.stderr,
                        realRuntime = realRuntime,
                        cpuRuntime = cpuRuntime,
                        target = target,
                        result = determineResult(result.returncode, result.stdout)))
    overallResourcesAfter = resource.getrusage(resource.RUSAGE_CHILDREN)
    overallCPURuntime = (overallResourcesAfter.ru_utime - overallResourcesBefore.ru_utime) + (overallResourcesAfter.ru_stime - overallResourcesBefore.ru_stime)
    overallRealRuntime = time.perf_counter() - overallTimeBefore
            
    # save results to file
    outputDir = args.output_dir
    outputDir.mkdir(parents = True, exist_ok = True)
    resultLogPath = outputDir / "result.txt"
    resultLogPath.write_text(prettyPrintResults(results, timeout, overallRealRuntime, overallCPURuntime))

    # filter out crashed, timed out or misclassified results and group entries into separate lists for each solver choice
    solvedResults = [res for res in results if (res.result == Result.SAT and res.target == Target.SAT) or (res.result == Result.UNSAT and res.target == Target.UNSAT)]
    solvedWithConfig: dict[SolverConfig, list[RunResult]] = defaultdict(list)
    for res in solvedResults:
        solvedWithConfig[res.config].append(res)

    markers = ["x", "o", "s", "^", "D", "v", "P", "X", "<", ">", "*"]
    markerDict = getMarkerDict(configs, markers)

    default_width, default_height = plt.rcParams["figure.figsize"]

    legend_width = 3.0
    fig = plt.figure(figsize=(default_width + legend_width, default_height))
    gs = fig.add_gridspec(1, 2, width_ratios = [legend_width, default_width])
    legend_ax = fig.add_subplot(gs[0])
    ax = fig.add_subplot(gs[1])
    legend_ax.axis("off")

    # generate cactus plot for each solver

    plot_entries = []
    for (config, rs) in solvedWithConfig.items():
        cpuTimes = sorted(result.cpuRuntime for result in rs)
        xs = range(1, len(cpuTimes) + 1)
        line, = ax.plot(xs,
                cpuTimes,
                linewidth = 1,
                linestyle='-',
                marker=markerDict[config],
                markerfacecolor='none',
                markersize=3.5,
                markeredgewidth=0.8)
        plot_entries.append((line, textwrap.fill(configToString(config), width = 35)))

    ax.set_xlabel("number of solved instances")
    ax.set_ylabel("cumulative CPU time (s)")
    ax.grid(True, alpha=0.3)

    handles = [line for line, _ in plot_entries]
    labels = [text for _, text in plot_entries]
    legend = legend_ax.legend(
        handles,
        labels,
        loc="upper center",
        frameon=True,
        edgecolor="black",
        facecolor="white",
        fontsize=10,
        ncol=1,
    )

    cactusPlotPath = outputDir / "result.pdf"
    fig.tight_layout()
    fig.canvas.draw()
    renderer = fig.canvas.get_renderer()
    legend_bbox = legend.get_window_extent(renderer=renderer)
    legend_height_in = legend_bbox.height / fig.dpi
    fig_width, fig_height = fig.get_size_inches()
    if legend_height_in > fig_height:
        fig.set_size_inches(fig_width, legend_height_in + 0.5)
        fig.tight_layout()
    fig.savefig(cactusPlotPath, dpi=300)
    plt.close(fig)

# main entrypoint
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("Keyboard interrupt...")
        sys.exit(1)
