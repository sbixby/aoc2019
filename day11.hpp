//
// Created by sbixby on 1/7/20.
//

#ifndef AOC2019_DAY11_HPP
#define AOC2019_DAY11_HPP

#include "day_base.hpp"
class day11:day_base
{
   public:
    void run_sim(int half) override;
    bool runProgram(std::vector<long>& pg, std::vector<long>& inputs, std::vector<long>& outputs, int expOutputCount,
                    long& sp);
};

#endif    // AOC2019_DAY11_HPP
