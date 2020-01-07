//
// Created by sbixby on 12/31/19.
//

#include <cmath>
#include <algorithm>
#include "day10.hpp"

bool day10::isBetween(int i1, int i2, int i3)
{
    if (i1 < i2)
        return (i3 > i1) && (i3 < i2);
    else
        return (i3 > i2) && (i3 < i1);
}

bool day10::onLineBetween(xyadr &p1, xyadr &p2, xyadr &p3)
{
    bool xb = isBetween(p1.x, p2.x, p3.x);
    bool yb = isBetween(p1.y, p2.y, p3.y);

    if (p1.x == p2.x)
    {
        return p1.x == p3.x && yb;
    }
    else if (p1.y == p2.y)
    {
        return p1.y == p3.y && xb;
    }
    else if (xb && yb)
    {
        // Do slope-intercepts
        double m = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
        double b = ((double)(p2.x * p1.y - p1.x * p2.y) / (p2.x - p1.x));

        return fabs(m * p3.x + b - p3.y) < 0.000001;
    }
    return false;
}

int day10::countVisible(xyadr &mp)
{
    //    std::cout << "Looking at: " << mp << std::endl;
    int notBlocked = 0;
    for (auto &srcPt : asteroids)
    {
        if (srcPt == mp)
        {
            continue;
        }
        bool hasMid = false;
        for (auto &midPt : asteroids)
        {
            if (midPt == srcPt || midPt == mp)
            {
                continue;
            }
            bool btw = onLineBetween(mp, srcPt, midPt);
            //            std::cout << midPt << " between " << mp << " and " << srcPt << "? "<< (btw?"true":"false") <<
            //            std::endl;
            if (btw)
            {
                hasMid = true;
                //                std::cout << "Blocked:" << srcPt << " by " << midPt << std::endl;
                break;
            }
        }
        if (!hasMid)
        {
            notBlocked++;
            //            std::cout << "Not Blocked:" << srcPt << std::endl;
        }
    }
    //    std::cout << "count: " << notBlocked << std::endl << std::endl;
    return notBlocked;
}

void day10::ExtractPoints(std::vector<std::string> map)
{
    width  = map[0].size();
    height = map.size();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (map[y][x] == '#')
            {
                asteroids.emplace_back(x, y);
            }
        }
    }
}

void day10::CalculateAngles(xyadr &station)
{
    for (auto &pt : asteroids)
    {
        CalculatePC(station, pt, pt.angle, pt.dist);
    }
}

// "converts" grid to represent rotation clockwise around
// source point.   Angle is 0 to 2*PI
void day10::CalculatePC(xyadr &orig, xyadr &tgt, double &angle, double &radius)
{
    double dx = tgt.y - orig.y;
    double dy = tgt.x - orig.x;
    radius    = std::sqrt(std::pow(dx, 2.0) + std::pow(dy, 2.0));
    angle     = -std::atan2(dy, dx) + M_PI;
}

bool day10::eff0(double d1, double d2)
{
    return std::abs(d1 - d2) < 0.000001;
}

void day10::run_sim(int half)
{
    ExtractPoints(load_data("../data/day10.txt"));

    int   maxCount = -1;
    xyadr mc;

    for (auto &pt : asteroids)
    {
        int c = countVisible(pt);
        if (c > maxCount)
        {
            maxCount = c;
            mc       = pt;
        }
    }

    if (half == 1)
    {
        std::cout << "maxCount:" << maxCount << " at: " << mc.x << "," << mc.y << std::endl;
    }
    else
    {
        CalculateAngles(mc);
        // Sort by angle+radius
        std::sort(asteroids.begin(), asteroids.end(), [](const xyadr &a, const xyadr &b) -> bool {
            if (!eff0(a.angle, b.angle))
                return a.angle < b.angle;
            return a.dist < b.dist;
        });

        // Assign to rings
        for (int i = 0; i < asteroids.size() - 1; ++i)
        {
            if (eff0(asteroids[i].angle, asteroids[i + 1].angle))
            {
                asteroids[i + 1].ring = asteroids[i].ring + 1;
            }
        }

        // Sort by ring+radius
        std::sort(asteroids.begin(), asteroids.end(), [](const xyadr &a, const xyadr &b) -> bool {
            if (a.ring != b.ring)
                return a.ring < b.ring;
            return a.angle < b.angle;
        });

        // Print specific indexes:
//        std::cout << "asteroid#1:" << asteroids[0] << std::endl;
//        std::cout << "asteroid#2:" << asteroids[1] << std::endl;
//        std::cout << "asteroid#3:" << asteroids[2] << std::endl;
//        std::cout << "asteroid#10:" << asteroids[9] << std::endl;
//        std::cout << "asteroid#20:" << asteroids[19] << std::endl;
//        std::cout << "asteroid#50:" << asteroids[49] << std::endl;
//        std::cout << "asteroid#100:" << asteroids[99] << std::endl;
//        std::cout << "asteroid#199:" << asteroids[198] << std::endl;
        std::cout << "asteroid#200:" << asteroids[199] << std::endl;
//        std::cout << "asteroid#201:" << asteroids[200] << std::endl;
//        std::cout << "asteroid#299:" << asteroids[298] << std::endl;
    }
}
