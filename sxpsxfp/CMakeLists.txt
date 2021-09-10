include(GNUInstallDirs)

add_library(sxpsxfp STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(SxPsxFp::sxpsxfp ALIAS sxpsxfp)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(
    sxpsxfp PUBLIC
    # different include directory path depending on if using the local or installed version of library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    sxpsxfp PRIVATE
    -DSXPSXFP_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DSXPSXFP_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DSXPSXFP_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DSXPSXFP_VERSION_STRING=${SXPSXFP_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    sxpsxfp PROPERTIES
    VERSION ${SXPSXFP_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_sxpsxfp_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_sxpsxfp_MINOR_VERSION ${PROJECT_VERSION_MINOR}
)
set_property(
    TARGET sxpsxfp
    APPEND PROPERTY COMPATIBLE_INTERFACE_STRING "${SxPsxFp_MAJOR_VERSION}.${SxPsxFp_MINOR_VERSION}"
)
# inherit common project compiler options
target_link_libraries(
    sxpsxfp
        PRIVATE
            $<BUILD_INTERFACE:sxpsxfp-compiler-options>
)

# install if we're not being built as a sub-project
if (NOT SXPSXFP_SUBPROJECT)
    # library
    install(
        TARGETS sxpsxfp
        EXPORT SxPsxFpTargets
        # when a static library
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # when a shared library on UNIX
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        # when a DLL on Windows
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    # public headers
    install(
        DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    # CMake export
    install(
        EXPORT SxPsxFpTargets
        FILE SxPsxFpTargets.cmake
        NAMESPACE SxPsxFp::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SxPsxFp"
    )
    # CMake package
    include(CMakePackageConfigHelpers)
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/SxPsxFpConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SxPsxFp"
    )
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/SxPsxFpConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY SameMinorVersion
    )
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/SxPsxFpConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/SxPsxFpConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SxPsxFp"
    )
endif()
