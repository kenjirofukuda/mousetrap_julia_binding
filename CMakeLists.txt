cmake_minimum_required(VERSION 3.12)

### PROJECT ###

project(mousetrap_julia_binding
    VERSION 0.1.0
    LANGUAGES CXX
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

find_package(JlCxx REQUIRED)
find_package(mousetrap REQUIRED)

set(LIBRARY_NAME mousetrap_julia_binding)

add_library(${LIBRARY_NAME} SHARED
    mousetrap.cpp
)

target_link_libraries(${LIBRARY_NAME} PUBLIC
    ${MOUSETRAP_LIBRARIES}
    JlCxx::cxxwrap_julia
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    "${MOUSETRAP_INCLUDE_DIRECTORIES}"
    "${Julia_INCLUDE_DIRS}"
)

target_compile_features(${LIBRARY_NAME} PUBLIC
    cxx_std_17
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

