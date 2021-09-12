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
    foo *= bar;
    REQUIRE((double)foo == i * j);
}

TEST_CASE("Fixed *= UnderlyingType") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Underlying j = GENERATE_COPY(take(10, random((Underlying)-max_operand, (Underlying)max_operand)));
    Fixed foo(i);
    Underlying bar = j;
    foo *= bar;
    REQUIRE((double)foo == i * j);
}

TEST_CASE("Fixed * Fixed") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    double j = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Fixed foo(i);
    Fixed bar(j);
    Fixed baz = foo * bar;
    REQUIRE((double)baz == i * j);
}

TEST_CASE("Fixed * UnderlyingType") {
    // max value is sqrt(max fixed point value) to prevent overflow
    const double max_operand = std::sqrt(524287.9997558594);
    double i = GENERATE_COPY(take(10, random(-max_operand, max_operand)));
    Underlying j = GENERATE_COPY(take(10, random((Underlying)-max_operand, (Underlying)max_operand)));
    Fixed foo(i);
    Underlying bar = j;
    Fixed baz = foo * bar;
    REQUIRE((double)baz == i * j);
}
