cmake_minimum_required(VERSION 3.2)

PROJECT(power_strip)

  add_executable(power_strip crc.c main.c)
  if(MSVC)
	target_compile_options(power_strip PRIVATE /wall)
  else()
  	target_compile_options(power_strip PRIVATE -Wall -Wextra -pedantic)
  endif()

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
#target_link_libraries(MyExample PRIVATE MyLibExample)
