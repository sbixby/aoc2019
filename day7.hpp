//
// Created by sbixby on 12/28/19.
//

#ifndef AOC2019_DAY7_HPP
#define AOC2019_DAY7_HPP

#include "day_base.hpp"
class day7 : day_base
{
   public:
    void run_sim(int half) override;

   private:
    bool runProgram(std::vector<long> &pg, int phase, int input, int& output, bool returnOnOutput, int& sp);
    void MakePermutations(std::vector<int> v, std::vector<std::vector<int>> &perms);
};

#endif    // AOC2019_DAY7_HPP
