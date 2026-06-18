cmake_minimum_required(VERSION 3.5)

project(my_allocator  VERSION 1.0.0)
add_executable(my_allocator my_allocator.cpp)

set_target_properties(my_allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if (MSVC)
    target_compile_options(my_allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(my_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
    target_compile_options(my_allocator PRIVATE /W4)
else ()
    target_compile_options(my_allocator PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in" 
    "${CMAKE_BINARY_DIR}/version.h"          
)
target_include_directories(my_allocator PRIVATE "${CMAKE_BINARY_DIR}")