#include <cmath>
#include "day9.hpp"
#include "day11.hpp"
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include "day_base.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

std::vector<std::string> day_base::load_data(std::string fileName)
{
    try
    {
        std::ifstream ifl(fileName.c_str());
        if (ifl.is_open())
        {
            std::vector<std::string> lines;
            while (ifl.good())
            {
                std::string line;
                std::getline(ifl, line);
                if (!line.empty())
                    lines.push_back(line);
            }
            ifl.close();
            return lines;
        }
        else
        {
            std::cout << "Couldn't open file" << std::endl;
            exit(1);
        }
    }
    catch (std::exception& e)
    {
        std::cout << "File load exception thrown:" << e.what() << std::endl;
        exit(2);
    }
}

std::ostream& operator<<(std::ostream& os, const xy& o)
{
    os << "(" << o.x << "," << o.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const xyadr& o)
{
    os << "(" << o.x << "," << o.y << ") - a:" << o.angle << " r:" << o.dist << " ring:" << o.ring;
    return os;
}

std::ostream& operator<<(std::ostream& os, const xyclr& o)
{
    os << "(" << o.x << "," << o.y << ") - color:" << o.color;
    return os;
}

std::ostream& operator<<(std::ostream& os, const xyzvel& o)
{
    os << "pos=<x=" << std::setfill(' ') << std::setw(6)  << o.x;
    os << ", y=" << std::setfill(' ') << std::setw(6)   << o.y;
    os << ", z=" << std::setfill(' ') << std::setw(6)   << o.z;
    os << ">, vel=<x=" << std::setfill(' ') << std::setw(6)   << o.vx;
    os << ", y=" << std::setfill(' ') << std::setw(6)   << o.vy;
    os << ", z=" << std::setfill(' ') << std::setw(6)   << o.vz;
    os << ">";
    return os;
}

std::vector<long> day_base::ParseLine(const std::string& line, long reserve)
{
    std::vector<long> opCodes;
    if (reserve >= 0)
        opCodes.reserve(reserve);
    auto sep = boost::char_separator<char>(",");
    auto tok = boost::tokenizer<boost::char_separator<char>>(line, sep);
    int  idx = 0;
    for (auto& itr : tok)
    {
        long oc = std::stol(itr);
        if (reserve >= 0)
        {
            opCodes[idx++] = oc;
        }
        else
            opCodes.push_back(oc);
    }
    return opCodes;
}

long day_base::getIntCodeVal(std::vector<long>& pg, long sp, long pm, long relBase)
{
    int fct = 10;
    for (int i = 0; i < pm; ++i)
    {
        fct *= 10;
    }
    long mode = pg[sp] / fct % 10;
    long loc;
    if (mode == 0)
    {
        loc = pg[sp + pm];
    }
    else if (mode == 1)
    {
        loc = sp + pm;
    }
    else
    {
        loc = pg[sp + pm] + relBase;
    }
    return pg[loc];
}

void day_base::setIntCodeVal(std::vector<long>& pg, long sp, long pm, long relBase, long newValue)
{
    int fct = 10;
    for (int i = 0; i < pm; ++i)
    {
        fct *= 10;
    }
    long mode = pg[sp] / fct % 10;
    long dest;
    if (mode == 0)
    {
        dest = pg[sp + pm];
    }
    else if (mode == 1)
    {
        dest = sp + pm;
    }
    else
    {
        dest = pg[sp + pm] + relBase;
    }
    pg[dest] = newValue;
}
