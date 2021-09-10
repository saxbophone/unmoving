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
        constexpr Fixed();
        /**
         * @brief Implicit converting constructor from fixed-point integer
         * @details Creates a Fixed instance wrapping a raw fixed-point integer,
         * of the kind used by the PlayStation SDK functions.
         * @warning Don't use this for converting plain integers into Fixed
         * @see Fixed::from_integer
         */
        constexpr Fixed(UnderlyingType raw_value);
        /**
         * @brief Implicit converting constructor from float/double
         * @details Creates a Fixed instance with the nearest fixed-point value
         * to the given floating point value. This loses precision!
         * @warning Not recommended to use this outside of constexpr contexts
         * where avoidable on the PlayStation, as the console has no hardware
         * floating point support, so slow software floats will be used.
         */
        constexpr Fixed(double value);
        /**
         * @returns a Fixed instance representing the closest fixed-point value
         * to the given integer value.
         * @warning Don't use this for converting raw fixed-point integers to Fixed
         * @see Fixed::Fixed UnderlyingType
         */
        static constexpr Fixed from_integer(int value);
        /**
         * @brief Implicit cast operator to underlying type
         */
        constexpr operator UnderlyingType() const;
        /**
         * @brief Implicit cast operator to float/double
         * @details Returns closest floating point value to this fixed-point
         * value. As the precision of single-precision IEEE floats is twice that
         * of this Fixed type, the results should be exact.
         */
        constexpr operator float() const;
        /**
         * @brief Defaulted three-way comparison operator
         */
        friend auto operator<=>(const Fixed&, const Fixed&) = default;
        /**
         * @brief Prefix increment operator
         */
        constexpr Fixed& operator++();
        /**
         * @brief Prefix decrement operator
         */
        constexpr Fixed& operator--();
        /**
         * @brief Postfix increment operator
         */
        constexpr Fixed operator++(int);
        /**
         * @brief Postfix decrement operator
         */
        constexpr Fixed operator--(int);
        /**
         * @brief Compound assignment addition operator
         */
        constexpr Fixed& operator +=(const Fixed& rhs);
        /**
         * @brief Compound assignment subtraction operator
         */
        constexpr Fixed& operator -=(const Fixed& rhs);
        /**
         * @brief Compound assignment multiplication operator
         */
        constexpr Fixed& operator *=(const Fixed& rhs);
        /**
         * @brief Compound assignment division operator
         */
        constexpr Fixed& operator /=(const Fixed& rhs);
        /**
         * @brief Unary minus (negation) operator
         */
        constexpr Fixed& operator-();
        /**
         * @brief Addition operator
         */
        constexpr friend Fixed operator+(Fixed lhs, const Fixed& rhs);
        /**
         * @brief Subtraction operator
         */
        constexpr friend Fixed operator-(Fixed lhs, const Fixed& rhs);
        /**
         * @brief Multiplication operator
         */
        constexpr friend Fixed operator*(Fixed lhs, const Fixed& rhs);
        /**
         * @brief Division operator
         */
        constexpr friend Fixed operator/(Fixed lhs, const Fixed& rhs);

    private:
        static constexpr const UnderlyingType ONE = 4096;

        UnderlyingType _raw_value;
    };
}

#endif // include guard
