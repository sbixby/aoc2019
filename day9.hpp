//
// Created by sbixby on 12/30/19.
//

#ifndef AOC2019_DAY9_HPP
#define AOC2019_DAY9_HPP

#include "day_base.hpp"
class day9 : day_base
{
   public:
    void run_sim(int half) override;
    static void runProgram(std::vector<long> &pg, long input, long& output);
};

#endif    // AOC2019_DAY9_HPP
