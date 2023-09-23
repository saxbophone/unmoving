/**
 * @file
 * @brief This file forms part of Unmoving
 * @details Unmoving is a C++ header-only library providing more convenient
 * fixed-point arithmetic for the Sony PlayStation ("PS1"), in the form of a
 * C++ class that wraps the native integer type used by the console standard
 * library for performing fixed-point calculations. This class is intended to
 * remove much of the more tedious aspects of the boilerplate code required to
 * handle numbers in this way. The author hopes that it is useful.
 * @warning Performance testing has not been done either in emulators or real
 * PlayStation hardware. Although effort has been made to make this code
 * efficient, at this stage this cannot be guaranteed, particularly with
 * multiplication or division between two PSXFixed instances.
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date September 2021
 *
 * @copyright Copyright Joshua Saxby <joshua.a.saxby@gmail.com> 2021
 *
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef COM_SAXBOPHONE_UNMOVING_PSX_FIXED_HPP
#define COM_SAXBOPHONE_UNMOVING_PSX_FIXED_HPP

// we can get int32 and size_t from the C++ standard library when build is hosted
#if __STDC_HOSTED__
#include <cstddef> // size_t
#include <cstdint> // int32
#else
// NOTE: this C header is specific to the PSX SDK
#include <sys/types.h> // int32, size_t
#endif
/*
 * get other symbols from the C headers as these are guaranteed to exist both in
 * C++ and the PSX SDK
 */
#include <stdio.h>  // snprintf
#include <stdlib.h> // abs

namespace unmoving {
    class PSXFixed; // forward-declaration to allow declaration of user-defined literals

    /**
     * @brief User-defined literal for PSXFixed objects with fractional parts
     *
     * @b Usage:
     * @code
     * PSXFixed full = 123.45_fx;
     * PSXFixed fractional = .45_fx;
     * @endcode
     * @relatedalso PSXFixed
     */
    template <char...>
    constexpr PSXFixed operator"" _fx();

    /**
     * @brief User-defined literal for PSXFixed objects without fractional parts
     *
     * @b Usage:
     * @code
     * PSXFixed integral = 123_fx;
     * @endcode
     * @warning Use this to initialise PSXFixed objects when the intention is
     * to hold the same value as the integer. Use regular integer literals
     * when the intention is to interpret the integer as a fixed-point value
     * (this is the fixed-point equivalent of initialising a float from raw
     * memory values).
     * @relatedalso PSXFixed
     */
    constexpr PSXFixed operator"" _fx(unsigned long long int literal);

