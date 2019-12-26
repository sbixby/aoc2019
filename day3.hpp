//
// Created by sbixby on 12/14/19.
//

#ifndef AOC2019_DAY3_HPP
#define AOC2019_DAY3_HPP

#include "day_base.hpp"

class day3 : day_base
{
   public:
    void run_sim(int half) override;

   private:
    static std::vector<dir_len> ParseLine(const std::string& line);
    static std::vector<ln>      MakeLines(std::vector<dir_len> path);
    std::vector<xy>             GetCoordsHit(std::vector<dir_len> path);
    void                        FindDupes(const std::vector<xy>& ch) const;
    static void                 FindShortestDist(std::vector<xy>& ch, xy& c, int& idx, int& dist);
    static std::vector<xy>      FindCrossings(std::vector<ln>& lines);
    static std::vector<xy>      FindCrossings(std::vector<ln>& lines1, std::vector<ln>& lines2);
    void dump_map(std::vector<xy> ch1, std::vector<xy> cross1, std::vector<xy> ch2, std::vector<xy> cross2,
                  std::vector<xy> crossings);
    int  FindSteps(std::vector<xy> coords, std::vector<xy> selfCrosses, xy& commonCross);
};

#endif    // AOC2019_DAY3_HPP
