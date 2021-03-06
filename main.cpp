#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"
#include "day13.hpp"
#include "day14.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    int day  = std::stoi(argv[1]);
    int half = std::stoi(argv[2]);

    switch (day)
    {
        case 1:
            day1().run_sim(half);
            break;
        case 2:
            day2().run_sim(half);
            break;
        case 3:
            day3().run_sim(half);
            break;
        case 4:
            day4().run_sim(half);
            break;
        case 5:
            day5().run_sim(half);
            break;
        case 6:
            day6().run_sim(half);
            break;
        case 7:
            day7().run_sim(half);
            break;
        case 8:
            day8().run_sim(half);
            break;
        case 9:
            day9().run_sim(half);
            break;
        case 10:
            day10().run_sim(half);
            break;
        case 11:
            day11().run_sim(half);
            break;
        case 12:
            day12().run_sim(half);
            break;
        case 13:
            day13().run_sim(half);
            break;
        case 14:
            day14().run_sim(half);
            break;
        default:
            std::cout << "Day " << day << " not implemented yet!" << std::endl;
    }

    return 0;
}
