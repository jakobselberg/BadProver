# ToDO

+ make prove files
+ bug hunting
+ when seting time lower like t = 10 some instances in CASC17 crash with segmentation fault
+ add config in benchmarking via commandline
+ some instances crash with fingerprint

# BadProver

superposition prover
requires c++ version 20+


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

to configure and build run:
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

As an example this call compares the performance of BadProver and Vampire on the easy100 Problem set
```
./benchmark.py -t 60 -j easy100 --config-file inputs/PlotConfigs/BadProver-vs-Vampir
e.json 
```

# AI Usage Disclaimer
AI was used to generate some Tests and was used in the cretion of the Pythonscripts easySelection.py and selectionscript.py.
Furthermore AI Tools were used for Debugging Purposes