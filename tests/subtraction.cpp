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
 #include <limits>

#include <cmath>
#include <cstdint>

#include <catch2/catch.hpp>

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

using namespace unmoving;
using Underlying = PSXFixed::UnderlyingType;

// calculated propagated accuracy error after a subtraction
constexpr double ACCURACY = PSXFixed::ACCURACY * 2.0;

TEST_CASE("Subtraction") {
    double i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                PSXFixed::FRACTIONAL_MIN,
                PSXFixed::FRACTIONAL_MAX
            )
        )
    );
    // pick second operand carefully to avoid signed overflow UB
    double j = GENERATE_COPY(
        take(
            1,
            filter(
                [=](double u) {
                    auto sum = i - u;
                    return PSXFixed::FRACTIONAL_MIN <= sum and
                        sum <= PSXFixed::FRACTIONAL_MAX;
                },
                random(
                    PSXFixed::FRACTIONAL_MIN,
                    PSXFixed::FRACTIONAL_MAX
                )
            )
        )
    );
    PSXFixed foo(i);
    PSXFixed bar(j);
    // use calculated accuracy to set the margin of error
    auto expected_result = Approx(i - j).margin(ACCURACY);

    SECTION("PSXFixed -= PSXFixed") {
        CHECK((double)(foo -= bar) == expected_result);
        REQUIRE((double)foo == expected_result);
    }

    SECTION("PSXFixed - PSXFixed") {
        PSXFixed baz = foo - bar;
        REQUIRE((double)baz == expected_result);
    }
}
