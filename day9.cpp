//
// Created by sbixby on 12/30/19.
//

#include "day9.hpp"
#include "day_base.hpp"

void day9::runProgram(std::vector<long>& pg, long input, long& output)
{
    long sp      = 0;
    long relBase = 0;
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
            std::cout << "set input:" << input << std::endl;
            setIntCodeVal(pg, sp, 1, relBase, input);
            sp += 2;
        }
        else if (opCode == 4)
        {
            output = getIntCodeVal(pg, sp, 1, relBase);
            std::cout << "output:" << output << std::endl;
            sp += 2;
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
            break;
        }
    }
}

void day9::run_sim(int half)
{
    long outCode = 0;
    //    std::vector<long> opCodes {104,1125899906842624,99};

    if (half == 1)
    {
        auto opCodes = ParseLine(load_data("../data/day9.txt")[0]);
        std::cout << "Before opCodes.size():" << opCodes.size() << std::endl;
        runProgram(opCodes, 1, outCode);
        std::cout << "After opCodes.size():" << opCodes.size() << std::endl;
        std::cout << "outCode:" << outCode << std::endl;
    }
    else
    {
        auto opCodes = ParseLine(load_data("../data/day9.txt")[0]);

        std::cout << "Before opCodes.size():" << opCodes.size() << std::endl;
        runProgram(opCodes, 2, outCode);
        std::cout << "After opCodes.size():" << opCodes.size() << std::endl;
        std::cout << "outCode:" << outCode << std::endl;
    }
}
