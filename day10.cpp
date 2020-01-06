//
// Created by sbixby on 12/31/19.
//

#include <cmath>
#include "day10.hpp"

bool day10::isBetween(int i1, int i2, int i3)
{
    if (i1 < i2)
        return (i3 > i1) && (i3 < i2);
    else
        return (i3 > i2) && (i3 < i1);
}

bool day10::onLineBetween(xyang &p1, xyang &p2, xyang &p3)
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

int day10::countVisible(xyang &mp)
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

void day10::CalculateAngles(xyang &station)
{
    for(auto &pt : asteroids) {
//        if (pt!=station) {
//
//        }
    }
}

void day10::run_sim(int half)
{
    ExtractPoints(load_data("../data/day10_f.txt"));

    //    std::vector<std::vector<int>> mapCounts;
    //    mapCounts.reserve(height);
    //    for (int i = 0; i < height; ++i)
    //        mapCounts.emplace_back(width, 0);
    //
    int maxCount = -1;
    xyang  mc;

//    xyang p{4, 0};
//    countVisible(p);
//    return;

    for (auto &pt : asteroids)
    {
        int c = countVisible(pt);
        if (c > maxCount)
        {
            maxCount = c;
            mc       = pt;
        }
    }

    if (half==1) {
        std::cout << "maxCount:" << maxCount << " at: " << mc.x << "," << mc.y << std::endl;
    } else {
        CalculateAngles(mc);
    }

}
