//
// Created by sbixby on 1/12/20.
//

#include <regex>
#include "day14.hpp"

namespace d14
{
std::ostream& operator<<(std::ostream& os, const pair& o)
{
    os << "(" << o.qty << " " << o.name << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const reaction& o)
{
    for (int i = 0; i < o.inputs.size(); ++i)
    {
        if (i > 0)
            os << ", ";
        os << o.inputs[i];
    }
    os << " => " << o.output;
    return os;
}
}    // namespace d14

void day14::GetReactions(const std::vector<std::string>& lines)
{
    reactions.clear();
    for (auto& line : lines)
    {
        auto sep = boost::char_separator<char>(",=>");
        auto tok = boost::tokenizer<boost::char_separator<char>>(line, sep);

        std::vector<d14::pair> pairs;
        for (auto& itr : tok)
        {
            auto subTok = std::regex_replace(itr, std::regex("^ +| +$|( ) +"), "$1");
            int  sp     = subTok.find(' ');
            pairs.emplace_back(std::stoi(subTok.substr(0, sp)), subTok.substr(sp + 1));
        }
        d14::reaction r{pairs};
        reactions.insert(std::pair<std::string, d14::reaction>(r.output.name, r));
        counts[r.output.name] = 0;
    }
    counts["ORE"] = 0;
}

void day14::WalkTree(d14::reaction& r, long mult)
{
    // Assumes ORE is only child of a reaction
    if (r.inputs[0].name == "ORE")
    {
        while (counts["ORE"] < r.inputs[0].qty)
        {
            counts["ORE"] += r.inputs[0].qty;
            oreConsumed += r.inputs[0].qty;
        }
        counts["ORE"] -= r.inputs[0].qty;
        counts[r.output.name] += r.output.qty;
        return;
    }

    // For each input
    for (auto& inp : r.inputs)
    {
        // Iterate to get enough
        while (counts[inp.name] < inp.qty)
        {
            WalkTree(reactions[inp.name],1);
        }
        // Consume what we need
        counts[inp.name] -= inp.qty;
    }
    counts[r.output.name] += r.output.qty;
}

void day14::run_sim(int half)
{
    GetReactions(load_data("../data/day14_b.txt"));
    long trillion = 1000000000000;

    WalkTree(reactions["FUEL"],1);
    long multiplier = trillion/oreConsumed;
    std::cout << "oreConsumed:" << oreConsumed << std::endl;

//    std::cout << "Remaining counts:" << std::endl;
//    for(auto &cp:counts) {
//        std::cout << cp.first << " : " << cp.second << std::endl;
//    }

    if (half == 2)
    {
        std::cout << "Trillion/oreconsumed:" << multiplier << std::endl;

        // Clear the counts
        oreConsumed = 0;
        for (auto& p : counts)
        {
            p.second = 0;
        }

        // Multiply the top-level quantity by the starting point
        auto& r = reactions["FUEL"];
        for (auto& inp : r.inputs)
        {
            inp.qty *= multiplier;
        }
        WalkTree(reactions["FUEL"],1);
        std::cout << "much-fuel, oreConsumed:" << oreConsumed << std::endl;
    }
}
