//
// Created by sbixby on 12/28/19.
//

#include "day7.hpp"
#include <sstream>
#include <algorithm>

bool day7::runProgram(std::vector<long>& pg, int phase, int inputValue, int& output, bool returnOnOutput, int& sp)
{
    int input;
    if (sp > 0)
        input = inputValue;
    else
        input = phase;

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
            // If it was phase, now it's inputValue.
            input = input;
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
            if (returnOnOutput)
            {
                return false;
            }
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
            return true;
        }
    }
}

void day7::MakePermutations(std::vector<int> v, std::vector<std::vector<int>>& perms)
{
    std::sort(v.begin(), v.end());
    perms.push_back(v);
    while (std::next_permutation(v.begin(), v.end()))
        perms.push_back(v);
}

namespace
{
void comp(std::vector<int> a, std::vector<int> b)
{
    bool changed = false;
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
        {
            if (!changed)
            {
                std::cout << "  Differs:";
                changed = true;
            }
            std::cout << " " << i << ":" << a[i] << "->" << b[i];
        }
        if (changed)
            std::cout << std::endl;
    }
}

std::string toStr(std::vector<int> v)
{
    std::stringstream ss;
    for (int i = 0; i < v.size() - 1; ++i)
    {
        ss << v[i] << ",";
    }
    ss << v.back();
    return ss.str();
}

int vtoi(std::vector<int> v)
{
    int tot = 0;
    for (int& it : v)
    {
        tot *= 10;
        tot += it;
    }
    return tot;
}

}    // namespace

void day7::run_sim(int half)
{
    auto opCodes = ParseLine(load_data("../data/day7.txt")[0]);

    if (half == 1)
    {
        std::vector<std::vector<int>> inputSets;

        // _a
        //     inputSets.push_back({4,3,2,1,0});
        // _b
        //     inputSets.push_back({0,1,2,3,4});
        // _c
        //     inputSets.push_back({1,0,4,3,2});

        MakePermutations({0, 1, 2, 3, 4}, inputSets);

        std::sort(inputSets.begin(), inputSets.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) { return vtoi(a) < vtoi(b); });

        int largest = 0;

        for (auto& inputSet : inputSets)
        {
            int outa, outb, outc, outd, oute;

            auto pg = opCodes;
            int  sp = 0;
            runProgram(pg, inputSet[0], 0, outa, false, sp);
            pg = opCodes;
            sp = 0;
            runProgram(pg, inputSet[1], outa, outb, false, sp);
            pg = opCodes;
            sp = 0;
            runProgram(pg, inputSet[2], outb, outc, false, sp);
            pg = opCodes;
            sp = 0;
            runProgram(pg, inputSet[3], outc, outd, false, sp);
            pg = opCodes;
            sp = 0;
            runProgram(pg, inputSet[4], outd, oute, false, sp);

            if (oute > largest)
                largest = oute;
        }

        std::cout << "largest:" << largest << std::endl;
    }
    else
    {
        std::vector<std::vector<int>> inputSets;

        // _d
        //        inputSets.push_back({9, 8, 7, 6, 5});
        //        opCodes = {3,  26, 1001, 26,   -4, 26, 3,  27,   1002, 27, 2,  27, 1, 27, 26,
        //                   27, 4,  27,   1001, 28, -1, 28, 1005, 28,   6,  99, 0,  0, 5};
        // _e
        //        inputSets.push_back({9, 7, 8, 5, 6});
        //        opCodes = {3,    52, 1001, 52, -5,   52, 3,    53, 1,  52, 56,   54,   1007, 54, 5,  55,   1005, 55,
        //        26,
        //                   1001, 54, -5,   54, 1105, 1,  12,   1,  53, 54, 53,   1008, 54,   0,  55, 1001, 55,   1,
        //                   55, 2,    53, 55,   53, 4,    53, 1001, 56, -1, 56, 1005, 56,   6,    99, 0,  0,    0, 0,
        //                   10};
        // Puzzle
        MakePermutations({5, 6, 7, 8, 9}, inputSets);

        std::sort(inputSets.begin(), inputSets.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) { return vtoi(a) < vtoi(b); });

        int              largest = 0;
        std::vector<long> pga = opCodes, pgb = opCodes, pgc = opCodes, pgd = opCodes, pge = opCodes;

        for (auto& inputSet : inputSets)
        {
            int output = 0, spa = 0, spb = 0, spc = 0, spd = 0, spe = 0;
            while (true)
            {
                if (runProgram(pga, inputSet[0], output, output, true, spa))
                    break;
                if (runProgram(pgb, inputSet[1], output, output, true, spb))
                    break;
                if (runProgram(pgc, inputSet[2], output, output, true, spc))
                    break;
                if (runProgram(pgd, inputSet[3], output, output, true, spd))
                    break;
                if (runProgram(pge, inputSet[4], output, output, true, spe))
                    break;
            }
            if (output > largest)
                largest = output;
        }
        std::cout << "largest:" << largest << std::endl;
    }
}
