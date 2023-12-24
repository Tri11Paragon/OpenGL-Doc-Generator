cmake_minimum_required(VERSION 3.25)
project(gl_doc_generator VERSION 0.0.1 LANGUAGES CXX)

option(ENABLE_ADDRSAN "Enable the address sanitizer" OFF)
option(ENABLE_UBSAN "Enable the ub sanitizer" OFF)
option(ENABLE_TSAN "Enable the thread data race sanitizer" OFF)

set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
endif ()
message("Using ${CMAKE_BUILD_TYPE}")

add_subdirectory(libraries/BLT)

file(COPY ${CMAKE_SOURCE_DIR}/gl_doc_generator.py DESTINATION ${CMAKE_BINARY_DIR}/)

include_directories(include/)
file(GLOB_RECURSE PROJECT_BUILD_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(gl_doc_generator ${PROJECT_BUILD_FILES})

target_compile_options(gl_doc_generator PRIVATE -Wall -Wextra -Werror -Wpedantic -Wno-comment)
target_link_options(gl_doc_generator PRIVATE -Wall -Wextra -Werror -Wpedantic -Wno-comment)

target_link_libraries(gl_doc_generator PUBLIC BLT)

if (${ENABLE_ADDRSAN} MATCHES ON)
    target_compile_options(gl_doc_generator PRIVATE -fsanitize=address)
    target_link_options(gl_doc_generator PRIVATE -fsanitize=address)
endif ()

if (${ENABLE_UBSAN} MATCHES ON)
    target_compile_options(gl_doc_generator PRIVATE -fsanitize=undefined)
    target_link_options(gl_doc_generator PRIVATE -fsanitize=undefined)
endif ()

if (${ENABLE_TSAN} MATCHES ON)
    target_compile_options(gl_doc_generator PRIVATE -fsanitize=thread)
    target_link_options(gl_doc_generator PRIVATE -fsanitize=thread)
endif ()