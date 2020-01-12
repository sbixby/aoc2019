//
// Created by sbixby on 1/8/20.
//

#ifndef AOC2019_DAY13_HPP
#define AOC2019_DAY13_HPP

#include "day_base.hpp"
class day13 : day_base
{
   public:
    void run_sim(int half) override;
    static bool runProgram(std::vector<long>& pg, std::vector<long>& inputs, std::vector<long>& outputs, int expOutputCount,
                    long& sp, long& relBase);
    static void PrintScreen(std::vector<std::vector<char>> &scrn, std::vector<long> &outputs, bool first);
};

#endif    // AOC2019_DAY13_HPP
