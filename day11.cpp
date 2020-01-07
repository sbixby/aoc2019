//
// Created by sbixby on 1/7/20.
//

#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "day11.hpp"
#include "day_base.hpp"

bool day11::runProgram(std::vector<long> &pg, std::vector<long> &inputs, std::vector<long> &outputs, int expOutputCount,
                       long &sp)
{
    long relBase = 0;
    auto inpIt   = inputs.begin();
    while (true)
    {
        long opCode = pg[sp] % 100;

        if (opCode == 1)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            setIntCodeVal(pg, sp, 3, relBase, val1 + val2);
            sp += 4;
        }
        else if (opCode == 2)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            setIntCodeVal(pg, sp, 3, relBase, val1 * val2);
            sp += 4;
        }
        else if (opCode == 3)
        {
            std::cout << "set input:" << *inpIt << std::endl;
            setIntCodeVal(pg, sp, 1, relBase, *inpIt);
            sp += 2;
        }
        else if (opCode == 4)
        {
            long output = getIntCodeVal(pg, sp, 1, relBase);
            std::cout << "output:" << output << std::endl;
            outputs.push_back(output);
            sp += 2;
            if (outputs.size() >= expOutputCount)
            {
                return false;
            }
        }
        else if (opCode == 5)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            if (val1 != 0)
            {
                sp = val2;
            }
            else
            {
                sp += 3;
            }
        }
        else if (opCode == 6)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            if (val1 == 0)
            {
                sp = val2;
            }
            else
            {
                sp += 3;
            }
        }
        else if (opCode == 7)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            setIntCodeVal(pg, sp, 3, relBase, val1 < val2 ? 1 : 0);
            sp += 4;
        }
        else if (opCode == 8)
        {
            long val1 = getIntCodeVal(pg, sp, 1, relBase);
            long val2 = getIntCodeVal(pg, sp, 2, relBase);
            setIntCodeVal(pg, sp, 3, relBase, val1 == val2 ? 1 : 0);
            sp += 4;
        }
        else if (opCode == 9)
        {
            relBase += getIntCodeVal(pg, sp, 1, relBase);
            sp += 2;
        }
        else if (pg[sp] == 99)
        {
            return true;
        }
    }
}

void day11::run_sim(int half)
{
    auto opCodes = ParseLine(load_data("../data/day11.txt")[0]);

    std::vector<xyclr> painted;
    int                currx = 0, curry = 0;
    char               currDir = 'U';
    long               sp      = 0;

    while (true)
    {
        std::vector<long> outputs;
        int currColor;

        auto loc = std::find(painted.begin(), painted.end(), xyclr{currx, curry});
        if (loc!=painted.end()) {
            currColor = loc->color;
        } else {
            currColor = 0;
        }
        std::vector<long> inputs {currColor};

        bool fini = runProgram(opCodes, inputs, outputs, 2, sp);

        if (outputs.size() == 2)
        {
            char newColor = outputs[0];

            if (loc != painted.end())
            {
                loc->color = newColor;
            }
            else
            {
                painted.emplace_back(currx,curry, newColor);
            }


        }
        if (fini)
            break;
    }

    /*
        std::vector<xyclr> test;
        test.emplace_back(1, 2);
        test.emplace_back(4, 3);
        test.emplace_back(7, 0);
        test.emplace_back(9, 12);

        for (auto &it : test)
        {
            std::cout << "it:" << it << std::endl;
        }

        auto  it2 = std::find(test.begin(), test.end(), xyclr{4,4});
        if (it2!=test.end())
        {
            it2->color = 'W';
        }

        std::cout << "After find, it2:" << *it2 << std::endl;
        for (auto &it : test)
        {
            std::cout << "it:" << it << std::endl;
        }
    */
}
