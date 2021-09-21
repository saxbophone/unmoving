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

#include <unmoving/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Unary operations") {
    SECTION("Fixed prefix increment") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0,
                    // max is reduced by 1 to prevent overflow
                    524286.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = ++foo;
        REQUIRE((double)bar == Approx(++i).margin(Fixed::ACCURACY));
        REQUIRE((double)foo == Approx(i).margin(Fixed::ACCURACY)); // relies upon i value changed in previous check
    }

    SECTION("Fixed postfix increment") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0,
                    // max is reduced by 1 to prevent overflow
                    524286.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = foo++;
        REQUIRE((double)bar == Approx(i++).margin(Fixed::ACCURACY));
        REQUIRE((double)foo == Approx(i).margin(Fixed::ACCURACY)); // relies upon i value changed in previous check
    }

    SECTION("Fixed prefix decrement") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    // min is increased by 1 to prevent underflow
                    -524287.0,
                    524287.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = --foo;
        REQUIRE((double)bar == Approx(--i).margin(Fixed::ACCURACY));
        REQUIRE((double)foo == Approx(i).margin(Fixed::ACCURACY)); // relies upon i value changed in previous check
    }

    SECTION("Fixed postfix decrement") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    // min is increased by 1 to prevent underflow
                    -524287.0,
                    524287.9997558594
                )
            )
        );
        Fixed foo(i);
        Fixed bar = foo--;
        REQUIRE((double)bar == Approx(i--).margin(Fixed::ACCURACY));
        REQUIRE((double)foo == Approx(i).margin(Fixed::ACCURACY)); // relies upon i value changed in previous check
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
