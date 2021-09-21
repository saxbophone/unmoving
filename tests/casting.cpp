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

TEST_CASE("Casting") {
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

    SECTION("Implicit cast Fixed to UnderlyingType") {
        Underlying bar = foo;
        REQUIRE(bar == i);
    }

    SECTION("Explicit cast Fixed to UnderlyingType") {
        REQUIRE((Underlying)foo == i);
    }

    SECTION("Explicit cast Fixed to float") {
        REQUIRE((float)foo == (float)i / 4096);
    }

    SECTION("Explicit cast Fixed to double") {
        REQUIRE((double)foo == (double)i / 4096);
    }

    SECTION("Fixed.to_integer()") {
        REQUIRE(foo.to_integer() == i / 4096);
    }
}
