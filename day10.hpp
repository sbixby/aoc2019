//
// Created by sbixby on 12/31/19.
//

#ifndef AOC2019_DAY10_HPP
#define AOC2019_DAY10_HPP

#include "day_base.hpp"
class day10 : day_base
{
   public:
    void run_sim(int half) override;

   private:
    std::vector<xyang> asteroids;
    int             width;
    int             height;

    static bool isBetween(int i1, int i2, int i3);
    bool        onLineBetween(xyang &p1, xyang &p2, xyang &p3);
    void        ExtractPoints(std::vector<std::string> map);
    int         countVisible(xyang& mp);
    void        CalculateAngles(xyang &station);
};

#endif    // AOC2019_DAY10_HPP
