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
 #include <catch2/catch.hpp>

#include <unmoving/Fixed.hpp>

using namespace com::saxbophone::unmoving;

TEST_CASE("Fixed.to_c_str() returns false when buffer is a null pointer") {
    Fixed var;

    // should fail because of null pointer and not buffer_size, the latter of which is big enough
    REQUIRE_FALSE(var.to_c_str(nullptr, 15));
}
