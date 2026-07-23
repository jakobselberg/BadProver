#!/usr/bin/env python

import argparse
import re
import shutil
from collections import defaultdict
from pathlib import Path


STATUS_RE = re.compile(r"^\s*%\s*Status\s*:\s*(.+)$", re.MULTILINE)
RATING_RE = re.compile(r"^\s*%\s*Rating\s*:\s*([0-9.]+)", re.MULTILINE)


def read(path: Path) -> str:
    return path.read_text(errors="ignore")


def is_untyped_cnf(text: str) -> bool:
    if "cnf(" not in text:
        return False

    if "fof(" in text:
        return False

    if "tff(" in text:
        return False

    if "thf(" in text:
        return False

    return True


def status(text: str):
    m = STATUS_RE.search(text)
    return m.group(1).strip() if m else None


def rating(text: str):
    m = RATING_RE.search(text)
    if m:
        return float(m.group(1))
    return None


def domain(path: Path):
    parts = path.parts
    if "Problems" in parts:
        i = parts.index("Problems")
        if i + 1 < len(parts):
            return parts[i + 1]
    return "OTHER"


def collect(root: Path):
    groups = defaultdict(list)

    for path in sorted(root.rglob("*.p")):
        text = read(path)

        if not is_untyped_cnf(text):
            continue

        s = status(text)
        if s is None or "Unsatisfiable" not in s:
            continue

        r = rating(text)
        if r is None or r >= 0.5:
            continue

        groups[domain(path)].append(path)

    return groups


def choose(groups, n=100):
    domains = sorted(groups.keys())

    result = []

    while len(result) < n:
        progress = False

        for d in domains:
            if groups[d]:
                result.append(groups[d].pop(0))
                progress = True

                if len(result) == n:
                    break

        if not progress:
            break

    return result


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument("--tptp", default=Path("inputs/TPTP-v9.2.1/Problems/"),type=Path)
    parser.add_argument("--output",  default=Path("inputs/easy100"),type=Path)
    parser.add_argument("-n", "--number", default=100, type=int)

    args = parser.parse_args()

    args.output.mkdir(parents=True, exist_ok=True)

    groups = collect(args.tptp)

    print("Problems per domain:")
    for d in sorted(groups):
        print(f"{d:6} {len(groups[d])}")

    selected = choose(groups, args.number)

    print(f"\nSelected {len(selected)} problems\n")

    for p in selected:
        shutil.copy2(p, args.output / p.name)
        print(p)


if __name__ == "__main__":
    main()