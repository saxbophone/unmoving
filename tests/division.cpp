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
 #include <catch2/catch.hpp>

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;
using Underlying = PSXFixed::UnderlyingType;

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

    SECTION("Division by PSXFixed") {
        double j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of PSXFixed type
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

        PSXFixed foo(i);
        PSXFixed bar(j);
        auto expected_result = Approx((double)foo / (double)bar).margin(std::pow(1.0 + PSXFixed::ACCURACY, 2.0) - 1.0);

        SECTION("PSXFixed /= PSXFixed") {
            CAPTURE(i, j, expected_result, (double)foo, (double)bar);
            CHECK((double)(foo /= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("PSXFixed / PSXFixed") {
            PSXFixed baz = foo / bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }
    }

    SECTION("Division by UnderlyingType") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                filter(
                    // verify result does not exceed bounds of PSXFixed type
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

        PSXFixed foo(i);
        Underlying bar = j;
        auto expected_result = Approx((double)foo / bar).margin(std::pow(1.0 + PSXFixed::ACCURACY, 2.0) - 1.0);

        SECTION("PSXFixed /= UnderlyingType") {
            CHECK((double)(foo /= bar) == expected_result);
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)foo == expected_result);
        }

        SECTION("PSXFixed / UnderlyingType") {
            PSXFixed baz = foo / bar;
            // allowed to deviate up to the smallest step in the fixed-point representation
            REQUIRE((double)baz == expected_result);
        }
    }
}
