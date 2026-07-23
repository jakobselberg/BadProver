# ToDO

+ find larger set of rellevant Problem files
+ make prove files
+ simplification rules
+ finish benchmarking script
+ Vapire integration for comparrison???
+ bug hunting
+ clean up Parser by removing unused old function versions
+ when seting time lower like t = 10 some instances in CASC17 crash with segmentation fault

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
 