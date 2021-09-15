#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Division") {
    double i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                -524288.0,
                524287.9997558594
            )
        )
    );

    SECTION("Division by Fixed") {
        double j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of Fixed type
                    [=](double u) {
                        return -524288.0 <= (i / u) and
                            (i / u) <= 524287.9997558594;
                    },
                    random(
                        -524288.0,
                        524287.9997558594
                    )
                )
            )
        );

        Fixed foo(i);
        Fixed bar(j);
        auto expected_result = Approx((double)foo / (double)bar).margin(Fixed::PRECISION);

        SECTION("Fixed /= Fixed") {
            CAPTURE(i, j, expected_result, (double)foo, (double)bar);
            CHECK((double)(foo /= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("Fixed / Fixed") {
            Fixed baz = foo / bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }
    }

    SECTION("Division by UnderlyingType") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of Fixed type
                    [=](Underlying u) {
                        return -524288.0 <= (i / u) and
                            (i / u) <= 524287.9997558594;
                    },
                    random(
                        -524288,
                        524287
                    )
                )
            )
        );

        Fixed foo(i);
        Underlying bar = j;
        auto expected_result = Approx((double)foo / bar).margin(Fixed::PRECISION);

        SECTION("Fixed /= UnderlyingType") {
            CHECK((double)(foo /= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("Fixed / UnderlyingType") {
            Fixed baz = foo / bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }
    }
}
