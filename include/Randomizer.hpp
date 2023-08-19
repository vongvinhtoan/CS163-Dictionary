#pragma once

#include <random>
#include <chrono>

class Randomizer
{
public:
    static Randomizer& getInstance();
    int nextInt(int min, int max);

private:
    Randomizer();
    Randomizer(const Randomizer&) = delete;
    Randomizer& operator=(const Randomizer&) = delete;
    Randomizer(Randomizer&&) = delete;
    Randomizer& operator=(Randomizer&&) = delete;

    int seed;
    std::default_random_engine generator;
};