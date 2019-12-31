//
// Created by sbixby on 12/30/19.
//

#include "day9.hpp"
#include <boost/tokenizer.hpp>
#include <math.h>

std::vector<long> day9::ParseLine(const std::string& line, long reserve = 5000)
{
    std::vector<long> opCodes;
    opCodes.reserve(reserve);
    auto sep = boost::char_separator<char>(",");
    auto tok = boost::tokenizer<boost::char_separator<char>>(line, sep);
    int idx=0;
    for (auto& itr : tok)
    {
        opCodes[idx++] = std::stoi(itr);
    }
    return opCodes;
}

long day9::getVal(std::vector<long>& pg, long sp, long pm, long relBase)
{
    int fct = 10;
    for (int i = 0; i < pm; ++i)
    {
        fct *= 10;
    }
    long mode = pg[sp] / fct % 10;
    if (mode == 0)
    {
        return pg[pg[sp + pm]];
    }
    else if (mode == 1)
    {
        return pg[sp + pm];
    }
    else
    {
        return pg[pg[sp + pm] + relBase];
    }
}

void day9::setVal(std::vector<long>& pg, long sp, long pm, long relBase, long newValue)
{
    int fct = 10;
    for (int i = 0; i < pm; ++i)
    {
        fct *= 10;
    }
    long mode = pg[sp] / fct % 10;
    if (mode == 0)
    {
        pg[pg[sp + pm]] = newValue;
    }
    else if (mode == 1)
    {
        pg[sp + pm] = newValue;
    }
    else
    {
        pg[pg[sp + pm] + relBase] = newValue;
    }
}

void day9::runProgram(std::vector<long>& pg, long input, long& output)
{
    long sp      = 0;
    long relBase = 0;
    while (true)
    {
        long opCode = pg[sp] % 100;

        if (opCode == 1)
        {
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
            setVal(pg, sp, 3, relBase, val1 + val2);
            sp += 4;
        }
        else if (opCode == 2)
        {
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
            setVal(pg, sp, 3, relBase, val1 * val2);
            sp += 4;
        }
        else if (opCode == 3)
        {
            std::cout << "set input:" << input << std::endl;
            setVal(pg, sp, 1, relBase, input);
            sp += 2;
        }
        else if (opCode == 4)
        {
            output = getVal(pg, sp, 1, relBase);
            std::cout << "output:" << output << std::endl;
            sp += 2;
        }
        else if (opCode == 5)
        {
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
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
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
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
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
            setVal(pg, sp, 3, relBase, val1 < val2 ? 1 : 0);
            sp += 4;
        }
        else if (opCode == 8)
        {
            long val1 = getVal(pg, sp, 1, relBase);
            long val2 = getVal(pg, sp, 2, relBase);
            setVal(pg, sp, 3, relBase, val1 == val2 ? 1 : 0);
            sp += 4;
        }
        else if (opCode == 9)
        {
            relBase += getVal(pg, sp, 1, relBase);
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
