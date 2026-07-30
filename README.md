# ToDO

+ make prove files
+ bug hunting
+ some instances crash with fingerprint

# BadProver,

is a simple superposition automated theorem prover.
The core proving concepts are based on the material coverd in the praktikum automatd theorem provers SOSE 2026 at lmu munich.
The prover takes tptp problem files as inputs and outputs UNSATISFIABLE, SATURATED or UNKNOWN in case of a timeout.
The prover is designed to work on untyped problems in cnf.
When using the prover, even on some of the test/benchmark problems included in this repository, at least the axioms folder of the TPTP library needs to be provided. By default the prover assumes there is a full TPTP-v9.2.1 installation in the inputs folder, but the location of axioms folder can be adjusted via the command-line.

# System requirements 
requires c++ version 20+

To run `atp`, you need the following software installed and configured:
- `clang` C/C++ compiler
- `clang-tools` C/C++ compiler tools
- `cmake` build system
- `ninja` build system
- `cxxopts` C++ library

Evaluating the builtin tests additionally requires:
- `doctest` C++ library

Using the benchmark tool to generate cactus plots additionally requires:
- `python` interpreter
- `matplotlib` python library

The benchmark tool supports comparing the `BadProver` automated theorem prover with `vampire`. This additionally requires:
- `vampire`

If you want the setup to be as simple and reproducible as possible, install the package manager Nix ([https://nixos.org/download/](https://nixos.org/download/)), navigate the shell into the repo directory and issue `nix-shell` - this will generate a shell environment with all the dependencies exactly as listed above, so it is as close as possible to 'guaranteed working'.
Be warned that on the first invocation of `nix-shell`, the process can take a while (<= 30 minutes) to finish.

# How to build
to configure build process run:
```
cmake -B build -G Ninja
```

to build run: 
```
cmake --build build
```

to configure and build run:
```
./build.sh
```

to rebuild the build folder and buid run:
```
./build.sh --clean
```

# How to run
to run the prover run:
```
./build/atp
```

see
```
./build/atp -h
```
for detailed description of all options

# How to test
to run all tests run:
```
ctest --test-dir build
```

to run one test seperatly run:
```
./build/TEST_NAME
```

# How to benchmark
to run the benchmark tool an generate cactus plots run:
```
./benchmark.py
```
By default the results will be saved to the `outputs` folder

see
```
./benchmark.py -h
```
for a detailed description of all options

As an example this call compares the performance of BadProver and Vampire on the easy100 Problem set with 60 seconds per problem.
```
./benchmark.py -t 60 -j easy100 --config-file inputs/PlotConfigs/BadProver-vs-Vampir
e.json 
```

The results of our own analysis are saved in outputs/Plots. They were created using the solver configurations stored as .json files in inputs/PlotConfigs.
The Problem-sets our analysis is based on were created by using the selection scripts easySelection.py, easySelectionSAT.py and selectionscript.py.
Each of them just copies problems out of the TPTP problem set.

# AI Usage Disclaimer
AI was used to generate some of the tests and was used in the creation of the Python-scripts easySelection.py, easySelectionSAT.py and selectionscript.py.
Furthermore AI tools like chat-gpt were used to aid in the debugging process.