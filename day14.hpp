//
// Created by sbixby on 1/12/20.
//

#ifndef AOC2019_DAY14_HPP
#define AOC2019_DAY14_HPP

#include "day_base.hpp"
#include <map>
#include <utility>

namespace d14
{
struct pair
{
    long         qty = 0;
    std::string name;
    pair() = default;
    pair(long qty, std::string name)
        : qty(qty)
        , name(std::move(name))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const pair& o);
};

struct reaction
{
    std::vector<pair> inputs;
    pair              output;
    reaction() = default;
    explicit reaction(std::vector<pair> inputs)
        : inputs({inputs.begin(), inputs.end() - 1})
        , output(inputs.back())
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const reaction& o);
};

}    // namespace d14

class day14 : day_base
{
   public:
    void run_sim(int half) override;
    void GetReactions(const std::vector<std::string>& lines);

   private:
    std::map<std::string, d14::reaction> reactions;
    std::map<std::string, long>           counts;
    long                                  oreConsumed = 0;

    void WalkTree(d14::reaction& r, long mult);
};

#endif    // AOC2019_DAY14_HPP
