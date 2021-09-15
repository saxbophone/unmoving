#include <limits>

#include <cmath>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Constructors") {
    SECTION("Default constructor can be called") {
        Fixed foo = {};
        REQUIRE((Underlying)foo == 0);
    }

    SECTION("Conversion from fixed-point integer") {
        Underlying i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        );

        SECTION("Implicit conversion from fixed-point integer") {
            Fixed var = i;
            REQUIRE((Underlying)var == i);
        }

        SECTION("Explicit conversion from fixed-point integer") {
            Fixed var(i);
            REQUIRE((Underlying)var == i);
        }

        SECTION("Special advanced constructors") {
            // Now for some more advanced stuff
            SECTION("Assignment operator can be called") {
                Fixed foo, bar(i);
                foo = bar;
                REQUIRE((Underlying)foo == (Underlying)bar);
            }

            SECTION("Copy constructor can be called") {
                Fixed foo(i);
                Fixed bar = foo;
                REQUIRE((Underlying)foo == (Underlying)bar);
            }

            SECTION("Explicit copy constructor can be called") {
                Fixed foo(i);
                Fixed bar(foo);
                REQUIRE((Underlying)foo == (Underlying)bar);
            }
        }
    }

    SECTION("Conversion from float") {
        float i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0f,
                    524287.9997558594f
                )
            )
        );

        SECTION("Implicit conversion from float") {
            Fixed var = i;
            CAPTURE(i, var, (Underlying)var, i * 4096, round(i * 4096), (Underlying)round(i * 4096));
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }

        SECTION("Explicit conversion from float") {
            Fixed var(i);
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }
    }

    SECTION("Conversion from double") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0,
                    524287.9997558594
                )
            )
        );

        SECTION("Implicit conversion from double") {
            Fixed var = i;
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }


        SECTION("Explicit conversion from double") {
            Fixed var(i);
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }
    }

    SECTION("Creation from integer value") {
        Underlying i = GENERATE(take(tests_config::ITERATIONS, random(-524288, 524287)));
        Fixed var = Fixed::from_integer(i);
        REQUIRE((Underlying)var == i * 4096);
    }
}

