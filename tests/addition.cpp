#include <limits>

#include <cmath>
#include <cstdint>

#include <catch2/catch.hpp>

#include <unmoving/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::unmoving;
using Underlying = Fixed::UnderlyingType;

// calculated propagated accuracy error after an addition
constexpr double ACCURACY = Fixed::ACCURACY * 2.0;

TEST_CASE("Addition") {
    double i = GENERATE(
        take(
            tests_config::ITERATIONS,
            random(
                Fixed::FRACTIONAL_MIN,
                Fixed::FRACTIONAL_MAX
            )
        )
    );
    // pick second operand carefully to avoid signed overflow UB
    double j = GENERATE_COPY(
        take(
            1,
            filter(
                [=](double u) {
                    auto sum = i + u;
                    return Fixed::FRACTIONAL_MIN <= sum and
                        sum <= Fixed::FRACTIONAL_MAX;
                },
                random(
                    Fixed::FRACTIONAL_MIN,
                    Fixed::FRACTIONAL_MAX
                )
            )
        )
    );
    Fixed foo(i);
    Fixed bar(j);
    // use calculated accuracy to set the margin of error
    auto expected_result = Approx(i + j).margin(ACCURACY);

    SECTION("Fixed += Fixed") {
        CHECK((double)(foo += bar) == expected_result);
        REQUIRE((double)foo == expected_result);
    }

    SECTION("Fixed + Fixed") {
        Fixed baz = foo + bar;
        REQUIRE((double)baz == expected_result);
    }
}
