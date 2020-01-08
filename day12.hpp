//
// Created by sbixby on 1/8/20.
//

#ifndef AOC2019_DAY12_HPP
#define AOC2019_DAY12_HPP

#include "day_base.hpp"
class day12 : day_base
{
   public:
    void run_sim(int half) override;
    std::vector<xyz> ParsePlanets(std::vector<std::string> lines);
};

#endif    // AOC2019_DAY12_HPP
