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

void day14::WalkTree(std::string& name, int need)
{
    if (name == "ORE")
    {
        oreConsumed += need;
        counts["ORE"] += need;
        return;
    }
    // Get the reaction of interest.
    auto& r = reactions[name];
    // See if we have enough to satisfy this condition
    if (counts[name] >= need)
    {
        counts[name] -= need;
        std::cout << "Satisfied need of " << need << " " << name << std::endl;
        return;
    }

    // Not enough.  Go through the inputs and
    // walk down the tree to get more of the input.
    std::cout << r.output.name << ", " << r.output.qty << std::endl;
    for (auto &inp:r.inputs) {
        WalkTree(inp.name, inp.qty*need);
    }

    // Now consume each of the inputs and move back up the stack.
    for (auto& inp : r.inputs)
    {
        counts[inp.name] -= inp.qty;
    }
}

void day14::run_sim(int half)
{
    //    GetReactions(load_data("../data/day14_a.txt"));
    GetReactions({"7 A, 2 B => 1 FUEL", "10 ORE => 10 A", "5 ORE => 1 B"});
//    GetReactions({"10 ORE => 1 FUEL"});

    //    for (auto& r : reactions)
    //        std::cout << r << std::endl;

    for (auto& p : reactions)
    {
        std::cout << "Reaction: " << p.second << std::endl;
    }
    for (auto& p : counts)
    {
        std::cout << "Counts for " << p.first << ":" << p.second << std::endl;
    }
    std::cout << std::endl;

    std::string root{"FUEL"};
    WalkTree(root, 1);

    std::cout << "oreConsumed:" << oreConsumed << std::endl;
}
