//
// Created by sbixby on 12/12/19.
//

#include "day2.hpp"

void day2::writeVec(std::vector<int> v)
{
    for (int i = 0; i < v.size() - 1; ++i)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << v[v.size() - 1] << std::endl;
}

void day2::run_sim(int half)
{
    if (half == 1)
    {
        auto ans = runProgram(12, 2);
        std::cout << "First half ans: " << ans << std::endl;
    }

    for (int noun = 0; noun < 100; ++noun)
    {
        for (int verb = 0; verb < 100; ++verb)
        {
            auto ans = runProgram(noun, verb);
            if (ans == 19690720)
            {
                std::cout << "Second half ans: " << (100 * noun + verb) << std::endl;
                std::cout << "noun:" << noun << std::endl;
                std::cout << "verb:" << verb << std::endl;
//                return;
            }
        }
    }
}

int day2::runProgram(int noun, int verb)
{
    auto pg = opCodes;

    pg[1] = noun;
    pg[2] = verb;

    int sp = 0;

    while (true)
    {
        if (pg[sp] == 1)
        {
            pg[pg[sp + 3]] = pg[pg[sp + 1]] + pg[pg[sp + 2]];
            sp += 4;
        }
        else if (pg[sp] == 2)
        {
            pg[pg[sp + 3]] = pg[pg[sp + 1]] * pg[pg[sp + 2]];
            sp += 4;
        }
        else if (pg[sp] == 99)
        {
            break;
        }
    }
    return pg[0];
}
