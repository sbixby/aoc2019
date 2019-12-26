//
// Created by sbixby on 12/12/19.
//

#include "day1.hpp"

void day1::run_sim(int half)
{
    auto             lines = load_data("../data/day1_1.txt");
    std::vector<int> masses;
    for (auto &s : lines)
        masses.push_back(std::stoi(s));

    int sum = 0;
    for (auto &m : masses)
    {
        int f = m / 3 - 2;
        sum += f;
    }

    if (half == 1)
    {
        std::cout << "Fuel requirement:" << sum << std::endl;
        return;
    }

    int sum2 = 0;

    for (auto &m : masses)
    {
        int msum = 0;
        int f    = m;
        do
        {
            f = f / 3 - 2;
            if (f >= 0)
            {
                msum += f;
            }
        } while (f >= 0);
        sum2 += msum;
    }

    std::cout << "Updated fuel requirement:" << sum2 << std::endl;
}
