//
// Created by sbixby on 12/13/19.
//

#include "day3.hpp"
#include <boost/tokenizer.hpp>
#include <array>

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

std::vector<dir_len> ParseLine(std::string line)
{
    std::vector<dir_len> rv;
    auto                 tok = boost::tokenizer<>(line);
    for (auto &itr : tok)
    {
        auto dir = itr[0];
        auto len = std::stoi(itr.substr(1));
        rv.push_back(dir_len{dir, len});
    }
    return rv;
}

void print_path(std::vector<dir_len> path)
{
    std::cout << "Path:" << std::endl;
    for (auto &dl : path)
    {
        std::cout << "    " << dl.dir << " " << dl.dist << std::endl;
    }
}

std::vector<xy> GetCoordsHit(std::vector<dir_len> path)
{
    std::vector<xy> coords;
    int             cx = 0, cy = 0;
    int             dx = 0, dy = 0;
    for (dir_len &dl : path)
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

std::vector<xy> FindCommon(std::vector<xy> p1, std::vector<xy> p2)
{
    std::vector<xy> ccs;
    for (auto &i1 : p1)
    {
        for (auto &i2 : p2)
        {
            if (i1.x == i2.x && i1.y == i2.y)
            {
                ccs.push_back(i2);
            }
        }
    }
    return ccs;
}

void FindExtents(std::vector<xy> p, int &minx, int &miny, int &maxx, int &maxy)
{
    for (auto &c : p)
    {
        if (c.x < minx)
            minx = c.x;
        if (c.x > maxx)
            maxx = c.x;
        if (c.y < miny)
            miny = c.y;
        if (c.y > maxy)
            maxy = c.y;
    }
}

void DumpFilledGrids(std::vector<xy> p1, std::vector<xy> p2)
{
    int minx = 999999, miny = 999999, maxx = -999999, maxy = -999999;
    FindExtents(p1, minx, miny, maxx, maxy);
    FindExtents(p2, minx, miny, maxx, maxy);
    std::cout << "minx:" << minx << std::endl;
    std::cout << "miny:" << miny << std::endl;
    std::cout << "maxx:" << maxx << std::endl;
    std::cout << "maxy:" << maxy << std::endl;

    std::size_t sizex = maxx - minx + 1;
    std::size_t sizey = maxy - miny + 1;
    int         offsx = -minx;
    int         offsy = -miny;

    std::vector<std::vector<char>> grid;
    grid.reserve(sizey);
    for (int iy = 0; iy < sizey; ++iy)
    {
        grid.emplace_back(sizex, '.');
    }

    grid[offsy][offsx] = 'O';

    for (auto &c : p1)
    {
        grid[c.y + offsy][c.x + offsx] = 'X';
    }
    for (auto &c : p2)
    {
        char cell = grid[c.y + offsy][c.x + offsx] == 'X' ? '*' : 'Y';

        grid[c.y + offsy][c.x + offsx] = cell;
    }

    std::reverse(grid.begin(), grid.end());
    for (auto &rw : grid)
    {
        for (auto &col : rw)
        {
            std::cout << col;
        }
        std::cout << std::endl;
    }
}

void print_coords(std::vector<xy> coords)
{
    std::cout << "Coords:" << std::endl;
    for (auto &c : coords)
    {
        std::cout << "  (" << c.x << "," << c.y << ")" << std::endl;
    }
}

void day3::run_sim(int half)
{
    auto lines = load_data("../data/day3.txt");

    auto path1 = ParseLine(lines[0]);
    std::cout << "path1size()s:" << path1.size() << std::endl;
//    print_path(path1);
    auto ca = GetCoordsHit(path1);
    std::cout << "ca.size():" << ca.size() << std::endl;
    //    print_coords(ca);
    auto path2 = ParseLine(lines[1]);
    std::cout << "path2.size():" << path2.size() << std::endl;
//    print_path(path2);
    auto cb = GetCoordsHit(path2);
    std::cout << "cb.size():" << cb.size() << std::endl;
    //    print_coords(cb);

    //    DumpFilledGrids(ca, cb);

    auto cc = FindCommon(ca, cb);
//    std::cout << "Common coords:" << std::endl;
//    print_coords(cc);

    int smallest{99999999};
    for (auto &c : cc)
    {
        int dist = abs(c.x) + abs(c.y);
        if (dist < smallest)
            smallest = dist;
    }

    std::cout << "Shortest dist: " <<smallest << std::endl;
}
