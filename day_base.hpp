//
// Created by sbixby on 12/12/19.
//

#ifndef AOC2019_DAY_BASE_HPP
#define AOC2019_DAY_BASE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class day_base
{
   public:
    virtual std::vector<std::string> load_data(std::string fileName);
    virtual void                     run_sim(int half) = 0;
};

struct dir_len
{
    char dir;
    int  dist;
};

struct xy
{
    int x;
    int y;
    int md;
    int c1Idx;
    int c2Idx;
    int c1Dist;
    int c2Dist;
    std::vector<int> crosses;

    xy(int x, int y)
        : x{x}
        , y{y}
        , c1Idx{-1}
        , c2Idx{-1}
        , c1Dist{-1}
        , c2Dist{-1} {
        md = abs(x) + abs(y);
    };

    bool operator<(const xy &other)
    {
        return md < other.md;
    }

    bool operator==(const xy &other)
    {
        return x == other.x && y == other.y;
    }
};

struct ln
{
    int  x1, x2;
    int  y1, y2;
    bool xline;
    ln(int x1, int x2, int y1, int y2)
        : x1(x1)
        , x2(x2)
        , y1(y1)
        , y2(y2)
    {
        xline = y1 == y2;
    }
};

#endif    // AOC2019_DAY_BASE_HPP