cmake_minimum_required (VERSION 3.31)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API YES)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

project(Spellrite DESCRIPTION "A modern C++ file-explorer" VERSION 1.0.0 LANGUAGES CXX)

# Deps
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Qml)
qt_standard_project_setup(REQUIRES 6.8)

# Executable
qt_add_executable(hermes)
set_property(TARGET hermes PROPERTY CMAKE_CXX_STANDARD 23)
target_compile_features(hermes PUBLIC cxx_std_23)
target_include_directories(hermes PUBLIC src/)

# Deps
find_package(spdlog REQUIRED)
target_link_libraries(hermes
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
    spdlog::spdlog
)

# Sources
file(GLOB_RECURSE hermesSources
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        )
file(GLOB_RECURSE hermesModules
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm"
)
file(GLOB_RECURSE hermesQML
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.qml"
)
file(GLOB_RECURSE hermesResources
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/*"
)
qt_add_qml_module(hermes
    URI Hermes
    VERSION 1.0
    QML_FILES
    ${hermesQML}
    RESOURCES
    ${hermesResources}
    NO_IMPORT_SCAN
)

target_sources(hermes
  PRIVATE
  ${hermesSources}
  ${hermesModules}
  PUBLIC
    FILE_SET CXX_MODULES
    FILES
    ${hermesModules}
)

# install
install(TARGETS hermes DESTINATION bin)

# compiler definitions
if(WIN32)
    target_compile_definitions(hermes PUBLIC HERMES_PLATFORM_WIN)
    message( FATAL_ERROR "Windows is not yet supported!" )
elseif(APPLE)
target_compile_definitions(hermes PUBLIC HERMES_PLATFORM_APPLE)
    message( FATAL_ERROR "Windows is not yet supported!" )
elseif(UNIX)
target_compile_definitions(hermes PUBLIC HERMES_PLATFORM_LINUX)
endif()
