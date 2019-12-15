//
// Created by sbixby on 12/14/19.
//

#ifndef AOC2019_DAY3_HPP
#define AOC2019_DAY3_HPP

#include "day_base.hpp"

struct dir_len
{
    char dir;
    int  dist;
};

struct xy
{
    int x;
    int y;
};

struct ln
{
    int x1, x2;
    int y1, y2;
    bool xline;
    ln(int x1, int x2, int y1, int y2)
        : x1(x1)
        , x2(x2)
        , y1(y1)
        , y2(y2)
    {
        xline = y1==y2;
    }
};

class day3 : day_base
{
   public:
    void run_sim(int half) override;

   private:
    static std::vector<dir_len> ParseLine(const std::string& line);
    static std::vector<ln>      MakeLines(std::vector<dir_len> path);
};

#endif    // AOC2019_DAY3_HPP
