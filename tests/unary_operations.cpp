#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed prefix increment") {
    double i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594,
                // max is reduced by 1 to prevent overflow
                524286.9997558594
            )
        )
    );
    Fixed foo(i);
    Fixed bar = ++foo;
    REQUIRE((double)bar == ++i);
    REQUIRE((double)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed postfix increment") {
    double i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594,
                // max is reduced by 1 to prevent overflow
                524286.9997558594
            )
        )
    );
    Fixed foo(i);
    Fixed bar = foo++;
    REQUIRE((double)bar == i++);
    REQUIRE((double)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed prefix decrement") {
    double i = GENERATE(
        take(
            100,
            random(
                // min is increased by 1 to prevent underflow
                -524287.9997558594,
                524287.9997558594
            )
        )
    );
    Fixed foo(i);
    Fixed bar = --foo;
    REQUIRE((double)bar == --i);
    REQUIRE((double)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed postfix decrement") {
    double i = GENERATE(
        take(
            100,
            random(
                // min is increased by 1 to prevent underflow
                -524287.9997558594,
                524287.9997558594
            )
        )
    );
    Fixed foo(i);
    Fixed bar = foo--;
    REQUIRE((double)bar == i--);
    REQUIRE((double)foo == i); // relies upon i value changed in previous check
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
    REQUIRE((double)bar == -((double)foo));
}
