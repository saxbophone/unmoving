#include <cmath>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed *= Fixed") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    double j = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Fixed foo(i);
    Fixed bar(j);
    // allowed to deviate up to the smallest step in the fixed-point representation
    auto expected_result = Approx((double)foo * (double)bar).margin(Fixed::FRACTIONAL_STEP);
    CHECK((double)(foo *= bar) == expected_result);
    REQUIRE((double)foo == expected_result);
}

TEST_CASE("Fixed *= UnderlyingType") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Underlying j = GENERATE_COPY(take(10, random((Underlying)-max_operand, (Underlying)max_operand)));
    Fixed foo(i);
    Underlying bar = j;
    // allowed to deviate up to the smallest step in the fixed-point representation
    auto expected_result = Approx((double)foo * bar).margin(Fixed::FRACTIONAL_STEP);
    CHECK((double)(foo *= bar) == expected_result);
    REQUIRE((double)foo == expected_result);
}

TEST_CASE("Fixed * Fixed") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    double j = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Fixed foo(i);
    Fixed bar(j);
    Fixed baz = foo * bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx((double)foo * (double)bar).margin(Fixed::FRACTIONAL_STEP));
}

TEST_CASE("Fixed * UnderlyingType") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Underlying j = GENERATE_COPY(take(10, random((Underlying)-max_operand, (Underlying)max_operand)));
    Fixed foo(i);
    Underlying bar = j;
    Fixed baz = foo * bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx((double)foo * bar).margin(Fixed::FRACTIONAL_STEP));
}

TEST_CASE("UnderlyingType * Fixed") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    Underlying i = GENERATE_COPY(take(10, random((Underlying)-max_operand, (Underlying)max_operand)));
    double j = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Underlying foo = i;
    Fixed bar(j);
    Fixed baz = foo * bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx(foo * (double)bar).margin(Fixed::FRACTIONAL_STEP));
}
