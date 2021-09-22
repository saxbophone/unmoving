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

## Usage

```cpp
#include <cassert>
#include <iostream>

#include <unmoving/PSXFixed.hpp>


using namespace unmoving;

void print(const PSXFixed& fixed);

int main() {
    PSXFixed d; // default-initialised
    print(d);   // -> "0.000000"
    // uses custom user-defined-literal, equivalent to the previous statement
    PSXFixed z = 0.0_fx, v = 0_fx;
    print(z); // -> "0.000000"
    print(v); // -> "0.000000"

    // contrasting use of custom literals vs built-in literals:
    PSXFixed c = 123456_fx;
    print(c); // -> "123456.000000"
    PSXFixed b = 123456; // -> equivalent to reinterpret_cast<>()
                         //    i.e. takes 123456 to be the raw integer
                         //    representation of a fixed-point value
    print(b);            // -> "30.140625"
    // NOTE: c and b have different values!
    assert(b != c);
    // use PSXFixed::from_integer() to value-convert from integer
    PSXFixed i = PSXFixed::from_integer(123456); // -> 123456.0_fx
    print(i); // -> "123456.000000"
    assert(i == c);

    // arithmetic expressions using fixed-point type
    // note that as all methods are constexpr, constants can be folded at compile-time
    static constexpr PSXFixed compile_time_expression = (3.14159265_fx / 3) + 0.02_fx * 45;
    /*
     * An optimising compiler can put the variable declared above in rodata as a constant:
     *
     * Disassembly of section .rodata:
     * 
     * ...[truncated]...
     * 
     * 0000000000400ca4 <main::compile_time_expression>:
     *   400ca4:       2b 1f                   sub    (%rdi),%ebx
     *         ...
     *
     * NOTE here that 0x1F2B as seen in the assembly is the decimal value 7979
     * which is the raw fixed-point value for 1.947998
     */
    print(compile_time_expression); // -> "1.947998"
    // fixed-point instances cast to int implicitly, yielding their raw value:
    std::cout << compile_time_expression << std::endl; // -> "7979"
}

void print(const PSXFixed& fixed) {
    char buffer[15] = {};
    if (fixed.to_c_str(buffer, sizeof(buffer))) {
        std::cout << buffer << std::endl;
    }
}
```

Further reading: [API reference](https://saxbophone.com/unmoving/)

## Test suite

Unmoving has a thorough unit test suite, however this cannot be built for the PlayStation due the extensive C++ library dependencies of the test suite itself. This test suite is run in CI for Linux, macOS and Windows. You can run the tests yourself by building the project in Debug mode or with `ENABLE_TESTS=ON` with CMake:

```sh
git checkout git@github.com:saxbophone/unmoving.git
cd unmoving/build
# debug mode is the default
cmake ..
# OR alternatively (builds tests but in optimised Release mode)
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=ON

# compile tests, using 5 threads
cmake --build . -j 5

# runs the tests with 5 threads
ctest -j 5
```
