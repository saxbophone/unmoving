#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Unary operations") {
    SECTION("Fixed prefix increment") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.9997558594,
                    // max is reduced by 1 to prevent overflow
                    524286.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = ++foo;
        REQUIRE((double)bar == Approx(++i).margin(Fixed::FRACTIONAL_STEP));
        REQUIRE((double)foo == Approx(i).margin(Fixed::FRACTIONAL_STEP)); // relies upon i value changed in previous check
    }

    SECTION("Fixed postfix increment") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.9997558594,
                    // max is reduced by 1 to prevent overflow
                    524286.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = foo++;
        REQUIRE((double)bar == Approx(i++).margin(Fixed::FRACTIONAL_STEP));
        REQUIRE((double)foo == Approx(i).margin(Fixed::FRACTIONAL_STEP)); // relies upon i value changed in previous check
    }

    SECTION("Fixed prefix decrement") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    // min is increased by 1 to prevent underflow
                    -524287.9997558594,
                    524287.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = --foo;
        REQUIRE((double)bar == Approx(--i).margin(Fixed::FRACTIONAL_STEP));
        REQUIRE((double)foo == Approx(i).margin(Fixed::FRACTIONAL_STEP)); // relies upon i value changed in previous check
    }

    SECTION("Fixed postfix decrement") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    // min is increased by 1 to prevent underflow
                    -524287.9997558594,
                    524287.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = foo--;
        REQUIRE((double)bar == Approx(i--).margin(Fixed::FRACTIONAL_STEP));
        REQUIRE((double)foo == Approx(i).margin(Fixed::FRACTIONAL_STEP)); // relies upon i value changed in previous check
    }

    SECTION("Fixed unary minus") {
        Underlying i = GENERATE(
            take(
                tests_config::ITERATIONS,
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
}
