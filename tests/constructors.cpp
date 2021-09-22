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

#include <catch2/catch.hpp>

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

using namespace unmoving;
using Underlying = PSXFixed::UnderlyingType;

TEST_CASE("Constructors") {
    SECTION("Default constructor can be called") {
        PSXFixed foo = {};
        REQUIRE((Underlying)foo == 0);
    }

    SECTION("Conversion from fixed-point integer") {
        Underlying i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        );

        SECTION("Implicit conversion from fixed-point integer") {
            PSXFixed var = i;
            REQUIRE((Underlying)var == i);
        }

        SECTION("Explicit conversion from fixed-point integer") {
            PSXFixed var(i);
            REQUIRE((Underlying)var == i);
        }

        SECTION("Special advanced constructors") {
            // Now for some more advanced stuff
            SECTION("Assignment operator can be called") {
                PSXFixed foo, bar(i);
                foo = bar;
                REQUIRE((Underlying)foo == (Underlying)bar);
            }

            SECTION("Copy constructor can be called") {
                PSXFixed foo(i);
                PSXFixed bar = foo;
                REQUIRE((Underlying)foo == (Underlying)bar);
            }

            SECTION("Explicit copy constructor can be called") {
                PSXFixed foo(i);
                PSXFixed bar(foo);
                REQUIRE((Underlying)foo == (Underlying)bar);
            }
        }
    }

    SECTION("Conversion from float") {
        float i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0f,
                    524287.9997558594f
                )
            )
        );

        SECTION("Implicit conversion from float") {
            PSXFixed var = i;
            CAPTURE(i, var, (Underlying)var, i * 4096, round(i * 4096), (Underlying)round(i * 4096));
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }

        SECTION("Explicit conversion from float") {
            PSXFixed var(i);
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }
    }

    SECTION("Conversion from double") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    -524288.0,
                    524287.9997558594
                )
            )
        );

        SECTION("Implicit conversion from double") {
            PSXFixed var = i;
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }


        SECTION("Explicit conversion from double") {
            PSXFixed var(i);
            REQUIRE((Underlying)var == (Underlying)round(i * 4096));
        }
    }

    SECTION("Creation from integer value") {
        Underlying i = GENERATE(take(tests_config::ITERATIONS, random(-524288, 524287)));
        PSXFixed var = PSXFixed::from_integer(i);
        REQUIRE((Underlying)var == i * 4096);
    }
}

