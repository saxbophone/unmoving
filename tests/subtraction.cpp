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
    float foo_f = (float)foo, bar_f = (float)bar;
    foo -= bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((float)foo == Approx(foo_f - bar_f).margin(1.0 / 4096));
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
    float foo_f = (float)foo, bar_f = (float)bar;
    Fixed baz = foo - bar;
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((float)baz == Approx(foo_f - bar_f).margin(1.0 / 4096));
}
