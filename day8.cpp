//
// Created by sbixby on 12/30/19.
//

#include "day8.hpp"
void day8::run_sim(int half)
{
    auto inputString = load_data("../data/day8.txt")[0];

    //    char max='0';
    //    for(char &c:inputString) {
    //        if(c > max) max=c;
    //    }
    //    std::cout << "max:" << max << std::endl;
    // Max=2

    if (half == 0)
    {
        int minZeros = 99999, times12 = 0;
        for (int imgIdx = 0; imgIdx < inputString.size(); imgIdx += (6 * 25))
        {
            int counts[3] = {0, 0, 0};
            for (int ridx = 0; ridx < 6; ++ridx)
            {
                for (int cidx = 0; cidx < 25; ++cidx)
                {
                    counts[(int)(inputString[imgIdx + 25 * ridx + cidx] - '0')]++;
                }
            }
            if (counts[0] < minZeros)
            {
                minZeros = counts[0];
                times12  = counts[1] * counts[2];
            }
        }
        std::cout << "times12:" << times12 << std::endl;
    }
    else
    {
        char img[150];
        std::fill(img, img+150,' ');

        for (int ridx = 0; ridx < 6; ++ridx)
        {
            for (int cidx = 0; cidx < 25; ++cidx)
            {
                for (int imgIdx = 0; imgIdx < inputString.size(); imgIdx += (6 * 25))
                {
                    char c = inputString[imgIdx + 25 * ridx + cidx];
                    if (c=='0' || c=='1') {
                        img[25 * ridx + cidx] = c;
                        break;
                    }
                }
            }
        }

        for (int ridx = 0; ridx < 6; ++ridx)
        {
            for (int cidx = 0; cidx < 25; ++cidx) {
                char c = img[25*ridx+cidx];
                char oc = c=='0' ? ' ':'*';
                std::cout << oc;
            }
            std::cout << std::endl;
        }
    }
}
