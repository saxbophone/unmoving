#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed /= Fixed") {
    double i = GENERATE(
        take(
            10,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    double j = GENERATE_COPY(
        take(
            10,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);
    auto expected_result = Approx((double)foo / (double)bar).margin(Fixed::FRACTIONAL_STEP);
    CAPTURE(i, j, expected_result, (double)foo, (double)bar);
    CHECK((double)(foo /= bar) == expected_result);
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == expected_result);
}

TEST_CASE("Fixed /= UnderlyingType") {
    double i = GENERATE(
        take(
            10,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    Underlying j = GENERATE(take(10, random(-524288, 524287)));
    Fixed foo(i);
    Underlying bar = j;
    auto expected_result = Approx((double)foo / bar).margin(Fixed::FRACTIONAL_STEP);
    CHECK((double)(foo /= bar) == expected_result);
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == expected_result);
}

TEST_CASE("Fixed / Fixed") {
    double i = GENERATE(
        take(
            10,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    double j = GENERATE_COPY(
        take(
            10,
            random(
                i / 524287.9997558594, // smallest value allowed to return
                i / Fixed::FRACTIONAL_STEP // largest value allowed to return
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);
    Fixed baz = foo / bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx((double)foo / (double)bar).margin(Fixed::FRACTIONAL_STEP));
}

TEST_CASE("Fixed / UnderlyingType") {
    double i = GENERATE(
        take(
            10,
            random(
                -524288.9997558594,
                524287.9997558594
            )
        )
    );
    Underlying j = GENERATE(take(10, random(-524288, 524287)));
    Fixed foo(i);
    Underlying bar = j;
    Fixed baz = foo / bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx((double)foo / bar).margin(Fixed::FRACTIONAL_STEP));
}
