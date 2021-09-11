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
#include <cstdint>
#else
#include <sys/types.h>
#endif

namespace com::saxbophone::sxpsxfp {
    class Fixed {
    public:
        using UnderlyingType = int32_t;
        /**
         * @brief Default constructor, creates a Fixed instance with value 0.0
         */
        constexpr Fixed() {}
        /**
         * @brief Implicit converting constructor from fixed-point integer
         * @details Creates a Fixed instance wrapping a raw fixed-point integer,
         * of the kind used by the PlayStation SDK functions.
         * @warning Don't use this for converting plain integers into Fixed
         * @see Fixed::from_integer
         */
        constexpr Fixed(UnderlyingType raw_value) {}
        /**
         * @brief Implicit converting constructor from float/double
         * @details Creates a Fixed instance with the nearest fixed-point value
         * to the given floating point value. This loses precision!
         * @warning Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        constexpr Fixed(double value) {}
        /**
         * @returns a Fixed instance representing the closest fixed-point value
         * to the given integer value.
         * @warning Don't use this for converting raw fixed-point integers to Fixed
         * @see Fixed::Fixed UnderlyingType
         */
        static constexpr Fixed from_integer(int value) {
            return {};
        }
        /**
         * @brief Implicit cast operator to underlying type
         */
        constexpr operator UnderlyingType() const {
            return {};
        }
        /**
         * @brief Explicit cast operator to float/double
         * @details Returns closest floating point value to this fixed-point
         * value. As the precision of single-precision IEEE floats is twice that
         * of this Fixed type, the results should be exact.
         */
        explicit constexpr operator float() const {
            return {};
        }
        /**
         * @returns Fixed-point value converted to integer, with fractional part truncated.
         */
        constexpr UnderlyingType to_integer() const {
            return {};
        }
        /**
         * @brief Compare two Fixed instances for equality
         */
        constexpr friend bool operator==(const Fixed& lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Check if one Fixed instance is less than another
         */
        constexpr friend bool operator<(const Fixed& lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Compare a Fixed instance with UnderlyingType for equality
         */
        constexpr friend bool operator==(const Fixed& lhs, const UnderlyingType& rhs) {
            return {};
        }
        /**
         * @brief Compare a value of UnderlyingType with a Fixed instance for equality
         * @note This overload is unneeded on all compiles (including PS1 mips target) except Clang and MSVC, both of
         * which refuse to substitute the call to the other == operator with swapped operand order. Unclear why this is.
         */
        constexpr friend bool operator==(const UnderlyingType& lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Check if a Fixed instance is less than a value of UnderlyingType
         */
        constexpr friend bool operator<(const Fixed& lhs, const UnderlyingType& rhs) {
            return {};
        }
        /**
         * @brief Check if value of UnderlyingType is less than a Fixed instance
         */
        constexpr friend bool operator<(const UnderlyingType& lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Prefix increment operator
         */
        constexpr Fixed& operator++() {
            return *this;
        }
        /**
         * @brief Prefix decrement operator
         */
        constexpr Fixed& operator--() {
            return *this;
        }
        /**
         * @brief Postfix increment operator
         */
        constexpr Fixed operator++(int) {
            return {};
        }
        /**
         * @brief Postfix decrement operator
         */
        constexpr Fixed operator--(int) {
            return {};
        }
        /**
         * @brief Compound assignment addition operator
         */
        constexpr Fixed& operator +=(const Fixed& rhs) {
            return *this;
        }
        /**
         * @brief Compound assignment subtraction operator
         */
        constexpr Fixed& operator -=(const Fixed& rhs) {
            return *this;
        }
        /**
         * @brief Compound assignment multiplication operator
         */
        constexpr Fixed& operator *=(const Fixed& rhs) {
            return *this;
        }
        /**
         * @brief Compound assignment integer multiplication operator
         */
        constexpr Fixed& operator *=(const UnderlyingType& rhs) {
            return *this;
        }
        /**
         * @brief Compound assignment division operator
         */
        constexpr Fixed& operator /=(const Fixed& rhs) {
            return *this;
        }
        /**
         * @brief Compound assignment integer division operator
         */
        constexpr Fixed& operator /=(const UnderlyingType& rhs) {
            return *this;
        }
        /**
         * @brief Unary minus (negation) operator
         */
        constexpr Fixed operator-() {
            return {};
        }
        /**
         * @brief Addition operator
         */
        constexpr friend Fixed operator+(Fixed lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Subtraction operator
         */
        constexpr friend Fixed operator-(Fixed lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Multiplication operator
         */
        constexpr friend Fixed operator*(Fixed lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Integer multiplication operator
         */
        constexpr friend Fixed operator*(Fixed lhs, const UnderlyingType& rhs) {
            return {};
        }
        /**
         * @brief Division operator
         */
        constexpr friend Fixed operator/(Fixed lhs, const Fixed& rhs) {
            return {};
        }
        /**
         * @brief Integer division operator
         */
        constexpr friend Fixed operator/(Fixed lhs, const UnderlyingType& rhs) {
            return {};
        }

    private:
        UnderlyingType _raw_value;
    };

    /**
     * @brief User-defined literal for Fixed objects with fractional parts
     *
     * @b Usage:
     * @code
     * Fixed full = 123.45_fx;
     * Fixed fractional = .45_fx;
     * @endcode
     */
    constexpr Fixed operator"" _fx(long double literal) {
        return {};
    }
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
     */
    constexpr Fixed operator"" _fx(unsigned long long int literal) {
        return {};
    }
}

#endif // include guard
