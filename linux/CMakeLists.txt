cmake_minimum_required(VERSION 3.2)

PROJECT(power_strip)

  add_executable(power_strip crc.c main.c)
  if(MSVC)
	target_compile_options(power_strip PRIVATE /wall)
  else()
  	target_compile_options(power_strip PRIVATE -Wall -Wextra -pedantic)
  endif()
