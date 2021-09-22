/*
 * This source file forms part of Unmoving
 * Unmoving is a C++ header-only library providing more convenient fixed-point
 * arithmetic for the Sony PlayStation ("PS1").
 *
 * Copyright Joshua Saxby <joshua.a.saxby@gmail.com> 2021
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
 #include <cmath>

#include <catch2/catch.hpp>

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;
using Underlying = PSXFixed::UnderlyingType;

template <typename T, typename U>
constexpr double propagated_accuracy(T x, U y) {
    if (x == 0 or y == 0) {
        return 0.0; // avoid divide-by-zero errors, these results are always exact
    }
    double z = x * y;
    // use standard deviation method
    return std::abs(z) * std::sqrt(std::pow(PSXFixed::ACCURACY / x, 2.0) + std::pow(PSXFixed::ACCURACY / y, 2.0));
}

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

    SECTION("Multiplication by PSXFixed") {
        double bound_a = -524288.0 / i;
        double bound_b = 524287.9997558594 / i;
        double bound_min = std::min(bound_a, bound_b);
        double bound_max = std::max(bound_a, bound_b);
        double j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of PSXFixed type
                    [=](double u) {
                        // get closest PSXFixed value of each operand
                        double x = (double)PSXFixed(i);
                        double y = (double)PSXFixed(u);
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

        PSXFixed foo(i);
        PSXFixed bar(j);

        // calculate propagated accuracy error based on operands
        auto expected_result = Approx((double)foo * (double)bar).margin(propagated_accuracy(i, j));

        SECTION("PSXFixed *= PSXFixed") {
            CAPTURE(i, j, expected_result, (double)foo, (double)bar);
            CHECK((double)(foo *= bar) == expected_result);
            REQUIRE((double)foo == expected_result);
        }

        SECTION("PSXFixed * PSXFixed") {
            PSXFixed baz = foo * bar;
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
                    // verify result does not exceed bounds of PSXFixed type
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

        PSXFixed foo(i);
        Underlying bar = j;
        // calculate propagated accuracy error based on operands
        auto expected_result = Approx((double)foo * bar).margin(propagated_accuracy(i, j));

        SECTION("PSXFixed *= UnderlyingType") {
            CHECK((double)(foo *= bar) == expected_result);
            REQUIRE((double)foo == expected_result);
        }

        SECTION("PSXFixed * UnderlyingType") {
            PSXFixed baz = foo * bar;
            REQUIRE((double)baz == expected_result);
        }

        SECTION("UnderlyingType * PSXFixed") {
            PSXFixed baz = bar * foo;
            REQUIRE((double)baz == expected_result);
        }

    }
}
