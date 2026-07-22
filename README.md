# ToDO

+ find larger set of rellevant Problem files
+ make prove files
+ simplification rules
+ finish benchmarking script
+ Vapire integration for comparrison???
+ bug hunting


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

# How to run
to run the prover run:
```
./build/atp
```

# How to test
to run all tests run:
```
ctest --test-dir build
```

to run one test seperatly run:
```
./build/TEST_NAME
```