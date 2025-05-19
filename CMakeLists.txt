# This file is part of AnsiCards.
#
# AnsiCards is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# AnsiCards is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AnsiCards.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright (C) 2025 Dante Doménech Martínez

cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(ansicards VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Settings 
set(SD ${CMAKE_SOURCE_DIR})
set(USE_DEFAULT_JSON $ENV{AC_USE_DEFAULT_JSON})
set(INCLUDE_EXAMPLE $ENV{AC_INCLUDE_EXAMPLE})
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include directories
include_directories(${SD}/includes)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SD}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SD}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SD}/build)

# Setup compilers
if(MSVC)
    # For Microsoft Visual Studio
    add_compile_options(/W4 /O2)
else()
    # For GCC and Clang
    add_compile_options(-Wall -Wextra -O3)
endif()

set(BASE_HEADERS
    ${SD}/includes/ansi.h
    ${SD}/includes/ansi_card_renderer.h
    ${SD}/includes/ansi_card_table.h
    ${SD}/includes/card.h
    ${SD}/includes/card_renderer.h
    ${SD}/includes/card_table.h
    ${SD}/includes/deck.h
    ${SD}/includes/json.h
    ${SD}/includes/number.h
    ${SD}/includes/point.h
    ${SD}/includes/suit.h
)

# List of source files
set(BASE_SOURCES
    ${SD}/src/ansi.cpp
    ${SD}/src/ansi_card_renderer.cpp
    ${SD}/src/ansi_card_table.cpp
    ${SD}/src/card.cpp
    ${SD}/src/card_renderer.cpp
    ${SD}/src/card_table.cpp
    ${SD}/src/deck.cpp
    ${SD}/src/json.cpp
    ${SD}/src/number.cpp
    ${SD}/src/point.cpp
    ${SD}/src/suit.cpp
)

# Deal with the example if INCLUDE_EXAMPLE is "TRUE"
if(INCLUDE_EXAMPLE STREQUAL "TRUE")
    list(APPEND BASE_HEADERS ${SD}/src/example.h)
    list(APPEND BASE_SOURCES ${SD}/src/example.cpp)
endif()

# Create a variable for sources
set(SOURCES ${BASE_SOURCES})

# Add default JSON parser (nlohmann_json)
if(USE_DEFAULT_JSON STREQUAL "TRUE")
    list(APPEND BASE_HEADERS ${SD}/includes/nlohmann_json.h)
    list(APPEND BASE_SOURCES ${SD}/src/nlohmann_json.cpp)
endif()

# Create the executable
add_executable(dbgansicards ${BASE_SOURCES} ${SD}/src/main.cpp)

# Create a static library
add_library(ansicards STATIC ${BASE_SOURCES})
set_target_properties(ansicards PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Deal with the headers
set(HEADERS_OUTPUT "${SD}/build/headersansicards.tar.gz")
add_custom_command(
    OUTPUT ${HEADERS_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E tar czf ${HEADERS_OUTPUT} ${BASE_HEADERS}
    DEPENDS ${BASE_HEADERS}
    COMMENT "Generating tar.gz file from base headers"
)
add_custom_target(generate_headers_tar ALL DEPENDS ${HEADERS_OUTPUT})

# Find the nlohmann/json package without specifying a version
# Link the nlohmann/json library
if(USE_DEFAULT_JSON STREQUAL "TRUE")
    find_package(nlohmann_json REQUIRED)
    target_link_libraries(ansicards nlohmann_json::nlohmann_json)
endif()

# Deal with the example if INCLUDE_EXAMPLE is not "TRUE"
if(NOT INCLUDE_EXAMPLE STREQUAL "TRUE")
    target_sources(dbgansicards PRIVATE ${SD}/src/example.cpp)
endif()

# Release target
add_custom_target(release)
add_dependencies(release ansicards generate_headers_tar)

# Debug symbols
if(MSVC)
    # For Microsoft Visual Studio
    target_compile_options(dbgansicards PRIVATE /Zi)
else()
    # For GCC and Clang
    target_compile_options(dbgansicards PRIVATE -g)
endif()
