#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed == Fixed") {
    Underlying i = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying j = GENERATE_COPY(
        take(
            100,
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
    Fixed foo = {}, bar = {};
    bool less = foo < bar;
    SUCCEED();
}

TEST_CASE("Fixed > Fixed") {
    Fixed foo = {}, bar = {};
    bool greater = foo > bar;
    SUCCEED();
}

TEST_CASE("Fixed < UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool less = foo < bar;
    SUCCEED();
}

TEST_CASE("Fixed > UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool greater = foo > bar;
    SUCCEED();
}

TEST_CASE("UnderlyingType < Fixed") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool less = bar < foo;
    SUCCEED();
}

TEST_CASE("UnderlyingType > Fixed") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool greater = bar > foo;
    SUCCEED();
}

TEST_CASE("Fixed <= Fixed") {
    Fixed foo = {}, bar = {};
    bool less = foo <= bar;
    SUCCEED();
}

TEST_CASE("Fixed >= Fixed") {
    Fixed foo = {}, bar = {};
    bool greater = foo >= bar;
    SUCCEED();
}

TEST_CASE("Fixed <= UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool less = foo <= bar;
    SUCCEED();
}

TEST_CASE("Fixed >= UnderlyingType") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool greater = foo >= bar;
    SUCCEED();
}

TEST_CASE("UnderlyingType <= Fixed") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool less = bar <= foo;
    SUCCEED();
}

TEST_CASE("UnderlyingType >= Fixed") {
    Fixed foo = {};
    Fixed::UnderlyingType bar = {};
    bool greater = bar >= foo;
    SUCCEED();
}
