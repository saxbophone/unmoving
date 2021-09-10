#include <sxpsxfp/Fixed.hpp>


namespace com::saxbophone::sxpsxfp {
    constexpr Fixed::Fixed() {}

    constexpr Fixed::Fixed(UnderlyingType) {}

    constexpr Fixed::Fixed(double) {}

    constexpr Fixed Fixed::from_integer(int) {
        return {};
    }

    constexpr Fixed::operator UnderlyingType() const {
        return {};
    }

    constexpr Fixed::operator float() const {
        return {};
    }
}
