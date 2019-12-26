//
// Created by sbixby on 12/25/19.
//

#include "day4.hpp"
void day4::run_sim(int half)
{
    int fv = 178416;
    int lv = 676461;

    if (half == 1)
    {
        int count = 0;
        for (int index = fv; index <= lv; index++)
        {
            std::string sv = std::to_string(index);
            if ((sv[0] == sv[1] || sv[1] == sv[2] || sv[2] == sv[3] || sv[3] == sv[4] || sv[4] == sv[5]) &&
                (sv[0] <= sv[1] && sv[1] <= sv[2] && sv[2] <= sv[3] && sv[3] <= sv[4] && sv[4] <= sv[5]))
                count++;
        }
        std::cout << "count:" << count << std::endl;
    }
    else
    {
        int count = 0;
        for (int index = fv; index <= lv; index++)
        {
            std::string sv = std::to_string(index);
            if (sv[0] > sv[1] || sv[1] > sv[2] || sv[2] > sv[3] || sv[3] > sv[4] || sv[4] > sv[5])
                continue;

            if (
                (sv[0]==sv[1] && sv[1]!=sv[2]) ||
                    (sv[0]!=sv[1] && sv[1]==sv[2] && sv[2]!= sv[3]) ||
                    (sv[1]!=sv[2] && sv[2]==sv[3] && sv[3]!= sv[4]) ||
                    (sv[2]!=sv[3] && sv[3]==sv[4] && sv[4]!= sv[5]) ||
                    (sv[3]!=sv[4] && sv[4]==sv[5])
                ) {
                count++;
            }

        }
        std::cout << "count:" << count << std::endl;
    }
}
