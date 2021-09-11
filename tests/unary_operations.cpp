#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Fixed prefix increment") {
    Fixed foo;
    Fixed bar = ++foo;
    SUCCEED();
}

TEST_CASE("Fixed postfix increment") {
    Fixed foo;
    Fixed bar = foo++;
    SUCCEED();
}

TEST_CASE("Fixed prefix decrement") {
    Fixed foo;
    Fixed bar = --foo;
    SUCCEED();
}

TEST_CASE("Fixed postfix decrement") {
    Fixed foo;
    Fixed bar = foo--;
    SUCCEED();
}

TEST_CASE("Fixed unary minus") {
    Fixed foo;
    Fixed bar = -foo;
    SUCCEED();
}
