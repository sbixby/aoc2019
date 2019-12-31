//
// Created by sbixby on 12/27/19.
//

#ifndef AOC2019_DAY6_HPP
#define AOC2019_DAY6_HPP

#include <utility>
#include <memory>

#include "day_base.hpp"

struct orb
{
    orb() = default;
    explicit orb(std::string name)
        : name{std::move(name)}
        , orbits{nullptr} {};
    std::string                       name;
    std::shared_ptr<orb>              orbits;
    std::vector<std::shared_ptr<orb>> orbiting;
};

class day6 : day_base
{
   public:
    void run_sim(int half) override;

    void getLR(std::string line, std::string& orbl, std::string& orbr);
    static std::vector<std::shared_ptr<orb>> GetPathToRoot(std::shared_ptr<orb> thisNode);
};


#endif    // AOC2019_DAY6_HPP
