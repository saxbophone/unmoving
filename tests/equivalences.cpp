#include <limits>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Can cast from and back to raw fixed point") {
    Underlying i = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed foo = i;
    Underlying bar = foo;
    REQUIRE(bar == i);
}

TEST_CASE("Can cast from and back to float") {
    float i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594f,
                524287.9997558594f
            )
        )
    );
    Fixed var = i;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((float)var == Approx(i).margin(1.0 / 4096));
}

TEST_CASE("Can cast from and back to double") {
    double i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594f,
                524287.9997558594f
            )
        )
    );
    Fixed var = i;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)var == Approx(i).margin(1.0 / 4096));
}

TEST_CASE("Can cast from and back to integer") {
    Underlying i = GENERATE(take(100, random(-524288, 524287)));
    Fixed var = Fixed::from_integer(i);
    REQUIRE(var.to_integer() == i);
}
