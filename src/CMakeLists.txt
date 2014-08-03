cmake_minimum_required(VERSION 2.6)
ADD_DEFINITIONS(
  -std=c++11
  -O3
  )
file(GLOB src
  "*.h"
  "*.cpp"
  )
add_executable(main ${src})
