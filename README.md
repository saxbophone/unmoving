# Unmoving

Unmoving is a C++ header-only library providing more convenient
fixed-point arithmetic for the Sony PlayStation ("PS1"), in the form of a
C++ class that wraps the native integer type used by the console standard
library for performing fixed-point calculations. This class is intended to
remove much of the more tedious aspects of the boilerplate code required to
handle numbers in this way. The author hopes that it is useful.

## Getting it

Unmoving is written in C++20 and can target the PlayStation or most desktop OSes.
In all cases, you will need a recent C++ compiler in order to build C++20 code.

_TODO: Instructions go here for using Unmoving with PSn00bSDK_

_TODO: Instructions go here for retrieving the library with CMake or just grabbing the header_

### Some general notes for running on the PlayStation

- Although written in C++20, Unmoving does not rely upon the C++ standard library or STL. The only dependencies it has are satisfied by the minimal C standard library that comes with PSn00bSDK.
- Unmoving has been tested and confirmed to run on PCSXR, the PlayStation emulator. There is no reason why it wouldn't also run on real PlayStation hardware, but this has not yet been tested.
- Unmoving hasn't been profiled for performance on the PlayStation. Vague observations from testing with PCSXR suggest its efficiency is reasonable, maybe even decent, but this area needs further investigation —particularly for the multiplication and division routines.

## Test suite

Unmoving has a thorough unit test suite, however this cannot be built for the PlayStation due the extensive C++ library dependencies of the test suite itself. This test suite is run in CI for Linux, macOS and Windows. You can run the tests yourself by building the project in Debug mode or with `ENABLE_TESTS=ON` with CMake:

```sh
git checkout git@github.com:saxbophone/unmoving.git
cd unmoving/build
# debug mode is the default
cmake ..
# OR alternatively (builds tests but in optimised Release mode)
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=ON
# runs the tests with 5 threads
ctest -j 5
```

- [API reference](@ref com::saxbophone::unmoving)
