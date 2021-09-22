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

#include <unmoving/PSXFixed.hpp>

#include "config.hpp"

// various static (compile-time) checks on properties of PSXFixed class

using namespace com::saxbophone::unmoving;
using Underlying = PSXFixed::UnderlyingType;

TEST_CASE("Static Checks") {
    SECTION("PSXFixed::UnderlyingType is integral") {
        STATIC_REQUIRE(std::is_integral_v<Underlying>);
    }

    SECTION("PSXFixed::UnderlyingType has more bits than PSXFixed::FRACTION_BITS") {
        STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > PSXFixed::FRACTION_BITS);
    }

    SECTION("PSXFixed::UnderlyingType has more bits than PSXFixed::DECIMAL_BITS") {
        STATIC_REQUIRE(std::numeric_limits<Underlying>::digits > PSXFixed::DECIMAL_BITS);
    }

    SECTION("PSXFixed::SCALE == 2 ** PSXFixed::FRACTION_BITS") {
        STATIC_REQUIRE(PSXFixed::SCALE == 1 << PSXFixed::FRACTION_BITS);
    }

    SECTION("PSXFixed::DECIMAL_BITS == PSXFixed::UnderlyingType bits - PSXFixed::FRACTION_BITS") {
        STATIC_REQUIRE(PSXFixed::DECIMAL_BITS == std::numeric_limits<Underlying>::digits - PSXFixed::FRACTION_BITS);
    }

    SECTION("PSXFixed::PRECISION == 1 / PSXFixed::SCALE") {
        STATIC_REQUIRE(PSXFixed::PRECISION == Approx(1.0 / PSXFixed::SCALE));
    }

    SECTION("PSXFixed::ACCURACY == PSXFixed::PRECISION / 2") {
        STATIC_REQUIRE(PSXFixed::ACCURACY == PSXFixed::PRECISION / 2.0);
    }

    SECTION("PSXFixed::DECIMAL_MAX == 2 ** PSXFixed::DECIMAL_BITS - 1") {
        STATIC_REQUIRE(PSXFixed::DECIMAL_MAX == (1 << PSXFixed::DECIMAL_BITS) - 1);
    }

    SECTION("PSXFixed::DECIMAL_MIN == -(2 ** PSXFixed::DECIMAL_BITS)") {
        STATIC_REQUIRE(PSXFixed::DECIMAL_MIN == -(1 << PSXFixed::DECIMAL_BITS));
    }

    SECTION("PSXFixed::FRACTIONAL_MAX == PSXFixed::DECIMAL_MAX + (1 - PSXFixed::PRECISION)") {
        STATIC_REQUIRE(PSXFixed::FRACTIONAL_MAX == PSXFixed::DECIMAL_MAX + (1.0 - PSXFixed::PRECISION));
    }

    SECTION("PSXFixed::FRACTIONAL_MIN == PSXFixed::DECIMAL_MIN") {
        STATIC_REQUIRE(PSXFixed::FRACTIONAL_MIN == PSXFixed::DECIMAL_MIN);
    }

    SECTION("PSXFixed::MAX() == Max 32-bit signed integer") {
        STATIC_REQUIRE(PSXFixed::MAX() == PSXFixed(std::numeric_limits<PSXFixed::UnderlyingType>::max()));
    }

    SECTION("PSXFixed::MIN() == Min 32-bit signed integer") {
        STATIC_REQUIRE(PSXFixed::MIN() == PSXFixed(std::numeric_limits<PSXFixed::UnderlyingType>::min()));
    }

    SECTION("typeof(PSXFixed::MAX()) == PSXFixed") {
        STATIC_REQUIRE(std::is_same_v<decltype(PSXFixed::MAX()), PSXFixed>);
    }

    SECTION("typeof(PSXFixed::MIN()) == PSXFixed") {
        STATIC_REQUIRE(std::is_same_v<decltype(PSXFixed::MIN()), PSXFixed>);
    }

    SECTION("typeof(PSXFixed + PSXFixed) == PSXFixed") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x + y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed += PSXFixed) == PSXFixed&") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x += y), PSXFixed&>);
    }

    SECTION("typeof(PSXFixed - PSXFixed) == PSXFixed") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x - y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed -= PSXFixed) == PSXFixed&") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x -= y), PSXFixed&>);
    }

    SECTION("typeof(PSXFixed * PSXFixed) == PSXFixed") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed *= PSXFixed) == PSXFixed&") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x *= y), PSXFixed&>);
    }

    SECTION("typeof(PSXFixed * UnderlyingType) == PSXFixed") {
        PSXFixed x = {};
        PSXFixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed *= UnderlyingType) == PSXFixed&") {
        PSXFixed x = {};
        PSXFixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x *= y), PSXFixed&>);
    }

    SECTION("typeof(UnderlyingType * PSXFixed) == PSXFixed") {
        PSXFixed::UnderlyingType x = {};
        PSXFixed y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x * y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed / PSXFixed) == PSXFixed") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x / y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed /= PSXFixed) == PSXFixed&") {
        PSXFixed x = {}, y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x /= y), PSXFixed&>);
    }

    SECTION("typeof(PSXFixed / UnderlyingType) == PSXFixed") {
        PSXFixed x = {};
        PSXFixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x / y), PSXFixed>);
    }

    SECTION("typeof(PSXFixed /= UnderlyingType) == PSXFixed&") {
        PSXFixed x = {};
        PSXFixed::UnderlyingType y = {};
        STATIC_REQUIRE(std::is_same_v<decltype(x /= y), PSXFixed&>);
    }
}

