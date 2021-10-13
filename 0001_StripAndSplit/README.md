# What is this?

*A* C++ implementation of Python's `strip()` and `split()` functions.

### Pre-requisites

- GoogleTest
- CMake

### How to build?

Like a standard CMake project:

    cmake -G Ninja <path_to_0001_StripAndSplit>
    ninja

**NOTE:** There is nothing that ties this code to Ninja. Make can be use here as well.

### How to run?

Run `./test` from the same directory in which the build commands were run.