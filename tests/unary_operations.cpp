#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed prefix increment") {
    float i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594f,
                // max is reduced by 1 to prevent overflow
                524286.9997558594f
            )
        )
    );
    Fixed foo(i);
    Fixed bar = ++foo;
    REQUIRE((float)bar == ++i);
    REQUIRE((float)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed postfix increment") {
    float i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594f,
                // max is reduced by 1 to prevent overflow
                524286.9997558594f
            )
        )
    );
    Fixed foo(i);
    Fixed bar = foo++;
    REQUIRE((float)bar == i++);
    REQUIRE((float)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed prefix decrement") {
    float i = GENERATE(
        take(
            100,
            random(
                // min is increased by 1 to prevent underflow
                -524287.9997558594f,
                524287.9997558594f
            )
        )
    );
    Fixed foo(i);
    Fixed bar = --foo;
    REQUIRE((float)bar == --i);
    REQUIRE((float)foo == i); // relies upon i value changed in previous check
}

TEST_CASE("Fixed postfix decrement") {
    float i = GENERATE(
        take(
            100,
            random(
                // min is increased by 1 to prevent underflow
                -524287.9997558594f,
                524287.9997558594f
            )
        )
    );
    Fixed foo(i);
    Fixed bar = foo--;
    REQUIRE((float)bar == i--);
    REQUIRE((float)foo == i); // relies upon i value changed in previous check
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
