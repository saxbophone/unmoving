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

#include <cstdlib>

#include <catch2/catch.hpp>

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;

TEST_CASE("Conversion to String") {
    SECTION("PSXFixed.to_c_str() creates a C string with the value's decimal respresentation") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    PSXFixed::FRACTIONAL_MIN,
                    PSXFixed::FRACTIONAL_MAX
                )
            )
        );
        PSXFixed var = i;
        char output[15] = {}; // need up to 15 characters for string, including null-terminator

        // we require the function call to return true for successful call
        CHECK(var.to_c_str(output, sizeof(output)));
        // now, try and convert that value back to double so we can approximately compare it
        char* cursor = nullptr;
        double value = std::strtod(output, &cursor);
        // strtod sets cursor to output if conversion failed, so check that it isn't
        REQUIRE(cursor != output);

        // finally, approximately compare this value cast to double --we want them equal to 6 decimal places
        REQUIRE(value == Approx((double)var).margin(0.000001));
    }

    SECTION("PSXFixed.to_c_str() returns false when given buffer_size = zero") {
        PSXFixed var;
        char output = {};

        REQUIRE_FALSE(var.to_c_str(&output, 0));
    }

    SECTION("PSXFixed.to_c_str() returns false when 1 ≤ buffer_size < 15") {
        std::size_t buffer_size = GENERATE(range(1U, 14U));
        PSXFixed var;
        char* output = new char[buffer_size] {0};

        REQUIRE_FALSE(var.to_c_str(output, buffer_size));
    }
}
