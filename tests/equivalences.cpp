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

#include <catch2/catch.hpp>

#include <unmoving/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Equivalences") {
    SECTION("Can cast from and back to raw fixed point") {
        Underlying i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        );
        Fixed foo = i;
        Underlying bar = foo;
        REQUIRE(bar == i);
    }

    SECTION("Can cast from and back to float") {
        float i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0f,
                    524287.9997558594f
                )
            )
        );
        Fixed var = i;
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((float)var == Approx(i).margin(Fixed::ACCURACY));
    }

    SECTION("Can cast from and back to double") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0,
                    524287.9997558594
                )
            )
        );
        Fixed var = i;
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((double)var == Approx(i).margin(Fixed::ACCURACY));
    }

    SECTION("Can cast from and back to integer") {
        Underlying i = GENERATE(take(tests_config::ITERATIONS, random(-524288, 524287)));
        Fixed var = Fixed::from_integer(i);
        REQUIRE(var.to_integer() == i);
    }
}
