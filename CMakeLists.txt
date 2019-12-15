cmake_minimum_required(VERSION 3.15)
project(aoc2019)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc2019 main.cpp day1.cpp day1.hpp day_base.hpp day_base.cpp day2.cpp day2.hpp day3.cpp day3.hpp)

target_link_libraries(aoc2019 PRIVATE
        Boost::headers
        Boost::filesystem
        Boost::system
        )