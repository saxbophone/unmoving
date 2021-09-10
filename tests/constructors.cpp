#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Default constructor can be called") {
    Fixed foo;
    SUCCEED();
}
