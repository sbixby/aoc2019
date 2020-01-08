//
// Created by sbixby on 1/8/20.
//

#ifndef AOC2019_DAY12_HPP
#define AOC2019_DAY12_HPP

#include "day_base.hpp"
class day12 : day_base
{
   public:
    void                run_sim(int half) override;
    static void                ParseMoons(const std::vector<std::string>& lines, int* moons);
    static void                PrintMoons(int* moons, int timeIndex);
    void                UpdateMoons(int* moons);
    static int          CalculateEnergy(int* moons);
    static void                       UpdateMoons(int* moons, int dim);
};

#endif    // AOC2019_DAY12_HPP
