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
            auto        subTok = std::regex_replace(itr, std::regex("^ +| +$|( ) +"), "$1");
            int         sp     = subTok.find(' ');
            d14::pair   p;
            std::string st1 = subTok.substr(0, sp);
            std::string st2 = subTok.substr(sp + 1);
            p.qty           = std::stoi(st1);
            p.name          = st2;
            pairs.push_back(p);
        }
        d14::reaction r;
        r.inputs              = {pairs.begin(), pairs.end() - 1};
        r.output              = pairs.back();
        finder[r.output.name] = &r;
        reactions.push_back(r);
    }
}

d14::reaction& day14::FindReaction(std::string name)
{
    for (auto& r : reactions)
    {
        if (r.output.name == name)
        {
            return r;
        }
    }
}

void day14::WalkTree(d14::reaction r)
{
}

void day14::run_sim(int half)
{
    GetReactions(load_data("../data/day14_a.txt"));

    for (auto& r : reactions)
        std::cout << r << std::endl;

    auto& fuel = finder["FUEL"];
    //    d14::reaction& fuel = FindReaction("FUEL");

    auto x = fuel->output.name;
    std::cout << "found: " << x << std::endl;
    std::cout << "fuel.output.qty:" << fuel->output.qty << std::endl;
}
