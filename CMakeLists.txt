project (ALGO)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable (high-precision high-precision.cpp)
