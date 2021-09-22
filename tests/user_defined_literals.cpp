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

/*
 * NOTE: we shouldn't test any negative literals here, because this would be
 * testing the unary minus operator as well. Negative literals in C++ are
 * actually positive literals with the unary minus operator applied to them, so
 * there are no "true" negative integer literals.
 */

TEST_CASE("User-defined literals") {
    SECTION("Full user-defined literal") {
        auto literal_to_value = GENERATE(table<PSXFixed, double>({
            {123.45_fx, 123.45,},
            {123.456789_fx, 123.456789,},
            {0.317282_fx, 0.317282,},
            {456128.33937921009_fx, 456128.33937921009,},
        }));
        PSXFixed foo = std::get<PSXFixed>(literal_to_value);
        CAPTURE(std::get<PSXFixed>(literal_to_value), std::get<double>(literal_to_value));
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(PSXFixed::ACCURACY));
    }

    SECTION("Fractional user-defined literal") {
        auto literal_to_value = GENERATE(table<PSXFixed, double>({
            {.45_fx, .45,},
            {.456789_fx, .456789,},
            {.317282_fx, .317282,},
            {.33937921009_fx, .33937921009,},
        }));
        PSXFixed foo = std::get<PSXFixed>(literal_to_value);
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(PSXFixed::ACCURACY));
    }

    SECTION("Integral user-defined literal") {
        auto literal_to_value = GENERATE(table<PSXFixed, double>({
            {12345_fx, 12345.0,},
            {123456_fx, 123456.0,},
            {317282_fx, 317282.0,},
            {456128_fx, 456128.0,},
        }));
        PSXFixed foo = std::get<PSXFixed>(literal_to_value);
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(PSXFixed::ACCURACY));
    }
}
