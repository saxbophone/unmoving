#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed == Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Fixed same(i); // same as original
    Fixed different(j); // different from original
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK_FALSE(original == different);
}

TEST_CASE("Fixed != Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Fixed same(i); // same as original
    Fixed different(j); // different from original
    // check for both affirmative and negative != checks
    CHECK_FALSE(original != same);
    CHECK(original != different);
}

TEST_CASE("Fixed == UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Underlying same = i; // same as original
    Underlying different = j; // different from original
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK_FALSE(original == different);
}

TEST_CASE("Fixed != UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Underlying same = i; // same as original
    Underlying different = j; // different from original
    // check for both affirmative and negative == checks
    CHECK_FALSE(original != same);
    CHECK(original != different);
}

TEST_CASE("UnderlyingType == Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying original = i;
    Fixed same(i); // same as original
    Fixed different(j); // different from original
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK_FALSE(original == different);
}

TEST_CASE("UnderlyingType != Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return u != i; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying original = i;
    Fixed same(i); // same as original
    Fixed different(j); // different from original
    // check for both affirmative and negative == checks
    CHECK_FALSE(original != same);
    CHECK(original != different);
}

TEST_CASE("Fixed < Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i < u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed smaller(i);
    Fixed bigger(j);
    Fixed not_bigger(k);
    // check for both affirmative and negative < checks
    CHECK(smaller < bigger);
    CHECK_FALSE(smaller < not_bigger);
}

TEST_CASE("Fixed > Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i > u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed bigger(i);
    Fixed smaller(j);
    Fixed not_smaller(k);
    // check for both affirmative and negative < checks
    CHECK(bigger > smaller);
    CHECK_FALSE(bigger > not_smaller);
}

TEST_CASE("Fixed < UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i < u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed smaller(i);
    Underlying bigger = j;
    Underlying not_bigger = k;
    // check for both affirmative and negative < checks
    CHECK(smaller < bigger);
    CHECK_FALSE(smaller < not_bigger);
}

TEST_CASE("Fixed > UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i > u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed bigger(i);
    Underlying smaller = j;
    Underlying not_smaller = k;
    // check for both affirmative and negative < checks
    CHECK(bigger > smaller);
    CHECK_FALSE(bigger > not_smaller);
}

TEST_CASE("UnderlyingType < Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i < u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying smaller = i;
    Fixed bigger(j);
    Fixed not_bigger(k);
    // check for both affirmative and negative < checks
    CHECK(smaller < bigger);
    CHECK_FALSE(smaller < not_bigger);
}

TEST_CASE("UnderlyingType > Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i > u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying bigger = i;
    Fixed smaller(j);
    Fixed not_smaller(k);
    // check for both affirmative and negative < checks
    CHECK(bigger > smaller);
    CHECK_FALSE(bigger > not_smaller);
}

TEST_CASE("Fixed <= Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i <= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Fixed equal(i);
    Fixed bigger(j);
    Fixed not_bigger_or_equal(k);
    // check for both affirmative and negative <= checks
    CHECK(original <= equal);
    CHECK(original <= bigger);
    CHECK_FALSE(original <= not_bigger_or_equal);
}

TEST_CASE("Fixed >= Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i >= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Fixed equal(i);
    Fixed smaller(j);
    Fixed not_smaller_or_equal(k);
    // check for both affirmative and negative <= checks
    CHECK(original >= equal);
    CHECK(original >= smaller);
    CHECK_FALSE(original >= not_smaller_or_equal);
}

TEST_CASE("Fixed <= UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i <= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Underlying equal = i;
    Underlying bigger = j;
    Underlying not_bigger_or_equal = k;
    // check for both affirmative and negative <= checks
    CHECK(original <= equal);
    CHECK(original <= bigger);
    CHECK_FALSE(original <= not_bigger_or_equal);
}

TEST_CASE("Fixed >= UnderlyingType") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i >= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed original(i);
    Underlying equal = i;
    Underlying smaller = j;
    Underlying not_smaller_or_equal = k;
    // check for both affirmative and negative <= checks
    CHECK(original >= equal);
    CHECK(original >= smaller);
    CHECK_FALSE(original >= not_smaller_or_equal);
}

TEST_CASE("UnderlyingType <= Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i < u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i <= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying original = i;
    Fixed equal(i);
    Fixed bigger(j);
    Fixed not_bigger_or_equal(k);
    // check for both affirmative and negative <= checks
    CHECK(original <= equal);
    CHECK(original <= bigger);
    CHECK_FALSE(original <= not_bigger_or_equal);
}

TEST_CASE("UnderlyingType >= Fixed") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return i > u; },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying k = GENERATE_COPY(
        take(
            tests_config::ITERATIONS,
            filter(
                [=](Underlying u) { return not (i >= u); },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Underlying original = i;
    Fixed equal(i);
    Fixed smaller(j);
    Fixed not_smaller_or_equal(k);
    // check for both affirmative and negative <= checks
    CHECK(original >= equal);
    CHECK(original >= smaller);
    CHECK_FALSE(original >= not_smaller_or_equal);
}
