#include <limits>

#include <cmath>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Default constructor can be called") {
    Fixed foo = {};
    REQUIRE((Underlying)foo == 0);
}

TEST_CASE("Implicit conversion from fixed-point integer") {
    Underlying i = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed var = i;
    REQUIRE((Underlying)var == i);
}

TEST_CASE("Explicit conversion from fixed-point integer") {
    Underlying i = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed var(i);
    REQUIRE((Underlying)var == i);
}

TEST_CASE("Implicit conversion from float") {
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
    REQUIRE((Underlying)var == (Underlying)round(i * 4096));
}

TEST_CASE("Implicit conversion from double") {
    double i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    Fixed var = i;
    REQUIRE((Underlying)var == (Underlying)round(i * 4096));
}

TEST_CASE("Explicit conversion from float") {
    float i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594f,
                524287.9997558594f
            )
        )
    );
    Fixed var(i);
    REQUIRE((Underlying)var == (Underlying)round(i * 4096));
}

TEST_CASE("Explicit conversion from double") {
    double i = GENERATE(
        take(
            100,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    Fixed var(i);
    REQUIRE((Underlying)var == (Underlying)round(i * 4096));
}

TEST_CASE("Creation from integer value") {
    Underlying i = GENERATE(take(100, random(-524288, 524287)));
    Fixed var = Fixed::from_integer(i);
    REQUIRE((Underlying)var == i * 4096);
}

// Now for some more advanced stuff

TEST_CASE("Assignment operator can be called") {
    Fixed foo, bar;
    foo = bar;
    REQUIRE((Underlying)foo == (Underlying)bar);
}

TEST_CASE("Copy constructor can be called") {
    Fixed foo = {};
    Fixed bar = foo;
    REQUIRE((Underlying)foo == (Underlying)bar);
}

TEST_CASE("Explicit copy constructor can be called") {
    Fixed foo = {};
    Fixed bar(foo);
    REQUIRE((Underlying)foo == (Underlying)bar);
}
