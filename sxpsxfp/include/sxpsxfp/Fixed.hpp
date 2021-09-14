/**
 * @file
 * This file forms part of sxpsxfp
 *
 * @author Joshua Saxby <joshua.a.saxby@gmail.com>
 * @date September 2021
 *
 * @copyright Copyright Joshua Saxby <joshua.a.saxby@gmail.com> 2021
 *
 * @copyright
 * This is closed-source software and may not be used in any way without the
 * express written permission of the copyright holder. All rights reserved.
 */

#ifndef COM_SAXBOPHONE_SXPSXFP_SXPSXFP_HPP
#define COM_SAXBOPHONE_SXPSXFP_SXPSXFP_HPP

// NOTE: Blindly assuming that the PS1 environment declares itself as a freestanding implementation for this check!
#if __STDC_HOSTED__
#include <cstddef>
#include <cstdint>
#else
#include <sys/types.h>
#endif

#include <limits>

namespace com::saxbophone::sxpsxfp {
    class Fixed; // forward-declaration to allow declaration of user-defined literals

    /**
     * @brief User-defined literal for Fixed objects with fractional parts
     *
     * @b Usage:
     * @code
     * Fixed full = 123.45_fx;
     * Fixed fractional = .45_fx;
     * @endcode
     * @relatedalso Fixed
     */
    constexpr Fixed operator"" _fx(long double literal);

    /**
     * @brief User-defined literal for Fixed objects without fractional parts
     *
     * @b Usage:
     * @code
     * Fixed integral = 123_fx;
     * @endcode
     * @warning Use this to initialise Fixed objects when the intention is
     * to hold the same value as the integer. Use regular integer literals
     * when the intention is to interpret the integer as a fixed-point value
     * (this is the fixed-point equivalent of initialising a float from raw
     * memory values).
     * @relatedalso Fixed
     */
    constexpr Fixed operator"" _fx(unsigned long long int literal);

