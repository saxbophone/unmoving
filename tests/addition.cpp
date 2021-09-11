#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Fixed += Fixed") {
    Fixed foo;
    Fixed bar;
    foo += bar;
    SUCCEED();
}

TEST_CASE("Fixed + Fixed") {
    Fixed foo;
    Fixed bar;
    Fixed baz = foo + bar;
    SUCCEED();
}
