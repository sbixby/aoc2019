//
// Created by sbixby on 1/7/20.
//

#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <map>
#include <sstream>
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

        std::cout << "OpCode " << opCode << "  (pg[sp]: " << pg[sp] << ")" << std::endl;
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
            //            std::cout << "set input:" << *inpIt << std::endl;
            setIntCodeVal(pg, sp, 1, relBase, *inpIt);
            sp += 2;
        }
        else if (opCode == 4)
        {
            long output = getIntCodeVal(pg, sp, 1, relBase);
            //            std::cout << "output:" << output << std::endl;
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
        else if (opCode == 99)
        {
            return true;
        }
        else
        {
            std::cout << "Unknown opcode: " << opCode << " at sp:" << sp << std::endl;
            exit(-1);
        }
    }
}

void day11::run_sim(int half)
{
    std::map<char, std::tuple<char, char>> directions{
        {'N', {'W', 'E'}}, {'E', {'N', 'S'}}, {'S', {'E', 'W'}}, {'W', {'S', 'N'}}};

    auto opCodes = ParseLine(load_data("../data/day11.txt")[0]);

    std::vector<xyclr> painted;
    int                currx = 0, curry = 0;
    char               currDir = 'N';
    long               sp      = 0;

    bool firstWhite = half == 2;

    while (true)
    {
        std::vector<long> outputs;
        int               currColor;

        const xyclr &t   = xyclr{currx, curry};
        auto         loc = std::find(painted.begin(), painted.end(), t);
        if (loc != painted.end())
        {
            currColor = loc->color;
        }
        else
        {
            if (firstWhite)
            {
                currColor  = 1;
                firstWhite = false;
                std::cout << "First color is white" << std::endl;
            }
            else
            {
                currColor = 0;
            }
        }

        std::vector<long> inputs{currColor};

        bool fini = runProgram(opCodes, inputs, outputs, 2, sp);

        if (outputs.size() == 2)
        {
            //            std::cout << "in:" << inputs[0] << " clr:" << outputs[0] << " dirch:" << outputs[1] <<
            //            std::endl;

            char newColor = outputs[0];

            if (loc != painted.end())
            {
                loc->color = newColor;
            }
            else
            {
                painted.emplace_back(currx, curry, newColor);
            }

            //            std::cout << "CurrDir: " << currDir;
            currDir = outputs[1] == 0 ? std::get<0>(directions.find(currDir)->second)
                                      : std::get<1>(directions.find(currDir)->second);
            if (currDir == 'N')
                curry++;
            else if (currDir == 'E')
                currx++;
            else if (currDir == 'S')
                curry--;
            else
                currx--;
            //            std::cout << "   newDir:" << currDir << std::endl;
        }
        else if (fini)
        {
            break;
        }
        else
        {
            std::cout << "Unexpected output count!" << std::endl;
            exit(-1);
        }
    }

    if (half == 1)
    {
        std::cout << "painted.size():" << painted.size() << std::endl;
    }
    else
    {
    }
}
