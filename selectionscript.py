#!/usr/bin/env python

from pathlib import Path
import shutil

# Change this to your TPTP installation
TPTP = Path("inputs/TPTP-v9.2.1/Problems/")

OUT = Path("inputs/CASC17")
OUT.mkdir(exist_ok=True)

problems = {
    "HEQ": [
        "CID003-1", "LCL341-3", "LAT002-1", "ANA003-1", "CAT002-4",
        "LCL269-3", "LAT005-6", "LCL302-3", "LCL306-3", "LCL109-4",
        "COL044-2", "LCL193-3", "HEN011-1", "COL006-2", "COL044-4",
    ],

    "HNE": [
        "LCL122-1", "LCL394-1", "LCL123-1", "PLA011-2", "PLA012-1",
        "LCL368-1", "LCL020-1", "PLA014-1", "PLA019-1", "PLA004-2",
        "SYN312-1", "SYN311-1", "PLA009-2", "PLA005-2", "LCL129-1",
    ],

    "NEQ": [
        "SET454-6", "GEO028-2", "GEO066-2", "GEO009-1", "GEO012-1",
        "SET347-6", "SET497-6", "GEO010-2", "NUM049-1", "SET230-6",
        "GEO060-2", "CAT005-3", "GEO002-2", "MSC007-2.005", "GEO001-1",
    ],

    "NNE": [
        "SET014-2", "ANA002-4", "SYN067-1", "SET015-2", "SYN067-3",
        "SET013-2", "SET015-1", "SET012-1", "SET013-1", "SYN067-2",
        "COM003-1", "ANA002-3", "CIV006-1", "ANA002-1", "ANA002-2",
    ],

    "PEQ": [
        "COL078-1", "GRP055-1", "CAT003-2", "COL077-1", "GRP052-1",
        "COL075-1", "BOO020-1", "GRP057-1", "GRP072-1", "GRP053-1",
        "COL080-1", "GRP086-1", "LAT015-1", "GRP051-1", "ALG004-1",
    ],
}

missing = []

for category, plist in problems.items():
    outdir = OUT / category
    outdir.mkdir(exist_ok=True)

    for problem in plist:
        domain = problem[:3]
        src = TPTP / domain / f"{problem}.p"

        if src.exists():
            shutil.copy2(src, outdir / src.name)
            print(f"Copied {problem}")
        else:
            print(f"Missing {problem}")
            missing.append(problem)

print("\nDone.")

if missing:
    print("\nMissing problems:")
    for p in missing:
        print(" ", p)