    /**
     * @brief PSXFixed-point arithmetic value type for Sony PlayStation
     * @details Wraps the native 32-bit integers used on the platform for fixed
     * point arithmetic and allows arithmetic operations to be done on these
     * instances directly, handling the additional arithmetic for emulating
     * fixed-point internally.
     * @note The fixed-point integers implemented by this type match those
     * handled by the PSX standard library, which are `Q19.12` numbers when
     * specified in Q Notation (https://en.wikipedia.org/wiki/Q_(number_format))
     */
    class PSXFixed {
    public:
        /**
         * @brief Underlying base type the fixed-point integer is stored as
         * @details Should be `int32` or `int` to match the type used by PSX
         * standard library in its fixed-point maths routines.
         */
        using UnderlyingType = int32_t;
        /** @brief How many bits are used for the integer part of the fixed-point integer */
        static constexpr size_t DECIMAL_BITS = 19;
        /** @brief How many bits are used for the fraction part of the fixed-point integer */
        static constexpr size_t FRACTION_BITS = 12;
        /**
         * @brief The scale used for the fixed-point integer
         * @note This matches the scale used by the PSX standard library for
         * fixed-point arithmetic, which uses a scale of 4096 (macro: `ONE`).
         */
        static constexpr UnderlyingType SCALE = 1 << PSXFixed::FRACTION_BITS;
        /**
         * @brief How far apart two adjacent fixed-point values are
         */
        static constexpr double PRECISION = 1.0 / PSXFixed::SCALE;
        /**
         * @brief The largest difference between a fixed-point value and the
         * "true" value it represents.
         */
        static constexpr double ACCURACY = PSXFixed::PRECISION / 2.0;
        /**
         * @brief Largest integer value representable by the fixed-point type
         */
        static constexpr UnderlyingType DECIMAL_MAX = (1 << PSXFixed::DECIMAL_BITS) - 1;
        /**
         * @brief Smallest integer value representable by the fixed-point type
         */
        static constexpr UnderlyingType DECIMAL_MIN = -(1 << PSXFixed::DECIMAL_BITS);
        /**
         * @brief Largest real value representable by the fixed-point type
         */
        static constexpr double FRACTIONAL_MAX = PSXFixed::DECIMAL_MAX + (1.0 - PSXFixed::PRECISION);
        /**
         * @brief Smallest real value representable by the fixed-point type
         */
        static constexpr double FRACTIONAL_MIN = PSXFixed::DECIMAL_MIN;
        /**
         * @brief Largest PSXFixed value
         */
        static constexpr PSXFixed MAX() {
            return PSXFixed((UnderlyingType)2147483647);
        }
        /**
         * @brief Smallest PSXFixed value
         */
        static constexpr PSXFixed MIN() {
            return PSXFixed((UnderlyingType)-2147483648);
        }
        /**
         * @brief Default constructor, creates a PSXFixed instance with value `0.0_fx`
         */
        constexpr PSXFixed() : _raw_value(0) {}
        /**
         * @brief Implicit converting constructor from fixed-point integer
         * @details Creates a PSXFixed instance wrapping a raw fixed-point integer,
         * of the kind used by the PlayStation SDK functions.
         * @warning Don't use this for converting plain integers into PSXFixed.
         * Use PSXFixed::from_integer for that.
         * @see PSXFixed::from_integer
         */
        constexpr PSXFixed(UnderlyingType raw_value) : _raw_value(raw_value) {}
        /**
         * @brief Implicit converting constructor from float/double
         * @details Creates a PSXFixed instance with the nearest fixed-point value
         * to the given floating point value.
         * @warning This loses precision.
         * @note Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         * @todo Consider adding a single-precision `float` version of this
         * method for faster emulation when doing runtime conversions on the
         * PlayStation and `double` precision is not needed.
         */
        constexpr PSXFixed(double value) {
            double scaled = value * PSXFixed::SCALE;
            // separate into integer and fraction so we can round the fraction
            UnderlyingType integral = (UnderlyingType)scaled;
            double remainder = scaled - integral;
            // there's no rounding function in the PS1 stdlib so round manually
            if (remainder <= -0.5 or remainder >= 0.5) { // round half to infinity
                integral += (integral < 0 ? -1 : 1);
            }
            this->_raw_value = integral;
        }
        /**
         * @returns a PSXFixed instance representing the closest fixed-point value
         * to the given integer value.
         * @warning Don't use this for converting raw fixed-point integers to PSXFixed.
         * Use PSXFixed::PSXFixed(UnderlyingType) for that.
         * @see PSXFixed::PSXFixed(UnderlyingType)
         * @todo Check for overflow? No exceptions on the PS1...
         */
        static constexpr PSXFixed from_integer(int value) {
            return PSXFixed(value << PSXFixed::FRACTION_BITS);
        }
        /**
         * @brief Implicit cast operator to underlying type
         */
        constexpr operator UnderlyingType() const {
            return this->_raw_value;
        }
        /**
         * @brief Explicit cast operator to double
         * @details Returns exact value of this PSXFixed instance as double-precision floating point
         * @note There is enough precision in double-precision IEEE floats to
         * exactly represent all PSXFixed point values.
         * @note Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        explicit constexpr operator double() const {
            return (double)this->_raw_value / PSXFixed::SCALE;
        }
        /**
         * @brief Explicit cast operator to float
         * @details Returns closest floating point value to this fixed-point
         * value.
         * @warning This loses precision as single-precision floating point cannot
         * represent all possible fixed-point values. Cast to double instead
         * for an exact result.
         * @note Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        explicit constexpr operator float() const {
            // reuse cast to double and then narrow it to float
            return (float)(double)*this;
        }
        /**
         * @returns PSXFixed-point value converted to integer, with fractional part truncated.
         */
        constexpr UnderlyingType to_integer() const {
            // can't use a right-shift here due to it not handling negative values properly
            return this->_raw_value / PSXFixed::SCALE;
        }
        /**
         * @brief Stringifies the PSXFixed-point value to a C-string
         * @details Output is equivalent to `printf()`-family `%.6f`, so trailing zeroes are always displayed
         * @param buffer pointer to array of `char`. Must be non-null and pointing to buffer of size `buffer_size`.
         * @param[out] buffer_size size of `buffer`. Should be at least `15`.
         * @returns `false` if buffer could not be written, because buffer_size wasn't big enough
         * @returns `true` if buffer was written
         * @note Although conforming C-libraries check if `buffer == nullptr` for you, the implementation of `vsnprintf()`
         * in libPSn00bSDK, which this project is intended for use with, doesn't seem to check if `buffer == NULL`, hence
         * the need to check it here.
         * @todo Consider replacing the call to `snprintf()` with a call to
         * `sprintf()` --it looks like the original Sony C library doesn't support
         * `snprintf()`...
         * @todo Consider adding the ability to reduce the number of displayed decimal places, or to remove trailing zeroes
         */
        constexpr bool to_c_str(char* buffer, size_t buffer_size) const {
            // don't write to a null-pointer!
            if (buffer == nullptr) { return false; }
            // need at least 14 characters and 1 for the null-terminator
            if (buffer_size < 15) { return false; } // refuse if not at least this many in buffer
            int decimal_part = this->_raw_value / 4096; // floor-divide
            // decompose the fractional part into an unsigned int to allow us to scale it up for more decimal places
            unsigned int remainder = ((unsigned int)abs(this->_raw_value)) % 4096;
            // 1M is the maximum we can scale it up without overflow, since 4096*1M = 4096M, compared to max uint32 = ~4294M
            unsigned int fractional_part = (remainder * 1'000'000) / 4096; // this gives us 6 decimal places
            // can't print a negative sign if negative but decimal_part is zero
            if (this->_raw_value < 0 and decimal_part == 0) {
                snprintf(buffer, buffer_size, "-0.%06u", fractional_part);
            } else { // otherwise, we can rely on snprintf() to do it for us
                snprintf(buffer, buffer_size, "%d.%06u", decimal_part, fractional_part);
            }
            return true;
        }
        /**
         * @brief Prefix increment operator
         */
        constexpr PSXFixed& operator++() {
            *this += PSXFixed::SCALE;
            return *this;
        }
        /**
         * @brief Prefix decrement operator
         */
        constexpr PSXFixed& operator--() {
            *this -= PSXFixed::SCALE;
            return *this;
        }
        /**
         * @brief Postfix increment operator
         */
        constexpr PSXFixed operator++(int) {
            PSXFixed old = *this; // copy old value
            ++*this; // prefix increment
            return old; // return old value
        }
        /**
         * @brief Postfix decrement operator
         */
        constexpr PSXFixed operator--(int) {
            PSXFixed old = *this; // copy old value
            --*this; // prefix decrement
            return old; // return old value
        }
        /**
         * @brief Compound assignment addition operator
         */
        constexpr PSXFixed& operator +=(const PSXFixed& rhs) {
            this->_raw_value += rhs._raw_value;
            return *this;
        }
        /**
         * @brief Compound assignment subtraction operator
         */
        constexpr PSXFixed& operator -=(const PSXFixed& rhs) {
            this->_raw_value -= rhs._raw_value;
            return *this;
        }
        /**
         * @brief Compound assignment multiplication operator
         * @todo Investigate performance impact of compiler-generated 64-bit
         * multiplication emulation on 32-bit MIPS. If poor performance,
         * consider utilising Lameguy64's suggested implementation using inline
         * assembly to take advantage of the R3000's 64-bit double-word multiply
         * feature.
         */
        constexpr PSXFixed& operator *=(const PSXFixed& rhs) {
            // XXX: no int64_t on PS1, software emulation kicks in automatically
            int64_t result = (int64_t)this->_raw_value * rhs._raw_value;
            // shift back down
            this->_raw_value = (UnderlyingType)(result / PSXFixed::SCALE);
            return *this;
        }
        /**
         * @brief Compound assignment integer multiplication operator
         * @todo Investigate overflow?
         */
        constexpr PSXFixed& operator *=(const UnderlyingType& rhs) {
            this->_raw_value *= rhs;
            return *this;
        }
        /**
         * @brief Compound assignment division operator
         * @todo Investigate performance impact of compiler-generated 64-bit
         * multiplication emulation on 32-bit MIPS. If poor performance,
         * consider utilising Lameguy64's suggested implementation using inline
         * assembly to take advantage of the R3000's 64-bit double-word multiply
         * feature.
         */
        constexpr PSXFixed& operator /=(const PSXFixed& rhs) {
            // XXX: no int64_t on PS1, software emulation kicks in automatically
            int64_t scaled = (int64_t)this->_raw_value * PSXFixed::SCALE;
            this->_raw_value = (UnderlyingType)(scaled / rhs._raw_value);
            return *this;
        }
        /**
         * @brief Compound assignment integer division operator
         * @todo Investigate overflow?
         */
        constexpr PSXFixed& operator /=(const UnderlyingType& rhs) {
            this->_raw_value /= rhs;
            return *this;
        }
        /**
         * @brief Unary minus (negation) operator
         */
        constexpr PSXFixed operator-() const {
            return PSXFixed(-this->_raw_value);
        }
        /**
         * @brief Addition operator
         */
        constexpr friend PSXFixed operator+(PSXFixed lhs, const PSXFixed& rhs) {
            lhs += rhs;
            return lhs;
        }
        /**
         * @brief Subtraction operator
         */
        constexpr friend PSXFixed operator-(PSXFixed lhs, const PSXFixed& rhs) {
            lhs -= rhs;
            return lhs;
        }
        /**
         * @brief Multiplication operator
         */
        constexpr friend PSXFixed operator*(PSXFixed lhs, const PSXFixed& rhs) {
            lhs *= rhs;
            return lhs;
        }
        /**
         * @brief Integer multiplication operator
         */
        constexpr friend PSXFixed operator*(PSXFixed lhs, const UnderlyingType& rhs) {
            lhs *= rhs;
            return lhs;
        }
        /**
         * @brief Integer multiplication operator
         */
        constexpr friend PSXFixed operator*(UnderlyingType lhs, const PSXFixed& rhs) {
            return rhs * lhs;
        }
        /**
         * @brief Division operator
         */
        constexpr friend PSXFixed operator/(PSXFixed lhs, const PSXFixed& rhs) {
            lhs /= rhs;
            return lhs;
        }
        /**
         * @brief Integer division operator
         */
        constexpr friend PSXFixed operator/(PSXFixed lhs, const UnderlyingType& rhs) {
            lhs /= rhs;
            return lhs;
        }

    private:
        UnderlyingType _raw_value;
    };

    template <char... DIGITS>
    constexpr PSXFixed operator"" _fx() {
        // unpack template characters into a char array for ease of access
        char digits[sizeof...(DIGITS)] = {DIGITS...};
        // handle digits before the decimal point first
        PSXFixed integral;
        size_t i = 0;
        for (; i < sizeof...(DIGITS) and digits[i] != '.'; ++i) {
            integral *= PSXFixed::from_integer(10);
            integral += PSXFixed::from_integer(digits[i] - '0');
        }
        // now do the fractional digits
        PSXFixed fractional;
        for (size_t j = sizeof...(DIGITS); j --> i + 1; ) {
            fractional += PSXFixed::from_integer(digits[j] - '0');
            fractional /= PSXFixed::from_integer(10);
        }
        return integral + fractional;
    }

    constexpr PSXFixed operator"" _fx(unsigned long long int literal) {
        return PSXFixed::from_integer((PSXFixed::UnderlyingType)literal);
    }
}

#endif // include guard
