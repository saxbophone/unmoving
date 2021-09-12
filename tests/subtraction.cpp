#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed -= Fixed") {
    // use half of range for both operands to avoid signed overflow UB
    Underlying i = GENERATE(
        take(
            10,
            random(
                std::numeric_limits<Underlying>::min() / 2,
                std::numeric_limits<Underlying>::max() / 2
            )
        )
    );
    Underlying j = GENERATE(
        take(
            10,
            random(
                std::numeric_limits<Underlying>::min() / 2,
                std::numeric_limits<Underlying>::max() / 2
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);
    double foo_f = (double)foo, bar_f = (double)bar;
    foo -= bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == Approx(foo_f - bar_f).margin(Fixed::FRACTIONAL_STEP));
}

TEST_CASE("Fixed - Fixed") {
    // use half of range for both operands to avoid signed overflow UB
    Underlying i = GENERATE(
        take(
            10,
            random(
                std::numeric_limits<Underlying>::min() / 2,
                std::numeric_limits<Underlying>::max() / 2
            )
        )
    );
    Underlying j = GENERATE(
        take(
            10,
            random(
                std::numeric_limits<Underlying>::min() / 2,
                std::numeric_limits<Underlying>::max() / 2
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);
    double foo_f = (double)foo, bar_f = (double)bar;
    Fixed baz = foo - bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)baz == Approx(foo_f - bar_f).margin(Fixed::FRACTIONAL_STEP));
}
