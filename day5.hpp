//
// Created by sbixby on 12/25/19.
//

#ifndef AOC2019_DAY5_HPP
#define AOC2019_DAY5_HPP

#include "day_base.hpp"
class day5 : day_base
{
   public:
    void run_sim(int half) override;
    static void             runProgram(std::vector<int> pg, int input, int& output);
    static std::vector<int> ParseLine(std::string line);
};

#endif    // AOC2019_DAY5_HPP
