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
#include <type_traits>

// defer static checks to runtime
// (so we can run the test suite and detect them as a runtime failure rather than compile error)
#define CATCH_CONFIG_RUNTIME_STATIC_REQUIRE
#include <catch2/catch.hpp>

#include <unmoving/Fixed.hpp>

#include "config.hpp"

// various static (compile-time) checks on properties of Fixed class

using namespace com::saxbophone::unmoving;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Static Checks") {
    SECTION("Fixed::UnderlyingType is integral") {
        STATIC_REQUIRE(std::is_integral_v<Underlying>);
    }

    SECTION("Fixed::UnderlyingType has more bits than Fixed::FRACTION_BITS") {
        STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > Fixed::FRACTION_BITS);
    }

    SECTION("Fixed::UnderlyingType has more bits than Fixed::DECIMAL_BITS") {
        STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > Fixed::DECIMAL_BITS);
    }

    SECTION("Fixed::SCALE == 2 ** Fixed::FRACTION_BITS") {
        STATIC_REQUIRE(Fixed::SCALE == 1 << Fixed::FRACTION_BITS);
    }

    SECTION("Fixed::DECIMAL_BITS == Fixed::UnderlyingType bits - Fixed::FRACTION_BITS") {
        STATIC_REQUIRE(Fixed::DECIMAL_BITS == std::numeric_limits<Underlying>::digits - Fixed::FRACTION_BITS);
    }

    SECTION("Fixed::PRECISION == 1 / Fixed::SCALE") {
        STATIC_REQUIRE(Fixed::PRECISION == Approx(1.0 / Fixed::SCALE));
    }

    SECTION("Fixed::ACCURACY == Fixed::PRECISION / 2") {
        STATIC_REQUIRE(Fixed::ACCURACY == Fixed::PRECISION / 2.0);
    }

    SECTION("Fixed::DECIMAL_MAX == 2 ** Fixed::DECIMAL_BITS - 1") {
        STATIC_REQUIRE(Fixed::DECIMAL_MAX == (1 << Fixed::DECIMAL_BITS) - 1);
    }

    SECTION("Fixed::DECIMAL_MIN == -(2 ** Fixed::DECIMAL_BITS)") {
        STATIC_REQUIRE(Fixed::DECIMAL_MIN == -(1 << Fixed::DECIMAL_BITS));
    }

    SECTION("Fixed::FRACTIONAL_MAX == Fixed::DECIMAL_MAX + (1 - Fixed::PRECISION)") {
        STATIC_REQUIRE(Fixed::FRACTIONAL_MAX == Fixed::DECIMAL_MAX + (1.0 - Fixed::PRECISION));
    }

    SECTION("Fixed::FRACTIONAL_MIN == Fixed::DECIMAL_MIN") {
        STATIC_REQUIRE(Fixed::FRACTIONAL_MIN == Fixed::DECIMAL_MIN);
    }

    SECTION("Fixed::MAX() == Max 32-bit signed integer") {
        STATIC_REQUIRE(Fixed::MAX() == Fixed(std::numeric_limits<Fixed::UnderlyingType>::max()));
    }

    SECTION("Fixed::MIN() == Min 32-bit signed integer") {
        STATIC_REQUIRE(Fixed::MIN() == Fixed(std::numeric_limits<Fixed::UnderlyingType>::min()));
    }

    SECTION("typeof(Fixed::MAX()) == Fixed") {
        STATIC_REQUIRE(std::is_same_v<decltype(Fixed::MAX()), Fixed>);
    }

    SECTION("typeof(Fixed::MIN()) == Fixed") {
        STATIC_REQUIRE(std::is_same_v<decltype(Fixed::MIN()), Fixed>);
    }

    SECTION("typeof(Fixed + Fixed) == Fixed") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x + y), Fixed>);
    }

    SECTION("typeof(Fixed += Fixed) == Fixed&") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x += y), Fixed&>);
    }

    SECTION("typeof(Fixed - Fixed) == Fixed") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x - y), Fixed>);
    }

    SECTION("typeof(Fixed -= Fixed) == Fixed&") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x -= y), Fixed&>);
    }

    SECTION("typeof(Fixed * Fixed) == Fixed") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), Fixed>);
    }

    SECTION("typeof(Fixed *= Fixed) == Fixed&") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x *= y), Fixed&>);
    }

    SECTION("typeof(Fixed * UnderlyingType) == Fixed") {
        Fixed x = {};
        Fixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), Fixed>);
    }

    SECTION("typeof(Fixed *= UnderlyingType) == Fixed&") {
        Fixed x = {};
        Fixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x *= y), Fixed&>);
    }

    SECTION("typeof(UnderlyingType * Fixed) == Fixed") {
        Fixed::UnderlyingType x = {};
        Fixed y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), Fixed>);
    }

    SECTION("typeof(Fixed / Fixed) == Fixed") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x / y), Fixed>);
    }

    SECTION("typeof(Fixed /= Fixed) == Fixed&") {
        Fixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x /= y), Fixed&>);
    }

    SECTION("typeof(Fixed / UnderlyingType) == Fixed") {
        Fixed x = {};
        Fixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x / y), Fixed>);
    }

    SECTION("typeof(Fixed /= UnderlyingType) == Fixed&") {
        Fixed x = {};
        Fixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x /= y), Fixed&>);
    }
}

