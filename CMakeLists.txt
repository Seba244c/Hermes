cmake_minimum_required (VERSION 3.31)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API YES)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Spellrite DESCRIPTION "A modern C++ file-explorer" VERSION 1.0.0 LANGUAGES CXX)

# Deps
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Qml)
qt_standard_project_setup(REQUIRES 6.8)

# Executable
qt_add_executable(hermes)
set_property(TARGET hermes PROPERTY CMAKE_CXX_STANDARD 23)
target_compile_features(hermes PUBLIC cxx_std_23)
target_link_libraries(hermes
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
)

# QML Source


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
        "src/*.qml"
)
qt_add_qml_module(hermes
    URI Hermes
    VERSION 1.0
    QML_FILES
    ${hermesQML}
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
