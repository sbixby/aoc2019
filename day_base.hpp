//
// Created by sbixby on 12/12/19.
//

#ifndef AOC2019_DAY_BASE_HPP
#define AOC2019_DAY_BASE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>

class day_base
{
   public:
    virtual std::vector<std::string> load_data(std::string fileName);
    virtual void                     run_sim(int half) = 0;
    static std::vector<long>         ParseLine(const std::string& line, long reserve = -1);
    static long                      getIntCodeVal(std::vector<long>& pg, long sp, long pm, long relBase);
    static void setIntCodeVal(std::vector<long>& pg, long sp, long pm, long relBase, long newValue);
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
    xy()
        : x{-1}
        , y{-1}
    {
    }
    xy(int x, int y)
        : x{x}
        , y{y}
    {
    }
    bool operator==(const xy& other)
    {
        return x == other.x && y == other.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const xy& o);
};

std::ostream& operator<<(std::ostream& os, const xy& o);

struct xy2 : xy
{
    int              md;
    int              c1Idx;
    int              c2Idx;
    int              c1Dist;
    int              c2Dist;
    std::vector<int> crosses;

    xy2(int x, int y)
        : xy{x, y}
        , c1Idx{-1}
        , c2Idx{-1}
        , c1Dist{-1}
        , c2Dist{-1}
    {
        md = abs(x) + abs(y);
    };

    bool operator<(const xy2& other)
    {
        return md < other.md;
    }
};

struct xyadr : xy
{
    double angle;
    double dist;
    int    ring;
    xyadr()
        : xy{-1, -1}
        , angle{99999999.0}
        , dist{0.0}
        , ring{0} {};
    xyadr(int x, int y)
        : xy{x, y}
        , dist{0.0}
        , ring{0}
        , angle{999999999.0}
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const xyadr& o);
};

struct xyclr : xy
{
    int color;    // 0=black, 1=white
    xyclr(int x, int y)
        : xy(x, y)
        , color(0)
    {
    }
    xyclr(int x, int y, int clr)
        : xy(x, y)
        , color(clr)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const xyclr& o);
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

struct xyzvel
{
    int x;
    int y;
    int z;
    int vx, vy, vz;
    xyzvel(int x, int y, int z)
        : x{x}
        , y{y}
        , z{z}
        , vx{0}
        , vy{0}
        , vz{0}
    {
    }
    xyzvel()
        : x{INT32_MAX}
        , y{INT32_MAX}
        , z{INT32_MAX}
        , vx{INT32_MAX}
        , vy{INT32_MAX}
        , vz{INT32_MAX}
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const xyzvel& o);

    int nrg()
    {
        return (abs(x) + abs(y) + abs(z)) * (abs(vx) + abs(vy) + abs(vz));
    }
};

#endif    // AOC2019_DAY_BASE_HPP
