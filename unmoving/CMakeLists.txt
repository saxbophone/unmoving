include(GNUInstallDirs)

add_library(unmoving STATIC)
# ALIAS target to export a namespaced target even when building in-tree
add_library(Unmoving::unmoving ALIAS unmoving)
# add source files
add_subdirectory(src)
# library public header files location
target_include_directories(
    unmoving PUBLIC
    # different include directory path depending on if using the local or installed version of library
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
# pass in version of project as preprocessor definitions
target_compile_definitions(
    unmoving PRIVATE
    -DUNMOVING_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DUNMOVING_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DUNMOVING_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    -DUNMOVING_VERSION_STRING=${UNMOVING_ESCAPED_VERSION_STRING}
)
# set up version and soversion for the main library object
set_target_properties(
    unmoving PROPERTIES
    VERSION ${UNMOVING_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_unmoving_MAJOR_VERSION ${PROJECT_VERSION_MAJOR}
    INTERFACE_unmoving_MINOR_VERSION ${PROJECT_VERSION_MINOR}
)
set_property(
    TARGET unmoving
    APPEND PROPERTY COMPATIBLE_INTERFACE_STRING "${Unmoving_MAJOR_VERSION}.${Unmoving_MINOR_VERSION}"
)
# inherit common project compiler options
target_link_libraries(
    unmoving
        PRIVATE
            $<BUILD_INTERFACE:unmoving-compiler-options>
)

# install if we're not being built as a sub-project
if (NOT UNMOVING_SUBPROJECT)
    # library
    install(
        TARGETS unmoving
        EXPORT UnmovingTargets
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
        EXPORT UnmovingTargets
        FILE UnmovingTargets.cmake
        NAMESPACE Unmoving::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Unmoving"
    )
    # CMake package
    include(CMakePackageConfigHelpers)
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/UnmovingConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Unmoving"
    )
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/UnmovingConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY SameMinorVersion
    )
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/UnmovingConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/UnmovingConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Unmoving"
    )
endif()
