//
// Created by sbixby on 1/8/20.
//

#include "day13.hpp"

bool day13::runProgram(std::vector<long> &pg, std::vector<long> &inputs, std::vector<long> &outputs, int expOutputCount,
                       long &sp, long &relBase)
{
    auto inpIt = inputs.begin();
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
            //            std::cout << "set input:" << *inpIt << std::endl;
            if (inpIt == inputs.end())
            {
                std::cout << "Ran out of inputs!" << std::endl;
                exit(-1);
            }
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

void day13::run_sim(int half)
{
    auto opCodes = ParseLine(load_data("../data/day13.txt")[0]);

    std::cout << "opCodes.size():" << opCodes.size() << std::endl;

    std::vector<long> inputs;
    std::vector<long> outputs;
    long              sp = 0, relBase = 0;

    runProgram(opCodes, inputs, outputs, 99999999, sp, relBase);
    std::cout << "outputs.size():" << outputs.size() << std::endl;

    int blockTiles=0;
    for (auto it = outputs.begin(); it != outputs.end(); it += 3) {
        if (*(it+2)==2)
            blockTiles++;
    }
    std::cout << "blockTiles:" << blockTiles << std::endl;
}
