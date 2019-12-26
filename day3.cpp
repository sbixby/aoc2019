//
// Created by sbixby on 12/14/19.
//

#include "day3.hpp"
#include "day_base.hpp"
#include <boost/tokenizer.hpp>
#include <array>

std::vector<dir_len> day3::ParseLine(const std::string& line)
{
    std::vector<dir_len> rv;
    auto                 tok = boost::tokenizer<>(line);
    for (auto& itr : tok)
    {
        auto dir = itr[0];
        auto len = std::stoi(itr.substr(1));
        rv.push_back(dir_len{dir, len});
    }
    return rv;
}

std::vector<ln> day3::MakeLines(std::vector<dir_len> path)
{
    std::vector<ln> lines;
    int             cx = 0, cy = 0;
    for (dir_len& dl : path)
    {
        switch (dl.dir)
        {
            case 'R':
                lines.emplace_back(cx + 1, cx + dl.dist, cy, cy);
                cx += dl.dist;
                break;
            case 'L':
                lines.emplace_back(cx - dl.dist, cx - 1, cy, cy);
                cx -= dl.dist;
                break;
            case 'U':
                lines.emplace_back(cx, cx, cy + 1, cy + dl.dist);
                cy += dl.dist;
                break;
            case 'D':
                lines.emplace_back(cx, cx, cy - dl.dist, cy - 1);
                cy -= dl.dist;
                break;
        }
    }

    return lines;
}

std::vector<xy> day3::GetCoordsHit(std::vector<dir_len> path)
{
    std::vector<xy> coords;
    int             cx = 0, cy = 0;
    int             dx = 0, dy = 0;
    for (dir_len& dl : path)
    {
        for (int i = 0; i < dl.dist; ++i)
        {
            switch (dl.dir)
            {
                case 'R':
                    dx = 1;
                    dy = 0;
                    break;
                case 'L':
                    dx = -1;
                    dy = 0;
                    break;
                case 'U':
                    dx = 0;
                    dy = 1;
                    break;
                case 'D':
                    dx = 0;
                    dy = -1;
                    break;
            }
            cx += dx;
            cy += dy;
            coords.push_back(xy{cx, cy});
        }
    }
    return coords;
}

void day3::FindDupes(const std::vector<xy>& ch) const
{
    for (int i = 0; i < ch.size(); ++i)
    {
        for (int j = i + 1; j < ch.size(); ++j)
        {
            if (ch[i].x == ch[j].x && ch[i].y == ch[j].y)
            {
                std::cout << "Visited " << ch[i].x << "," << ch[i].y << " more than once" << std::endl;
            }
        }
    }
}

void day3::FindShortestDist(std::vector<xy>& ch, xy& c, int& idx, int& dist)
{
    idx = std::distance(ch.begin(), std::find(ch.begin(), ch.end(), c));
    int  fwd, rev, iter;
    int  minDist = idx;
    bool done;

    for (iter = 0; iter < idx; iter++)
    {
        done = false;
        for (fwd = iter; fwd < idx; ++fwd)
        {
            for (rev = idx - 1; rev > fwd; --rev)
            {
                // If no shortcuts, done here.
                if (fwd == rev)
                {
                    done = true;
                    break;
                }
                // If a shortcut, and it's shorter
                // than the current minimum, change
                // the current minimum, and bump out.
                if (ch[fwd] == ch[rev])
                {
                    int currDist = idx - (rev - fwd);
                    if (currDist < minDist)
                        minDist = currDist;
                    done = true;
                    break;
                }
            }
            // Break from middle loop.
            if (done)
            {
                break;
            }
        }
    }
    dist = minDist;
}

std::vector<xy> day3::FindCrossings(std::vector<ln>& lines)
{
    std::vector<xy> crossings;
    for (int i1 = 0; i1 < lines.size() - 1; ++i1)
    {
        for (int i2 = i1 + 1; i2 < lines.size(); ++i2)
        {
            auto l1 = lines[i1];
            auto l2 = lines[i2];
            if (l1.xline && !l2.xline)
            {
                if (l1.x1 <= l2.x1 && l1.x2 >= l2.x1 && l2.y1 <= l1.y1 && l2.y2 >= l1.y1)
                {
                    crossings.emplace_back(l2.x1, l1.y1);
                }
            }
            if (l2.xline && !l1.xline)
            {
                if (l2.x1 <= l1.x1 && l2.x2 >= l1.x1 && l1.y1 <= l2.y1 && l1.y2 >= l2.y1)
                {
                    crossings.emplace_back(l1.x1, l2.y1);
                }
            }
        }
    }
    return crossings;
}

std::vector<xy> day3::FindCrossings(std::vector<ln>& lines1, std::vector<ln>& lines2)
{
    std::vector<xy> crossings;
    for (auto& l1 : lines1)
    {
        for (auto& l2 : lines2)
        {
            if (l1.xline && !l2.xline)
            {
                if (l1.x1 <= l2.x1 && l1.x2 >= l2.x1 && l2.y1 <= l1.y1 && l2.y2 >= l1.y1)
                {
                    crossings.emplace_back(l2.x1, l1.y1);
                }
            }
            if (l2.xline && !l1.xline)
            {
                if (l2.x1 <= l1.x1 && l2.x2 >= l1.x1 && l1.y1 <= l2.y1 && l1.y2 >= l2.y1)
                {
                    crossings.emplace_back(l1.x1, l2.y1);
                }
            }
        }
    }
    return crossings;
}

