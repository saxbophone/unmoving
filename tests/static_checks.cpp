#include <limits>
#include <type_traits>

// defer static checks to runtime
// (so we can run the test suite and detect them as a runtime failure rather than compile error)
#define CATCH_CONFIG_RUNTIME_STATIC_REQUIRE
#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

// various static (compile-time) checks on properties of Fixed class

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed::UnderlyingType is integral") {
    STATIC_REQUIRE(std::is_integral_v<Underlying>);
}

TEST_CASE("Fixed::UnderlyingType has more bits than Fixed::FRACTION_BITS") {
    STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > Fixed::FRACTION_BITS);
}

TEST_CASE("Fixed::UnderlyingType has more bits than Fixed::DECIMAL_BITS") {
    STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > Fixed::DECIMAL_BITS);
}

TEST_CASE("Fixed::SCALE == 2 ** Fixed::FRACTION_BITS") {
    STATIC_REQUIRE(Fixed::SCALE == 1 << Fixed::FRACTION_BITS);
}

TEST_CASE("Fixed::DECIMAL_BITS == Fixed::UnderlyingType bits - Fixed::FRACTION_BITS") {
    STATIC_REQUIRE(Fixed::DECIMAL_BITS == std::numeric_limits<Underlying>::digits - Fixed::FRACTION_BITS);
}

TEST_CASE("Fixed::FRACTIONAL_STEP == 1 / Fixed::SCALE") {
    STATIC_REQUIRE(Fixed::FRACTIONAL_STEP == Approx(1.0f / Fixed::SCALE));
}

TEST_CASE("Fixed::DECIMAL_MAX == 2 ** Fixed::DECIMAL_BITS - 1") {
    STATIC_REQUIRE(Fixed::DECIMAL_MAX == (1 << Fixed::DECIMAL_BITS) - 1);
}

TEST_CASE("Fixed::DECIMAL_MIN == -(2 ** Fixed::DECIMAL_BITS)") {
    STATIC_REQUIRE(Fixed::DECIMAL_MIN == -(1 << Fixed::DECIMAL_BITS));
}

TEST_CASE("Fixed::FRACTIONAL_MAX == Fixed::DECIMAL_MAX + (1 - Fixed::FRACTIONAL_STEP)") {
    STATIC_REQUIRE(Fixed::FRACTIONAL_MAX == Fixed::DECIMAL_MAX + (1.0 - Fixed::FRACTIONAL_STEP));
}

TEST_CASE("Fixed::FRACTIONAL_MIN == Fixed::DECIMAL_MIN - (1 - Fixed::FRACTIONAL_STEP)") {
    STATIC_REQUIRE(Fixed::FRACTIONAL_MIN == Fixed::DECIMAL_MIN - (1.0 - Fixed::FRACTIONAL_STEP));
}
