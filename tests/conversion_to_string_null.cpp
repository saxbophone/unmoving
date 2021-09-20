#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Fixed.to_c_str() returns false when buffer is a null pointer") {
    Fixed var;

    // should fail because of null pointer and not buffer_size, the latter of which is big enough
    REQUIRE_FALSE(var.to_c_str(nullptr, 15));
}
