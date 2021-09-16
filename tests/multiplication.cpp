#include <cmath>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Multiplication") {
    double i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                -524288.0,
                524287.9997558594
            )
        )
    );

    SECTION("Multiplication by Fixed") {
        double bound_a = -524288.0 / i;
        double bound_b = 524287.9997558594 / i;
        double bound_min = std::min(bound_a, bound_b);
        double bound_max = std::max(bound_a, bound_b);
        double j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of Fixed type
                    [=](double u) {
                        // get closest Fixed value of each operand
                        double x = (double)Fixed(i);
                        double y = (double)Fixed(u);
                        return -524288.0 <= (x * y) and
                            (x * y) <= 524287.9997558594;
                    },
                    random(
                        bound_min,
                        bound_max
                    )
                )
            )
        );

        Fixed foo(i);
        Fixed bar(j);
        auto expected_result = Approx((double)foo * (double)bar).margin(std::pow(1.0 + Fixed::ACCURACY, 2.0) - 1.0);

        SECTION("Fixed *= Fixed") {
            CAPTURE(i, j, expected_result, (double)foo, (double)bar);
            CHECK((double)(foo *= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("Fixed * Fixed") {
            Fixed baz = foo * bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }
    }

    SECTION("Multiplication by UnderlyingType") {
        Underlying bound_a = (Underlying)(-524288.0 / i);
        Underlying bound_b = (Underlying)(524287.9997558594 / i);
        Underlying bound_min = std::min(bound_a, bound_b);
        Underlying bound_max = std::max(bound_a, bound_b);
        Underlying j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of Fixed type
                    [=](Underlying u) {
                        return -524288.0 <= (i * u) and
                            (i * u) <= 524287.9997558594;
                    },
                    random(
                        bound_min,
                        bound_max
                    )
                )
            )
        );

        Fixed foo(i);
        Underlying bar = j;
        auto expected_result = Approx((double)foo * bar).margin(std::pow(1.0 + Fixed::ACCURACY, 2.0) - 1.0);

        SECTION("Fixed *= UnderlyingType") {
            CHECK((double)(foo *= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("Fixed * UnderlyingType") {
            Fixed baz = foo * bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }

        SECTION("UnderlyingType * Fixed") {
            Fixed baz = bar * foo;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }

    }
}
