# To DO

+ Term Types Predicate Vs Variable Type
+ maintaine unique Clause Id when adding clauses
+ hookup main to prover logic
+ find larger set of rellevant Problem files
+ modify parser to load axioms from additional files

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