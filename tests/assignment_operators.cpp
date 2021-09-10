#include <functional>
#include <limits>

#include <catch2/catch.hpp>

#include <sxpsxfp/sxpsxfp.hpp>

#include "TestTypes.hpp"


using namespace com::saxbophone::sxpsxfp;

template <typename T>
bool SAME(T lhs, T rhs) {
    if constexpr (std::numeric_limits<T>::is_iec559) {
        return lhs == rhs or (std::isnan(lhs) and std::isnan(rhs));
    } else {
        return lhs == rhs;
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> copy assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType> with this value") {
            sxpsxfp<TestType> sxpsxfp = value;
            REQUIRE(SAME((TestType)sxpsxfp, value));
            AND_GIVEN("Another instance of sxpsxfp<TestType>") {
                sxpsxfp<TestType> other;
                WHEN("The other instance of sxpsxfp<TestType> is assigned the first instance") {
                    other = sxpsxfp;
                    THEN("The other instance is equal to the value when cast to TestType") {
                        CHECK(SAME((TestType)other, value));
                    }
                }
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> move assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType>") {
            sxpsxfp<TestType> sxpsxfp;
            WHEN("The instance is assigned a temporary instance with the value") {
                sxpsxfp = sxpsxfp<TestType>(value);
                THEN("The instance is equal to the value when cast to TestType") {
                    CHECK(SAME((TestType)sxpsxfp, value));
                }
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> addition assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType> with this value") {
            sxpsxfp<TestType> sxpsxfp = value;
            REQUIRE(SAME((TestType)sxpsxfp, value));
            AND_GIVEN("Another random value of type TestType") {
                TestType addend = GENERATE(
                    take(
                        // random values of type TestType
                        RANDOM_TESTS,
                        random(
                            std::numeric_limits<TestType>::lowest(),
                            std::numeric_limits<TestType>::max()
                        )
                    )
                );
                AND_GIVEN("Another instance of sxpsxfp<TestType> with that value") {
                    sxpsxfp<TestType> other = addend;
                    REQUIRE(SAME((TestType)other, addend));
                    WHEN("The other instance of sxpsxfp<TestType> is addition-assigned to the first") {
                        sxpsxfp += other;
                        THEN("The original instance is equal to the sum of value and addend") {
                            CHECK(SAME((TestType)sxpsxfp, (TestType)(value + addend)));
                        }
                    }
                }
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> subtraction assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType> with this value") {
            sxpsxfp<TestType> sxpsxfp = value;
            REQUIRE(SAME((TestType)sxpsxfp, value));
            AND_GIVEN("Another random value of type TestType") {
                TestType subtrahend = GENERATE(
                    take(
                        // random values of type TestType
                        RANDOM_TESTS,
                        random(
                            std::numeric_limits<TestType>::lowest(),
                            std::numeric_limits<TestType>::max()
                        )
                    )
                );
                AND_GIVEN("Another instance of sxpsxfp<TestType> with that value") {
                    sxpsxfp<TestType> other = subtrahend;
                    REQUIRE(SAME((TestType)other, subtrahend));
                    WHEN("The other instance of sxpsxfp<TestType> is addition-assigned to the first") {
                        sxpsxfp -= other;
                        THEN("The original instance is equal to the sum of value and subtrahend") {
                            CHECK(SAME((TestType)sxpsxfp, (TestType)(value - subtrahend)));
                        }
                    }
                }
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> multiplication assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType> with this value") {
            sxpsxfp<TestType> sxpsxfp = value;
            REQUIRE(SAME((TestType)sxpsxfp, value));
            AND_GIVEN("Another random value of type TestType") {
                TestType multiplicand = GENERATE(
                    take(
                        // random values of type TestType
                        RANDOM_TESTS,
                        random(
                            std::numeric_limits<TestType>::lowest(),
                            std::numeric_limits<TestType>::max()
                        )
                    )
                );
                AND_GIVEN("Another instance of sxpsxfp<TestType> with that value") {
                    sxpsxfp<TestType> other = multiplicand;
                    REQUIRE(SAME((TestType)other, multiplicand));
                    WHEN("The other instance of sxpsxfp<TestType> is addition-assigned to the first") {
                        sxpsxfp *= other;
                        THEN("The original instance is equal to the sum of value and multiplicand") {
                            CHECK(SAME((TestType)sxpsxfp, (TestType)(value * multiplicand)));
                        }
                    }
                }
            }
        }
    }
}

TEMPLATE_LIST_TEST_CASE("sxpsxfp<T> division assignment operator", "", TestTypes) {
    GIVEN("A random value of type TestType") {
        // TODO: tweak for better random float generation, as in tr-sort's tests
        TestType value = GENERATE(
            take(
                // random values of type TestType
                RANDOM_TESTS,
                random(
                    std::numeric_limits<TestType>::lowest(),
                    std::numeric_limits<TestType>::max()
                )
            )
        );
        AND_GIVEN("An instance of sxpsxfp<TestType> with this value") {
            sxpsxfp<TestType> sxpsxfp = value;
            REQUIRE(SAME((TestType)sxpsxfp, value));
            AND_GIVEN("Another random value of type TestType") {
                TestType dividend = GENERATE(
                    take(
                        // random values of type TestType
                        RANDOM_TESTS,
                        random(
                            std::numeric_limits<TestType>::lowest(),
                            std::numeric_limits<TestType>::max()
                        )
                    )
                );
                AND_GIVEN("Another instance of sxpsxfp<TestType> with that value") {
                    sxpsxfp<TestType> other = dividend;
                    REQUIRE(SAME((TestType)other, dividend));
                    WHEN("The other instance of sxpsxfp<TestType> is addition-assigned to the first") {
                        sxpsxfp /= other;
                        THEN("The original instance is equal to the sum of value and dividend") {
                            CHECK(SAME((TestType)sxpsxfp, (TestType)(value / dividend)));
                        }
                    }
                }
            }
        }
    }
}
