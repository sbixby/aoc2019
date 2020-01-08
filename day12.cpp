//
// Created by sbixby on 1/8/20.
//

#include "day12.hpp"
#include <regex>

std::vector<xyz> day12::ParsePlanets(std::vector<std::string> lines)
{
    std::vector<xyz> planets;
    for (auto &line : lines)
    {
        std::regex  xyzline{R"(\<x=(.*), y=(.*), z=(.*)\>)"};
        std::smatch groups;
        if (std::regex_match(line, groups, xyzline))
        {
            planets.emplace_back(std::stoi(groups[1]), std::stoi(groups[2]), std::stoi(groups[3]));
        }
    }
    return planets;
}

void day12::run_sim(int half)
{
    auto planets = ParsePlanets(load_data("../data/day12_a.txt"));

    int pn = 1;
    for (auto &p : planets)
    {
        std::cout << "p@" << pn++ << ":" << p << std::endl;
    }
}
