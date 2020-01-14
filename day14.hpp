//
// Created by sbixby on 1/12/20.
//

#ifndef AOC2019_DAY14_HPP
#define AOC2019_DAY14_HPP

#include "day_base.hpp"
#include <map>

namespace d14
{
struct pair
{
    int                  qty;
    std::string          name;
    friend std::ostream& operator<<(std::ostream& os, const pair& o);
};

struct reaction
{
    std::vector<pair>    inputs;
    pair                 output;
    friend std::ostream& operator<<(std::ostream& os, const reaction& o);
};

}    // namespace d14

class day14 : day_base
{
   public:
    void                 run_sim(int half) override;
    void                 GetReactions(const std::vector<std::string>& lines);

   private:
    std::vector<d14::reaction>            reactions;
    std::map<std::string, d14::reaction*> finder;
    void                                  WalkTree(d14::reaction r);
};

#endif    // AOC2019_DAY14_HPP
