//
// Created by sbixby on 12/27/19.
//

#include "day6.hpp"
#include <boost/algorithm/string.hpp>

void day6::getLR(std::string line, std::string &orbl, std::string &orbr)
{
    std::vector<std::string> splits;
    boost::split(splits, line, [](char c) { return c == ')'; });
    orbl = splits[0];
    orbr = splits[1];
}

void day6::run_sim(int half)
{
    const auto &lines = load_data("../data/day6.txt");

    std::vector<std::shared_ptr<orb>> orbs;
    std::string                       orbNameL, orbNameR;
    std::shared_ptr<orb>              sporbl, sporbr;

    for (auto &line : lines)
    {
        getLR(line, orbNameL, orbNameR);

        auto it =
            std::find_if(orbs.begin(), orbs.end(), [orbNameL](std::shared_ptr<orb> &o) { return o->name == orbNameL; });

        if (it != orbs.end())
            sporbl = *it;
        else
        {
            sporbl = std::make_shared<orb>(orbNameL);
            orbs.push_back(sporbl);
        }

        it =
            std::find_if(orbs.begin(), orbs.end(), [orbNameR](std::shared_ptr<orb> &o) { return o->name == orbNameR; });
        if (it != orbs.end())
            sporbr = *it;
        else
        {
            sporbr = std::make_shared<orb>(orbNameR);
            orbs.push_back(sporbr);
        }

        sporbl->orbiting.push_back(sporbr);
        sporbr->orbits = sporbl;
    }

    if (half == 1)
    {
        int count{0};
        for (auto &o : orbs)
        {
            std::shared_ptr<orb> optr = o;
            while (optr->name != "COM")
            {
                optr = optr->orbits;
                count++;
            }
        }
        std::cout << "count:" << count << std::endl;
    }
    else
    {
        auto you =
            std::find_if(orbs.begin(), orbs.end(), [orbNameL](std::shared_ptr<orb> &o) { return o->name == "YOU"; });
        auto san =
            std::find_if(orbs.begin(), orbs.end(), [orbNameL](std::shared_ptr<orb> &o) { return o->name == "SAN"; });

        auto youOrbit  = (*you)->orbits;
        auto sanOrbit  = (*san)->orbits;

        std::vector<std::shared_ptr<orb>> youToRoot = GetPathToRoot(youOrbit);
        std::vector<std::shared_ptr<orb>> sanToRoot = GetPathToRoot(sanOrbit);

        int shortest = 999999;
        for (int yidx = 0; yidx < youToRoot.size(); ++yidx)
        {
            for (int sidx = 0; sidx < sanToRoot.size(); ++sidx)
            {
                if (youToRoot[yidx]->name==sanToRoot[sidx]->name) {
                    if (yidx+sidx<shortest) {
                        shortest = yidx+sidx;
                    }
                }
            }
        }
        std::cout << "shortest:" << shortest << std::endl;

/*
        std::cout << "you: ";
        for(auto &o:youToRoot) {
            std::cout << o->name << " ";
        }
        std::cout << std::endl << "san: ";
        for(auto &o:sanToRoot) {
            std::cout << o->name << " ";
        }
        std::cout << std::endl;
*/

    }
}

std::vector<std::shared_ptr<orb>> day6::GetPathToRoot(std::shared_ptr<orb> thisNode)
{
    std::vector<std::shared_ptr<orb>> path;
    while (thisNode != nullptr) {
        path.push_back(thisNode);
        thisNode = thisNode->orbits;
    }
    return path;
}
