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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed original(i);
    Fixed same(i); // same as original
    Fixed maybe_different(j); // might (probably will) be different
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK((original == maybe_different) == (i == j));
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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed original(i);
    Fixed same(i); // same as original
    Fixed maybe_different(j); // might (probably will) be different
    // check for both affirmative and negative != checks
    CHECK_FALSE(original != same);
    CHECK((original != maybe_different) == (i != j));
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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed original(i);
    Underlying same = i; // same as original
    Underlying maybe_different = j; // might (probably will) be different
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK((original == maybe_different) == (i == j));
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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Fixed original(i);
    Underlying same = i; // same as original
    Underlying maybe_different = j; // might (probably will) be different
    // check for both affirmative and negative == checks
    CHECK_FALSE(original != same);
    CHECK((original != maybe_different) == (i != j));
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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying original = i;
    Fixed same(i); // same as original
    Fixed maybe_different(j); // might (probably will) be different
    // check for both affirmative and negative == checks
    CHECK(original == same);
    CHECK((original == maybe_different) == (i == j));
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
    Underlying j = GENERATE(
        take(
            100,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    Underlying original = i;
    Fixed same(i); // same as original
    Fixed maybe_different(j); // might (probably will) be different
    // check for both affirmative and negative == checks
    CHECK_FALSE(original != same);
    CHECK((original != maybe_different) == (i != j));
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
