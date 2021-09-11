#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Implicit cast Fixed to UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = foo;
    SUCCEED();
}

TEST_CASE("Explicit cast Fixed to UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = (Fixed::UnderlyingType)foo;
    SUCCEED();
}

TEST_CASE("Explicit cast Fixed to float") {
    Fixed foo = {};
    float bar = (float)foo;
    SUCCEED();
}

TEST_CASE("Explicit cast Fixed to double") {
    Fixed foo = {};
    double bar = (double)foo;
    SUCCEED();
}

TEST_CASE("Fixed.to_integer()") {
    Fixed foo = {};
    Fixed::UnderlyingType truncated = foo.to_integer();
    SUCCEED();
}
