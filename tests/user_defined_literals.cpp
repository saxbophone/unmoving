#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

/*
 * NOTE: we shouldn't test any negative literals here, because this would be
 * testing the unary minus operator as well. Negative literals in C++ are
 * actually positive literals with the unary minus operator applied to them, so
 * there are no "true" negative integer literals.
 */

TEST_CASE("Full user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, double>({
        {123.45_fx, 123.45f,},
        {123.456789_fx, 123.456789f,},
        {0.317282_fx, 0.317282f,},
        {456128.33937921009_fx, 456128.33937921009f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    CAPTURE(std::get<Fixed>(literal_to_value), std::get<double>(literal_to_value));
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(1.0 / 4096));
}

TEST_CASE("Fractional user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, double>({
        {.45_fx, .45f,},
        {.456789_fx, .456789f,},
        {.317282_fx, .317282f,},
        {.33937921009_fx, .33937921009f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(1.0 / 4096));
}

TEST_CASE("Integral user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, double>({
        {12345_fx, 12345.0f,},
        {123456_fx, 123456.0f,},
        {317282_fx, 317282.0f,},
        {456128_fx, 456128.0f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    // allowed to deviate up to the smallest step in the fixed-point representation
    REQUIRE((double)foo == Approx(std::get<double>(literal_to_value)).margin(1.0 / 4096));
}
