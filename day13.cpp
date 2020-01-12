//
// Created by sbixby on 1/8/20.
//

#include <iomanip>
#include <thread>
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
            if (inpIt == inputs.end())
            {
                std::cout << "Ran out of inputs!" << std::endl;
                exit(-1);
            }
            setIntCodeVal(pg, sp, 1, relBase, *inpIt);
            inpIt++;
            sp += 2;
        }
        else if (opCode == 4)
        {
            long output = getIntCodeVal(pg, sp, 1, relBase);
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

void day13::PrintScreen(std::vector<std::vector<char>> &scrn, std::vector<long> &outputs, bool first)
{
    static std::string charMap{" #*=@"};
    static int         maxx = 0, maxy = 0;
    if (first)
    {
        for (auto it = outputs.begin(); it != outputs.end(); it += 3)
        {
            if (*(it) > maxx)
                maxx = *(it);
            if (*(it + 1) > maxy)
                maxy = *(it + 1);
        }
        scrn.reserve(maxy);
        for (int i = 0; i < maxy + 1; ++i)
        {
            scrn.emplace_back(maxx + 1, ' ');
        }
    }

    for (auto it = outputs.begin(); it != outputs.end(); it += 3)
    {
        if (*(it) == -1)
        {
            std::cout << "Score:" << *(it + 2) << std::endl;
        }
        if (*(it + 1) <= maxy)
            scrn[*(it + 1)][*(it)] = charMap[*(it + 2)];
        else
            std::cout << "Off screen! y=" << *(it + 1) << std::endl;
    }
    for (int y = 0; y < maxy + 1; ++y)
    {
        for (int x = 0; x < maxx + 1; ++x)
        {
            std::cout << scrn[y][x];
        }
        std::cout << std::endl;
    }
}

void day13::run_sim(int half)
{
    auto opCodes = ParseLine(load_data("../data/day13.txt")[0]);

    std::vector<long>              inputs;
    std::vector<long>              outputs;
    long                           sp = 0, relBase = 0;
    std::vector<std::vector<char>> scrn;

    if (half == 1)
    {
        runProgram(opCodes, inputs, outputs, 99999999, sp, relBase);
    }

    if (half == 2)
    {
        opCodes[0] = 2;
        inputs.push_back(0);
        double score;
        long   paddleX = -1;

        // Run until board is created; first score code will jump out.
        while (true)
        {
            std::vector<long> subOuts;
            runProgram(opCodes, inputs, subOuts, 3, sp, relBase);
            if (subOuts[0] == -1)
            {
                score = subOuts[2];
                break;
            }
            if (subOuts[2] == 3)
            {
                paddleX = subOuts[0];
            }
            outputs.insert(outputs.end(), subOuts.begin(), subOuts.end());
        }

        // Run for turns
        long ballMoves = 0;
        while (true)
        {
            long              dx;
            std::vector<long> subOuts;
            if (runProgram(opCodes, inputs, subOuts, 3, sp, relBase))
            {
                std::cout << "Game over, score: " << score <<  "  ball moves: " << ballMoves << std::endl;
                break;
            }
            if (subOuts[0] == -1)
            {
                score = subOuts[2];
            }
            else
            {
                if (subOuts[2] == 3)
                {
                    paddleX = subOuts[0];
                }
                if (subOuts[2] == 4)
                {
                    ballMoves++;
                    dx        = paddleX - subOuts[0];
                    inputs[0] = dx > 0 ? -1 : dx < 0 ? 1 : 0;
                }
            }
        }
    }
}