void day3::run_sim(int half)
{
    auto lines = load_data("../data/day3.txt");
    auto path1 = ParseLine(lines[0]);
    auto path2 = ParseLine(lines[1]);

    auto lines1 = MakeLines(path1);
    auto lines2 = MakeLines(path2);

    auto cross1 = FindCrossings(lines1);
    std::cout << "cross1.size():" << cross1.size() << std::endl;
    auto cross2 = FindCrossings(lines2);
    std::cout << "cross2.size():" << cross2.size() << std::endl;
    auto crossings = FindCrossings(lines1, lines2);
    std::cout << "crossings.size():" << crossings.size() << std::endl;

    if (half == 1)
    {
        int smallest{99999999};
        for (auto& c : crossings)
        {
            //        std::cout << c.x << ", " << c.y << std::endl;
            int dist = abs(c.x) + abs(c.y);
            if (dist < smallest)
                smallest = dist;
        }

        std::cout << "smallest:" << smallest << std::endl;
    }
    else
    {
        std::vector<xy> ch1 = GetCoordsHit(path1);
        std::cout << "ch1.size():" << ch1.size() << std::endl;
        std::vector<xy> ch2 = GetCoordsHit(path2);
        std::cout << "ch2.size():" << ch2.size() << std::endl;
        std::sort(crossings.begin(), crossings.end());

//        dump_map(ch1, cross1, ch2, cross2, crossings);

        int shortestPaths = 999999999;

        for (auto& cr : crossings)
        {
            int steps1 = FindSteps(ch1, cross1, cr);
//            std::cout << "steps1:" << steps1 << std::endl;
            int steps2 = FindSteps(ch2, cross2, cr);
//            std::cout << "steps2:" << steps2 << std::endl;

            if ((steps1+steps2) < shortestPaths) {
                shortestPaths = steps1+steps2;
            }
        }

        //        std::cout << "crossings.size():" << crossings.size() << std::endl;
        //        std::cout << "ch1.size():" << ch1.size() << std::endl;
        //        std::cout << "ch2.size():" << ch2.size() << std::endl;

        //        std::cout << "Dupes for ch1:" << std::endl;
        //        FindDupes(ch1);
        //        std::cout << "\n\nDupes for ch2:" << std::endl;
        //        FindDupes(ch2);

        std::cout << "Shortest steps:" << shortestPaths << std::endl;
    }
}

void day3::dump_map(std::vector<xy> ch1, std::vector<xy> cross1, std::vector<xy> ch2, std::vector<xy> cross2,
                    std::vector<xy> crossings)
{
    int minx = 999999, miny = 999999, maxx = -999999, maxy = -999999;
    for (auto& c : ch1)
    {
        if (c.x < minx)
            minx = c.x;
        if (c.y < miny)
            miny = c.y;
        if (c.x > maxx)
            maxx = c.x;
        if (c.y > maxy)
            maxy = c.y;
    }
    for (auto& c : ch2)
    {
        if (c.x < minx)
            minx = c.x;
        if (c.y < miny)
            miny = c.y;
        if (c.x > maxx)
            maxx = c.x;
        if (c.y > maxy)
            maxy = c.y;
    }
    int offx = -minx;
    int offy = -miny;

    std::vector<std::vector<char>> map;
    map.reserve(maxy - miny);
    for (int i = 0; i < (maxy - miny + 1); ++i)
    {
        map.emplace_back(maxx - minx + 1, '.');
    }

    // Origin
    map[offy][offx] = '0';

    for (auto& c : ch1)
    {
        map[c.y + offy][c.x + offx] = '1';
    }
    for (auto& c : cross1)
    {
        map[c.y + offy][c.x + offx] = '#';
    }
    for (auto& c : ch2)
    {
        map[c.y + offy][c.x + offx] = '2';
    }
    for (auto& c : cross2)
    {
        map[c.y + offy][c.x + offx] = '*';
    }
    for (auto& c : crossings)
    {
        map[c.y + offy][c.x + offx] = 'X';
    }

    std::ofstream os("grid.txt");
    for (auto it = map.rbegin(); it != map.rend(); it++)
    {
        for (auto c : (*it))
        {
            os << c;
        }
        os << std::endl;
    }
    os << std::endl;
    os.close();
}

int day3::FindSteps(std::vector<xy> coords, std::vector<xy> selfCrosses, xy& commonCross)
{
    int  ccIdx    = std::distance(coords.begin(), std::find(coords.begin(), coords.end(), commonCross));
    auto itr1     = coords.begin();
    auto itr2     = coords.begin() + ccIdx;
    int  shortest = ccIdx+1;

    // Look at all self crosses
//    for (auto& sc : selfCrosses)
//    {
//        // If this self-cross shortens the path, use it.
//        auto scr1 = std::find(itr1, itr2, sc);
//        if (scr1 == itr2)
//            continue;
//        int idx1 = std::distance(itr1, scr1);
//
//        // Look for last self-cross in the list before the common cross
//        int idx2 = -1;
//        for (int i = ccIdx - 1; i > idx1; --i)
//        {
//            if (coords[i] == sc)
//                idx2 = i;
//        }
//        // If we found one, calculate the shortened
//        // path and compare it to the current one.
//        if (idx2 >= 0)
//        {
//            int sp = ccIdx - (idx2 - idx1) +1;
//            if (sp < shortest)
//                shortest = sp;
//        }
//    }
    return shortest; //
}
