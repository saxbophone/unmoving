CPMFindPackage(
    NAME Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10
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
        conversion_to_string.cpp
        conversion_to_string_null.cpp
        division.cpp
        equivalences.cpp
        multiplication.cpp
        static_checks.cpp
        subtraction.cpp
        unary_operations.cpp
        user_defined_literals.cpp
)
# disable check for null buffer to vsnprintf() family functions for one file,
# which needs to deliberately pass a null-pointer as part of the test case
check_cxx_compiler_flag("-Wno-format-truncation" flag_supported)
if(flag_supported)
    set_source_files_properties(
        conversion_to_string_null.cpp
        PROPERTIES COMPILE_FLAGS -Wno-format-truncation
    )
endif()
unset(flag_supported CACHE)
target_link_libraries(
    tests
    PRIVATE
        unmoving-compiler-options  # use custom compiler options
        unmoving
        Catch2::Catch2             # unit testing framework
)

enable_testing()

# auto-discover and add Catch2 tests from unit tests program
include(CTest)
include(Catch)

catch_discover_tests(tests WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
