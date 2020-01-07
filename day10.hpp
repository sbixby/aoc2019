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
    std::vector<xyadr> asteroids;
    int             width;
    int             height;

    static bool isBetween(int i1, int i2, int i3);
    bool        onLineBetween(xyadr &p1, xyadr &p2, xyadr &p3);
    void        ExtractPoints(std::vector<std::string> map);
    int         countVisible(xyadr & mp);
    void        CalculateAngles(xyadr &station);
    void        CalculatePC(xyadr& orig, xyadr& tgt, double& angle, double& radius);
    static bool        eff0(double d1, double d2);
};

#endif    // AOC2019_DAY10_HPP
