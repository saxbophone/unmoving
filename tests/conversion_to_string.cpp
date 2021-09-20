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
        char output[15] = {}; // need up to 15 characters for string, including null-terminator

        // we require the function call to return true for successful call
        CHECK(var.to_c_str(output, sizeof(output)));
        // now, try and convert that value back to double so we can approximately compare it
        char* cursor = nullptr;
        double value = std::strtod(output, &cursor);
        // strtod sets cursor to output if conversion failed, so check that it isn't
        REQUIRE(cursor != output);

        // finally, approximately compare this value cast to double --we want them equal to 6 decimal places
        REQUIRE(value == Approx((double)var).margin(0.000001));
    }

    SECTION("Fixed.to_c_str() returns false when given buffer_size = zero") {
        Fixed var;
        char output = {};

        REQUIRE_FALSE(var.to_c_str(&output, 0));
    }

    SECTION("Fixed.to_c_str() returns false when 1 ≤ buffer_size < 15") {
        std::size_t buffer_size = GENERATE(range(1U, 14U));
        Fixed var;
        char* output = new char[buffer_size] {0};

        REQUIRE_FALSE(var.to_c_str(output, buffer_size));
    }

    SECTION("Fixed.to_c_str() returns false when buffer is a null pointer") {
        Fixed var;

        #pragma GCC diagnostic push
        #pragma GCC diagnostic warning "-Wformat-truncation=0"
        // should fail because of null pointer and not buffer_size, the latter of which is big enough
        REQUIRE_FALSE(var.to_c_str(nullptr, 15));
        #pragma GCC diagnostic pop
    }
}
