#include <catch2/catch.hpp>

#include <sxpsxfp/Fixed.hpp>

using namespace com::saxbophone::sxpsxfp;

TEST_CASE("Full user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, float>({
        {123.45_fx, 123.45f,},
        {123.456789_fx, 123.456789f,},
        {-0.317282_fx, -0.317282f,},
        {-456128.33937921009_fx, -456128.33937921009f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    REQUIRE((float)foo == std::get<float>(literal_to_value));
}

TEST_CASE("Fractional user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, float>({
        {.45_fx, .45f,},
        {.456789_fx, .456789f,},
        {-.317282_fx, -.317282f,},
        {-.33937921009_fx, -.33937921009f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    REQUIRE((float)foo == std::get<float>(literal_to_value));
}

TEST_CASE("Integral user-defined literal") {
    auto literal_to_value = GENERATE(table<Fixed, float>({
        {12345_fx, 12345.0f,},
        {123456_fx, 123456.0f,},
        {-317282_fx, -317282.0f,},
        {-456128_fx, -456128.0f,},
    }));
    Fixed foo = std::get<Fixed>(literal_to_value);
    REQUIRE((float)foo == std::get<float>(literal_to_value));
}
