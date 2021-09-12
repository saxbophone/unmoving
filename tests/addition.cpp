#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Fixed += Fixed") {
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
    foo += bar;
    REQUIRE((Underlying)foo == i + j);
}

TEST_CASE("Fixed + Fixed") {
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
    Fixed baz = foo + bar;
    REQUIRE((Underlying)baz == i + j);
}
