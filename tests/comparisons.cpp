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

using namespace unmoving;
using Underlying = PSXFixed::UnderlyingType;

TEST_CASE("Comparisons") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min() + 1, // prevent underflow at bounds
                std::numeric_limits<Underlying>::max() - 1  // prevent overflow at bounds
            )
        )
    );

    SECTION("equal") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                filter(
                    [=](Underlying u) { return u != i; },
                    random(
                        std::numeric_limits<Underlying>::min(),
                        std::numeric_limits<Underlying>::max()
                    )
                )
            )
        );

        SECTION("PSXFixed == PSXFixed") {
            PSXFixed original(i);
            PSXFixed same(i); // same as original
            PSXFixed different(j); // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("PSXFixed != PSXFixed") {
            PSXFixed original(i);
            PSXFixed same(i); // same as original
            PSXFixed different(j); // different from original
            // check for both affirmative and negative != checks
            CHECK_FALSE(original != same);
            CHECK(original != different);
        }

        SECTION("PSXFixed == UnderlyingType") {
            PSXFixed original(i);
            Underlying same = i; // same as original
            Underlying different = j; // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("PSXFixed != UnderlyingType") {
            PSXFixed original(i);
            Underlying same = i; // same as original
            Underlying different = j; // different from original
            // check for both affirmative and negative == checks
            CHECK_FALSE(original != same);
            CHECK(original != different);
        }

        SECTION("UnderlyingType == PSXFixed") {
            Underlying original = i;
            PSXFixed same(i); // same as original
            PSXFixed different(j); // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("UnderlyingType != PSXFixed") {
            Underlying original = i;
            PSXFixed same(i); // same as original
            PSXFixed different(j); // different from original
            // check for both affirmative and negative == checks
            CHECK_FALSE(original != same);
            CHECK(original != different);
        }
    }

    SECTION("less than") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return i < u; },
                    random(
                        i + 1, // must be greater than i
                        std::numeric_limits<Underlying>::max()
                    )
                // )
            )
        );
        Underlying k = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return not (i < u); },
                    random(
                        std::numeric_limits<Underlying>::min(),
                        i // must not be greater than i
                    )
                // )
            )
        );

        SECTION("PSXFixed < PSXFixed") {
            PSXFixed smaller(i);
            PSXFixed bigger(j);
            PSXFixed not_bigger(k);
            // check for both affirmative and negative < checks
            CHECK(smaller < bigger);
            CHECK_FALSE(smaller < not_bigger);
        }

        SECTION("PSXFixed < UnderlyingType") {
            PSXFixed smaller(i);
            Underlying bigger = j;
            Underlying not_bigger = k;
            // check for both affirmative and negative < checks
            CHECK(smaller < bigger);
            CHECK_FALSE(smaller < not_bigger);
        }

        SECTION("UnderlyingType < PSXFixed") {
            Underlying smaller = i;
            PSXFixed bigger(j);
            PSXFixed not_bigger(k);
            // check for both affirmative and negative < checks
            CHECK(smaller < bigger);
            CHECK_FALSE(smaller < not_bigger);
        }
    }

    SECTION("greater than") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return i > u; },
                    random(
                        std::numeric_limits<Underlying>::min(),
                        i - 1 // must be less than i
                    )
                // )
            )
        );
        Underlying k = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return not (i > u); },
                    random(
                        // must not be less than i
                        i,
                        std::numeric_limits<Underlying>::max()
                    )
                // )
            )
        );

        SECTION("PSXFixed > PSXFixed") {
            PSXFixed bigger(i);
            PSXFixed smaller(j);
            PSXFixed not_smaller(k);
            // check for both affirmative and negative < checks
            CHECK(bigger > smaller);
            CHECK_FALSE(bigger > not_smaller);
        }


        SECTION("PSXFixed > UnderlyingType") {
            PSXFixed bigger(i);
            Underlying smaller = j;
            Underlying not_smaller = k;
            // check for both affirmative and negative < checks
            CHECK(bigger > smaller);
            CHECK_FALSE(bigger > not_smaller);
        }


        SECTION("UnderlyingType > PSXFixed") {
            Underlying bigger = i;
            PSXFixed smaller(j);
            PSXFixed not_smaller(k);
            // check for both affirmative and negative < checks
            CHECK(bigger > smaller);
            CHECK_FALSE(bigger > not_smaller);
        }
    }

    SECTION("less than or equal") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return i < u; },
                    random(
                        i + 1, // must be greater than i
                        std::numeric_limits<Underlying>::max()
                    )
                // )
            )
        );
        Underlying k = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return not (i <= u); },
                    random(
                        std::numeric_limits<Underlying>::min(),
                        i - 1 // must not be greater than or equal to i
                    )
                // )
            )
        );

        SECTION("PSXFixed <= PSXFixed") {
            PSXFixed original(i);
            PSXFixed equal(i);
            PSXFixed bigger(j);
            PSXFixed not_bigger_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original <= equal);
            CHECK(original <= bigger);
            CHECK_FALSE(original <= not_bigger_or_equal);
        }

        SECTION("PSXFixed <= UnderlyingType") {
            PSXFixed original(i);
            Underlying equal = i;
            Underlying bigger = j;
            Underlying not_bigger_or_equal = k;
            // check for both affirmative and negative <= checks
            CHECK(original <= equal);
            CHECK(original <= bigger);
            CHECK_FALSE(original <= not_bigger_or_equal);
        }

        SECTION("UnderlyingType <= PSXFixed") {
            Underlying original = i;
            PSXFixed equal(i);
            PSXFixed bigger(j);
            PSXFixed not_bigger_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original <= equal);
            CHECK(original <= bigger);
            CHECK_FALSE(original <= not_bigger_or_equal);
        }
    }

    SECTION("greater than or equal") {
        Underlying j = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return i > u; },
                    random(
                        std::numeric_limits<Underlying>::min(),
                        i - 1 // must be less than i
                    )
                // )
            )
        );
        Underlying k = GENERATE_COPY(
            take(
                1,
                // filter(
                //     [=](Underlying u) { return not (i >= u); },
                    random(
                        // must not be less than or equal to i
                        i + 1,
                        std::numeric_limits<Underlying>::max()
                    )
                // )
            )
        );

        SECTION("PSXFixed >= PSXFixed") {
            PSXFixed original(i);
            PSXFixed equal(i);
            PSXFixed smaller(j);
            PSXFixed not_smaller_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }

        SECTION("PSXFixed >= UnderlyingType") {
            PSXFixed original(i);
            Underlying equal = i;
            Underlying smaller = j;
            Underlying not_smaller_or_equal = k;
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }

        SECTION("UnderlyingType >= PSXFixed") {
            Underlying original = i;
            PSXFixed equal(i);
            PSXFixed smaller(j);
            PSXFixed not_smaller_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }
    }
}
