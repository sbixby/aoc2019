//
// Created by sbixby on 12/14/19.
//

#include "day3.hpp"
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

void day3::run_sim(int half)
{
    auto lines  = load_data("../data/day3.txt");
    auto path1  = ParseLine(lines[0]);
    auto path2  = ParseLine(lines[1]);
    auto lines1 = MakeLines(path1);
    auto lines2 = MakeLines(path2);

//    std::cout << "lines 1" << std::endl;
//    for (auto& l : lines1)
//    {
//        std::cout << "Line from: " << l.x1 << "," << l.y1 << " to: " << l.x2 << "," << l.y2 << ",  x?:" << l.xline << std::endl;
//    }
//
//    std::cout << "lines 2" << std::endl;
//    for (auto& l : lines2)
//    {
//        std::cout << "Line from: " << l.x1 << "," << l.y1 << " to: " << l.x2 << "," << l.y2 << ",  x?:" << l.xline << std::endl;
//    }
//
    std::vector<xy> crossings;
    for (auto& l1 : lines1)
    {
        for (auto& l2 : lines2)
        {
            if (l1.xline && !l2.xline)
            {
                if (l1.x1 <= l2.x1 && l1.x2 >= l2.x1 && l2.y1 <= l1.y1 && l2.y2 >= l1.y1) {
                    crossings.push_back( xy { l2.x1, l1.y1});
                }
            }
            if (l2.xline && !l1.xline)
            {
                if (l2.x1 <= l1.x1 && l2.x2 >= l1.x1 && l1.y1 <= l2.y1 && l1.y2 >= l2.y1) {
                    crossings.push_back( xy { l1.x1, l2.y1});
                }

            }
        }
    }

    int smallest{99999999};
    for (auto &c : crossings)
    {
//        std::cout << c.x << ", " << c.y << std::endl;
        int dist = abs(c.x) + abs(c.y);
        if (dist < smallest)
            smallest = dist;
    }

    std::cout << "smallest:" << smallest << std::endl;

}
