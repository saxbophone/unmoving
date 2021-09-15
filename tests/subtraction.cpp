#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;
using Underlying = Fixed::UnderlyingType;

TEST_CASE("Subtraction") {
    Underlying i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                std::numeric_limits<Underlying>::min(),
                std::numeric_limits<Underlying>::max()
            )
        )
    );
    // pick second operand carefully to avoid signed underflow UB
    Underlying j = GENERATE_COPY(
        take(
            1,
            filter(
                [=](Underlying u) {
                    auto sum = ((std::int64_t)i - u);
                    return std::numeric_limits<Underlying>::min() <= sum and
                        sum <= std::numeric_limits<Underlying>::max();
                },
                random(
                    std::numeric_limits<Underlying>::min(),
                    std::numeric_limits<Underlying>::max()
                )
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);

    SECTION("Fixed -= Fixed") {
        double foo_f = (double)foo, bar_f = (double)bar;
        // allowed to deviate up to the smallest step in the fixed-point representation
        auto expected_result = Approx(foo_f - bar_f).margin(Fixed::ACCURACY);
        CHECK((double)(foo -= bar) == expected_result);
        REQUIRE((double)foo == expected_result);
    }

    SECTION("Fixed - Fixed") {
        double foo_f = (double)foo, bar_f = (double)bar;
        Fixed baz = foo - bar;
        // allowed to deviate up to the smallest step in the fixed-point representation
        REQUIRE((double)baz == Approx(foo_f - bar_f).margin(Fixed::ACCURACY));
    }
}
