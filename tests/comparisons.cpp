#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

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

        SECTION("Fixed == Fixed") {
            Fixed original(i);
            Fixed same(i); // same as original
            Fixed different(j); // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("Fixed != Fixed") {
            Fixed original(i);
            Fixed same(i); // same as original
            Fixed different(j); // different from original
            // check for both affirmative and negative != checks
            CHECK_FALSE(original != same);
            CHECK(original != different);
        }

        SECTION("Fixed == UnderlyingType") {
            Fixed original(i);
            Underlying same = i; // same as original
            Underlying different = j; // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("Fixed != UnderlyingType") {
            Fixed original(i);
            Underlying same = i; // same as original
            Underlying different = j; // different from original
            // check for both affirmative and negative == checks
            CHECK_FALSE(original != same);
            CHECK(original != different);
        }

        SECTION("UnderlyingType == Fixed") {
            Underlying original = i;
            Fixed same(i); // same as original
            Fixed different(j); // different from original
            // check for both affirmative and negative == checks
            CHECK(original == same);
            CHECK_FALSE(original == different);
        }

        SECTION("UnderlyingType != Fixed") {
            Underlying original = i;
            Fixed same(i); // same as original
            Fixed different(j); // different from original
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

        SECTION("Fixed < Fixed") {
            Fixed smaller(i);
            Fixed bigger(j);
            Fixed not_bigger(k);
            // check for both affirmative and negative < checks
            CHECK(smaller < bigger);
            CHECK_FALSE(smaller < not_bigger);
        }

        SECTION("Fixed < UnderlyingType") {
            Fixed smaller(i);
            Underlying bigger = j;
            Underlying not_bigger = k;
            // check for both affirmative and negative < checks
            CHECK(smaller < bigger);
            CHECK_FALSE(smaller < not_bigger);
        }

        SECTION("UnderlyingType < Fixed") {
            Underlying smaller = i;
            Fixed bigger(j);
            Fixed not_bigger(k);
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

        SECTION("Fixed > Fixed") {
            Fixed bigger(i);
            Fixed smaller(j);
            Fixed not_smaller(k);
            // check for both affirmative and negative < checks
            CHECK(bigger > smaller);
            CHECK_FALSE(bigger > not_smaller);
        }


        SECTION("Fixed > UnderlyingType") {
            Fixed bigger(i);
            Underlying smaller = j;
            Underlying not_smaller = k;
            // check for both affirmative and negative < checks
            CHECK(bigger > smaller);
            CHECK_FALSE(bigger > not_smaller);
        }


        SECTION("UnderlyingType > Fixed") {
            Underlying bigger = i;
            Fixed smaller(j);
            Fixed not_smaller(k);
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

        SECTION("Fixed <= Fixed") {
            Fixed original(i);
            Fixed equal(i);
            Fixed bigger(j);
            Fixed not_bigger_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original <= equal);
            CHECK(original <= bigger);
            CHECK_FALSE(original <= not_bigger_or_equal);
        }

        SECTION("Fixed <= UnderlyingType") {
            Fixed original(i);
            Underlying equal = i;
            Underlying bigger = j;
            Underlying not_bigger_or_equal = k;
            // check for both affirmative and negative <= checks
            CHECK(original <= equal);
            CHECK(original <= bigger);
            CHECK_FALSE(original <= not_bigger_or_equal);
        }

        SECTION("UnderlyingType <= Fixed") {
            Underlying original = i;
            Fixed equal(i);
            Fixed bigger(j);
            Fixed not_bigger_or_equal(k);
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

        SECTION("Fixed >= Fixed") {
            Fixed original(i);
            Fixed equal(i);
            Fixed smaller(j);
            Fixed not_smaller_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }

        SECTION("Fixed >= UnderlyingType") {
            Fixed original(i);
            Underlying equal = i;
            Underlying smaller = j;
            Underlying not_smaller_or_equal = k;
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }

        SECTION("UnderlyingType >= Fixed") {
            Underlying original = i;
            Fixed equal(i);
            Fixed smaller(j);
            Fixed not_smaller_or_equal(k);
            // check for both affirmative and negative <= checks
            CHECK(original >= equal);
            CHECK(original >= smaller);
            CHECK_FALSE(original >= not_smaller_or_equal);
        }
    }
}
