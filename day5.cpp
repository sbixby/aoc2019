//
// Created by sbixby on 12/25/19.
//

#include "day5.hpp"
#include <boost/tokenizer.hpp>

void day5::runProgram(std::vector<long> pg, int input, int& output)
{
    int sp = 0;
    while (true)
    {
        int opCode = pg[sp] % 100;
        int pm1    = pg[sp] / 100 % 10;
        int pm2    = pg[sp] / 1000 % 10;
        int pm3    = pg[sp] / 10000 % 10;

        if (opCode == 1)
        {
            int val1       = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2       = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
            pg[pg[sp + 3]] = val1 + val2;
            sp += 4;
        }
        else if (opCode == 2)
        {
            int val1       = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2       = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
            pg[pg[sp + 3]] = val1 * val2;
            sp += 4;
        }
        else if (opCode == 3)
        {
            if (pm1 == 0)
                pg[pg[sp + 1]] = input;
            else
            {
                pg[sp + 1] = input;
            }
            sp += 2;
        }
        else if (opCode == 4)
        {
            if (pm1 == 0)
                output = pg[pg[sp + 1]];
            else
            {
                output = pg[sp + 1];
            }

            sp += 2;
            //            std::cout << "output:" << output << std::endl;
        }
        else if (opCode == 5)
        {
            int val1 = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2 = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
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
            int val1 = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2 = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
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
            int val1       = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2       = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
            pg[pg[sp + 3]] = val1 < val2 ? 1 : 0;
            sp += 4;
        }
        else if (opCode == 8)
        {
            int val1       = pm1 == 0 ? pg[pg[sp + 1]] : pg[sp + 1];
            int val2       = pm2 == 0 ? pg[pg[sp + 2]] : pg[sp + 2];
            pg[pg[sp + 3]] = val1 == val2 ? 1 : 0;
            sp += 4;
        }
        else if (pg[sp] == 99)
        {
            break;
        }
    }
}

void day5::run_sim(int half)
{
    auto opCodes = ParseLine(load_data("../data/day5.txt")[0]);
    int  outCode;

    if (half == 1)
    {
        runProgram(opCodes, 1, outCode);
        std::cout << "outCode:" << outCode << std::endl;
    }
    else
    {
        int inp = 5;
        runProgram(opCodes, inp, outCode);
        std::cout << "in:" << inp << "  out:" << outCode << std::endl;
    }
}