    /**
     * @brief Fixed-point arithmetic value type for Sony PlayStation
     * @details Wraps the native 32-bit integers used on the platform for fixed
     * point arithmetic and allows arithmetic operations to be done on these
     * instances directly, handling the additional arithmetic for emulating
     * fixed-point internally.
     */
    class Fixed {
    public:
        using UnderlyingType = int32_t;
        static constexpr size_t FRACTION_BITS = 12;
        static constexpr size_t DECIMAL_BITS = 19;
        static constexpr UnderlyingType SCALE = 1 << Fixed::FRACTION_BITS;
        static constexpr double FRACTIONAL_STEP = 1.0 / Fixed::SCALE;
        static constexpr UnderlyingType DECIMAL_MAX = (1 << Fixed::DECIMAL_BITS) - 1;
        static constexpr UnderlyingType DECIMAL_MIN = -(1 << Fixed::DECIMAL_BITS);
        static constexpr double FRACTIONAL_MAX = Fixed::DECIMAL_MAX + (1.0 - Fixed::FRACTIONAL_STEP);
        static constexpr double FRACTIONAL_MIN = Fixed::DECIMAL_MIN - (1.0 - Fixed::FRACTIONAL_STEP);
        /**
         * @brief Default constructor, creates a Fixed instance with value `0.0_fx`
         */
        constexpr Fixed() : _raw_value(0) {}
        /**
         * @brief Implicit converting constructor from fixed-point integer
         * @details Creates a Fixed instance wrapping a raw fixed-point integer,
         * of the kind used by the PlayStation SDK functions.
         * @warning Don't use this for converting plain integers into Fixed.
         * Use Fixed::from_integer for that.
         * @see Fixed::from_integer
         */
        constexpr Fixed(UnderlyingType raw_value) : _raw_value(raw_value) {}
        /**
         * @brief Implicit converting constructor from float/double
         * @details Creates a Fixed instance with the nearest fixed-point value
         * to the given floating point value.
         * @warning This loses precision.
         * @note Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        constexpr Fixed(double value) {
            double scaled = value * Fixed::SCALE;
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
         * @returns a Fixed instance representing the closest fixed-point value
         * to the given integer value.
         * @warning Don't use this for converting raw fixed-point integers to Fixed.
         * Use Fixed::Fixed(UnderlyingType) for that.
         * @see Fixed::Fixed(UnderlyingType)
         */
        static constexpr Fixed from_integer(int value) {
            // TODO: Check for overflow? No exceptions on the PS1...
            return Fixed(value << Fixed::FRACTION_BITS);
        }
        /**
         * @brief Implicit cast operator to underlying type
         */
        constexpr operator UnderlyingType() const {
            return this->_raw_value;
        }
        /**
         * @brief Explicit cast operator to double
         * @details Returns exact value of this Fixed instance as double-precision floating point
         * @note There is enough precision in double-precision IEEE floats to
         * exactly represent all Fixed point values.
         * @note Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        explicit constexpr operator double() const {
            // return (double)this->_raw_value / Fixed::SCALE;
            return std::numeric_limits<double>::quiet_NaN(); // NaN doesn't compare equal to itself
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
            // return (float)(double)*this;
            return std::numeric_limits<float>::quiet_NaN(); // NaN doesn't compare equal to itself
        }
        /**
         * @returns Fixed-point value converted to integer, with fractional part truncated.
         */
        constexpr UnderlyingType to_integer() const {
            // can't use a right-shift here due to it not handling negative values properly
            return this->_raw_value / Fixed::SCALE;
        }
        /**
         * @brief Prefix increment operator
         */
        constexpr Fixed& operator++() {
            *this += Fixed::SCALE;
            return *this;
        }
        /**
         * @brief Prefix decrement operator
         */
        constexpr Fixed& operator--() {
            *this -= Fixed::SCALE;
            return *this;
        }
        /**
         * @brief Postfix increment operator
         */
        constexpr Fixed operator++(int) {
            Fixed old = *this; // copy old value
            ++*this; // prefix increment
            return old; // return old value
        }
        /**
         * @brief Postfix decrement operator
         */
        constexpr Fixed operator--(int) {
            Fixed old = *this; // copy old value
            --*this; // prefix decrement
            return old; // return old value
        }
        /**
         * @brief Compound assignment addition operator
         */
        constexpr Fixed& operator +=(const Fixed& rhs) {
            this->_raw_value += rhs._raw_value;
            return *this;
        }
        /**
         * @brief Compound assignment subtraction operator
         */
        constexpr Fixed& operator -=(const Fixed& rhs) {
            this->_raw_value -= rhs._raw_value;
            return *this;
        }
        /**
         * @brief Compound assignment multiplication operator
         */
        constexpr Fixed& operator *=(const Fixed& rhs) {
            // XXX: no int64_t on PS1, needs rewrite to run on that platform
            int64_t result = (int64_t)this->_raw_value * rhs._raw_value;
            // shift back down
            this->_raw_value = (UnderlyingType)(result / Fixed::SCALE);
            return *this;
        }
        /**
         * @brief Compound assignment integer multiplication operator
         */
        constexpr Fixed& operator *=(const UnderlyingType& rhs) {
            this->_raw_value *= rhs;
            return *this;
        }
        /**
         * @brief Compound assignment division operator
         */
        constexpr Fixed& operator /=(const Fixed& rhs) {
            // XXX: no int64_t on PS1, needs rewrite to run on that platform
            int64_t scaled = (int64_t)this->_raw_value * Fixed::SCALE;
            this->_raw_value = (UnderlyingType)(scaled / rhs._raw_value);
            return *this;
        }
        /**
         * @brief Compound assignment integer division operator
         */
        constexpr Fixed& operator /=(const UnderlyingType& rhs) {
            this->_raw_value /= rhs;
            return *this;
        }
        /**
         * @brief Unary minus (negation) operator
         */
        constexpr Fixed operator-() const {
            return Fixed(-this->_raw_value);
        }
        /**
         * @brief Addition operator
         */
        constexpr friend Fixed operator+(Fixed lhs, const Fixed& rhs) {
            lhs += rhs;
            return lhs;
        }
        /**
         * @brief Subtraction operator
         */
        constexpr friend Fixed operator-(Fixed lhs, const Fixed& rhs) {
            lhs -= rhs;
            return lhs;
        }
        /**
         * @brief Multiplication operator
         */
        constexpr friend Fixed operator*(Fixed lhs, const Fixed& rhs) {
            lhs *= rhs;
            return lhs;
        }
        /**
         * @brief Integer multiplication operator
         */
        constexpr friend Fixed operator*(Fixed lhs, const UnderlyingType& rhs) {
            lhs *= rhs;
            return lhs;
        }
        /**
         * @brief Division operator
         */
        constexpr friend Fixed operator/(Fixed lhs, const Fixed& rhs) {
            lhs /= rhs;
            return lhs;
        }
        /**
         * @brief Integer division operator
         */
        constexpr friend Fixed operator/(Fixed lhs, const UnderlyingType& rhs) {
            lhs /= rhs;
            return lhs;
        }

    private:
        UnderlyingType _raw_value;
    };

    constexpr Fixed operator"" _fx(long double literal) {
        return Fixed((double)literal);
    }

    constexpr Fixed operator"" _fx(unsigned long long int literal) {
        return Fixed::from_integer((Fixed::UnderlyingType)literal);
    }
}

#endif // include guard
