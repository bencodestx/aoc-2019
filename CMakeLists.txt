cmake_minimum_required( VERSION 2.8 )

project( aoc2019 )

SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET (CMAKE_C_FLAGS "-Wall -Wextra -Werror -std=c99" )
SET (CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -std=c++14")

include_directories("Catch2/single_include")

file(GLOB UNITTESTS *_test.cpp)

enable_testing()
add_executable(unittest unittest.cpp ${UNITTESTS})
add_test(unittests unittest)

add_executable(day1_part1 day1_part1.cpp)
add_executable(day1_part2 day1_part2.cpp)
