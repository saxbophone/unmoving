#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Fixed == Fixed") {
    Fixed foo, bar;
    bool equal = foo == bar;
    SUCCEED();
}

TEST_CASE("Fixed != Fixed") {
    Fixed foo, bar;
    bool unequal = foo != bar;
    SUCCEED();
}

// TEST_CASE("Fixed == UnderlyingType") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool equal = foo == bar;
//     SUCCEED();
// }

// TEST_CASE("Fixed != UnderlyingType") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool unequal = foo != bar;
//     SUCCEED();
// }

// TEST_CASE("UnderlyingType == Fixed") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool equal = bar == foo;
//     SUCCEED();
// }

// TEST_CASE("UnderlyingType != Fixed") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool unequal = bar != foo;
//     SUCCEED();
// }

TEST_CASE("Fixed < Fixed") {
    Fixed foo, bar;
    bool less = foo < bar;
    SUCCEED();
}

TEST_CASE("Fixed > Fixed") {
    Fixed foo, bar;
    bool greater = foo > bar;
    SUCCEED();
}

// TEST_CASE("Fixed < UnderlyingType") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool less = foo < bar;
//     SUCCEED();
// }

// TEST_CASE("Fixed > UnderlyingType") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool greater = foo > bar;
//     SUCCEED();
// }

// TEST_CASE("UnderlyingType < Fixed") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool less = bar < foo;
//     SUCCEED();
// }

// TEST_CASE("UnderlyingType > Fixed") {
//     Fixed foo;
//     Fixed::UnderlyingType bar;
//     bool greater = bar > foo;
//     SUCCEED();
// }
