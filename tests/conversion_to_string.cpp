#include <limits>

#include <cstdlib>

#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

#include "config.hpp"

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Conversion to String") {
    SECTION("Fixed.to_c_str() creates a C string with the value's decimal respresentation") {
        double i = GENERATE(
            take(
                tests_config::ITERATIONS,
                random(
                    Fixed::FRACTIONAL_MIN,
                    Fixed::FRACTIONAL_MAX
                )
            )
        );
        Fixed var = i;
        char output[16] = {}; // need up to 16 characters for string, including null-terminator

        // we require the function call to return true for successful call
        CHECK(var.to_c_str(output, sizeof(output)));
        // now, try and convert that value back to double so we can approximately compare it
        char* cursor = nullptr;
        double value = std::strtod(output, &cursor);
        // strtod sets cursor to output if conversion failed, so check that it isn't
        REQUIRE(cursor != output);

        // finally, approximately compare this value cast to double
        REQUIRE(value == Approx((double)var).margin(Fixed::ACCURACY));
    }
}
