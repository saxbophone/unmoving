#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Default constructor can be called") {
    Fixed foo;
    SUCCEED();
}

TEST_CASE("Implicit conversion from fixed-point integer") {
    Fixed var = 32;
    SUCCEED();
}

TEST_CASE("Explicit conversion from fixed-point integer") {
    Fixed var(32);
    SUCCEED();
}

TEST_CASE("Implicit conversion from float") {
    Fixed var = 32.0f;
    SUCCEED();
}

TEST_CASE("Implicit conversion from double") {
    Fixed var = 32.0;
    SUCCEED();
}

TEST_CASE("Explicit conversion from float") {
    Fixed var(32.0f);
    SUCCEED();
}

TEST_CASE("Explicit conversion from double") {
    Fixed var(32.0);
    SUCCEED();
}

TEST_CASE("Creation from integer value") {
    Fixed var = Fixed::from_integer(32);
    SUCCEED();
}
