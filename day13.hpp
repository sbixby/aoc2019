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
    bool runProgram(std::vector<long>& pg, std::vector<long>& inputs, std::vector<long>& outputs, int expOutputCount,
                    long& sp, long& relBase);
};

#endif    // AOC2019_DAY13_HPP
