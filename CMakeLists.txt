cmake_minimum_required(VERSION 3.10)

file(GLOB _src "./*.cpp" "./*.h"
)

add_executable(simple_debug_demo ${_src})
