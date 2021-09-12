#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed prefix increment") {
    Fixed foo = {};
    Fixed bar = ++foo;
    SUCCEED();
}

TEST_CASE("Fixed postfix increment") {
    Fixed foo = {};
    Fixed bar = foo++;
    SUCCEED();
}

TEST_CASE("Fixed prefix decrement") {
    Fixed foo = {};
    Fixed bar = --foo;
    SUCCEED();
}

TEST_CASE("Fixed postfix decrement") {
    Fixed foo = {};
    Fixed bar = foo--;
    SUCCEED();
}

TEST_CASE("Fixed unary minus") {
    Underlying i = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed foo(i);
    Fixed bar = -foo;
    // this should be an exact conversion, so comparing for exact equality is fine
    REQUIRE((float)bar == -((float)foo));
}
