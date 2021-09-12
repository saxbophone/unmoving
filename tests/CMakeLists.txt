CPMFindPackage(
    NAME Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.4
    EXCLUDE_FROM_ALL YES
)

add_executable(tests)
target_sources(
    tests
    PRIVATE
        main.cpp
        addition.cpp
        casting.cpp
        comparisons.cpp
        constructors.cpp
        division.cpp
        equivalences.cpp
        multiplication.cpp
        subtraction.cpp
        unary_operations.cpp
        user_defined_literals.cpp
)
target_link_libraries(
    tests
    PRIVATE
        sxpsxfp-compiler-options  # tests use same compiler options as main project
        sxpsxfp
        Catch2::Catch2             # unit testing framework
)

enable_testing()

# auto-discover and add Catch2 tests from unit tests program
include(CTest)
include(Catch)

catch_discover_tests(tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
