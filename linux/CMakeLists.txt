cmake_minimum_required(VERSION 3.10)

project(power_strip C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(power_strip
    main.c
    main.h
    crc.c
    crc.h
)

if(MSVC)
    target_compile_options(power_strip PRIVATE /W4)
else()
    target_compile_options(power_strip PRIVATE -Wall -Wextra -pedantic)
endif()
