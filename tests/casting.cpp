#include <limits>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Implicit cast Fixed to UnderlyingType") {
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
    Underlying bar = foo;
    REQUIRE(bar == i);
}

TEST_CASE("Explicit cast Fixed to UnderlyingType") {
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
    Underlying bar = (Underlying)foo;
    REQUIRE(bar == i);
}

TEST_CASE("Explicit cast Fixed to float") {
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
    float bar = (float)foo;
    REQUIRE(bar == (float)i / 4096);
}

TEST_CASE("Explicit cast Fixed to double") {
    Fixed foo = {};
    double bar = (double)foo;
    SUCCEED();
}

TEST_CASE("Fixed.to_integer()") {
    Fixed foo = {};
    Underlying truncated = foo.to_integer();
    SUCCEED();
}
