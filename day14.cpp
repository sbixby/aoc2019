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
    }
}

void day14::WalkTree(const d14::reaction& r, int need)
{
    for(auto &p:r.inputs) {
        if (p.name=="ORE") {
            if ()
        }
        WalkTree(reactions[p.name], need*p.qty);
    }
}

void day14::run_sim(int half)
{
    GetReactions(load_data("../data/day14_a.txt"));

    //    for (auto& r : reactions)
    //        std::cout << r << std::endl;

    for (auto& p : reactions)
    {
        std::cout << p.second << std::endl;
    }

    auto &r = reactions["FUEL"];

    WalkTree(r, r.output.qty);

}
