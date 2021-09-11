#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Full user-defined literal") {
    Fixed foo = 123.45_fx;
    SUCCEED();
}

TEST_CASE("Fractional user-defined literal") {
    Fixed foo = .45_fx;
    SUCCEED();
}

TEST_CASE("Integral user-defined literal") {
    Fixed foo = 123_fx;
    SUCCEED();
}
