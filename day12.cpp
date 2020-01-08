//
// Created by sbixby on 1/8/20.
//

#include "day12.hpp"
#include <regex>
#include <iomanip>
#include <boost/integer/common_factor.hpp>

void day12::ParseMoons(const std::vector<std::string>& lines, int* moons)
{
    std::fill(moons, moons + 24, 0);
    for (int i = 0; i < lines.size(); ++i)
    {
        std::regex  xyzline{R"(\<x=(.*), y=(.*), z=(.*)\>)"};
        std::smatch groups;
        if (std::regex_match(lines[i], groups, xyzline))
        {
            moons[i * 6 + 0] = stoi(groups[1]);
            moons[i * 6 + 1] = stoi(groups[2]);
            moons[i * 6 + 2] = stoi(groups[3]);
        }
    }
}

void day12::PrintMoons(int* moons, int timeIndex)
{
    std::cout << "timeIndex:" << timeIndex << std::endl;
    int idx = -1;
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "pos=<x=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ", y=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ", z=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ">, vel=<x=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ", y=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ", z=" << std::setfill(' ') << std::setw(6) << moons[++idx];
        std::cout << ">" << std::endl;
    }
    std::cout << std::endl;
}

void day12::UpdateMoons(int* moons, int dim)
{
    for (int ml = 0; ml < 3; ++ml)
    {
        int mml = ml * 6 + dim;
        for (int mr = ml; mr < 4; ++mr)
        {
            int mmr = mr * 6 + dim;
            if (moons[mml] < moons[mmr])
            {
                moons[mml + 3]++;
                moons[mmr + 3]--;
            }
            else if (moons[mml] > moons[mmr])
            {
                moons[mml + 3]--;
                moons[mmr + 3]++;
            }
        }
    }
    for (int ml = 0; ml < 4; ++ml)
    {
        moons[ml * 6 + dim] += moons[ml * 6 + dim + 3];
    }
}

int day12::CalculateEnergy(int* moons)
{
    int nrg = 0;
    for (int i = 0; i < 4; ++i)
    {
        int pe = abs(moons[i * 6 + 0]) + abs(moons[i * 6 + 1]) + abs(moons[i * 6 + 2]);
        int ke = abs(moons[i * 6 + 3]) + abs(moons[i * 6 + 4]) + abs(moons[i * 6 + 5]);
        nrg += pe * ke;
    }
    return nrg;
}

/*
int day12::GetChange(int src, int dst)
{
    if (src < dst)
        return 1;
    if (src > dst)
        return -1;
    return 0;
}

void day12::UpdateVel(xyzvel &src, xyzvel &dst)
{
    src.vx += GetChange(src.x, dst.x);
    src.vy += GetChange(src.y, dst.y);
    src.vz += GetChange(src.z, dst.z);
}

void day12::PrintMoons(const std::vector<xyzvel> &moons, int i)
{
    std::cout << "Time: " << i << std::endl;
    for (auto &p : moons)
    {
        std::cout << p << std::endl;
    }
    std::cout << std::endl;
}

void day12::CalcVels(int moons[4][6])
{
    for (int srcIdx = 0; srcIdx < moons.size() - 1; ++srcIdx)
    {
        for (int dstIdx = srcIdx; dstIdx < moons.size(); ++dstIdx)
        {
            UpdateVel(moons[srcIdx], moons[dstIdx]);
            UpdateVel(moons[dstIdx], moons[srcIdx]);
        }
    }
}

void day12::UpdatePositions(std::vector<xyzvel> &moons)
{
    for (auto &m : moons)
    {
        m.x += m.vx;
        m.y += m.vy;
        m.z += m.vz;
    }
}

int day12::CalculateEnergy(std::vector<xyzvel> &moons)
{
    int vel = 0;
    for (auto &m : moons)
    {
        vel += m.nrg();
    }
    return vel;
}

bool day12::PosSame(const std::vector<xyzvel> &a, const std::vector<xyzvel> &b)
{
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i].x != b[i].x || a[i].y != b[i].y || a[i].z != b[i].z)
            return false;
    }
    return true;
}
*/

void day12::run_sim(int half)
{
    int* moons = new int[4 * 6];
    ParseMoons(load_data("../data/day12.txt"), moons);

    if (half == 1)
    {
        //        PrintMoons(moons, 0);
        int turn = 1;
        for (; turn <= 100000000; ++turn)
        {
            UpdateMoons(moons, 0);
            UpdateMoons(moons, 1);
            UpdateMoons(moons, 2);
            //            PrintMoons(moons, turn);
        }
        PrintMoons(moons, turn - 1);

        std::cout << "nrg:" << CalculateEnergy(moons) << std::endl;
    }
    else
    {
        PrintMoons(moons, 0);
        unsigned long each[3]{0, 0, 0};
        for (int i = 0; i < 3; ++i)
        {
            int orig[8]{moons[0 * 6 + i],     moons[1 * 6 + i],     moons[2 * 6 + i],     moons[3 * 6 + i],
                        moons[0 * 6 + i + 3], moons[1 * 6 + i + 3], moons[2 * 6 + i + 3], moons[3 * 6 + i + 3]};
            while (true)
            {
                UpdateMoons(moons, i);
                each[i]++;
                if (orig[0] == moons[0 * 6 + i] && orig[1] == moons[1 * 6 + i] && orig[2] == moons[2 * 6 + i] &&
                    orig[3] == moons[3 * 6 + i] && orig[4] == moons[0 * 6 + i + 3] && orig[5] == moons[1 * 6 + i + 3] &&
                    orig[6] == moons[2 * 6 + i + 3] && orig[7] == moons[3 * 6 + i + 3])
                    break;
            }
        }

        std::cout << "x: " << each[0] << "  y=" << each[1] << "  z=" << each[2] << std::endl;

        long lcm = boost::integer::lcm(each[0], each[1], each[2]);
        std::cout << "lcm:" << lcm << std::endl;
    }

    delete[] moons;
}
