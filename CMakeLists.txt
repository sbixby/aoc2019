cmake_minimum_required(VERSION 3.15)
project(aoc2019)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc2019 main.cpp day1.cpp day1.hpp day_base.hpp day_base.cpp day2.cpp day2.hpp day3.cpp day3.hpp day4.cpp day4.hpp day5.cpp day5.hpp day6.cpp day6.hpp day7.cpp day7.hpp day8.cpp day8.hpp day9.cpp day9.hpp day10.cpp day10.hpp day11.cpp day11.hpp day12.cpp day12.hpp)

target_link_libraries(aoc2019 PRIVATE
        Boost::headers
        Boost::filesystem
        Boost::system
        )