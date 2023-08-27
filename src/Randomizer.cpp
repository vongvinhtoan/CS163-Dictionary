#include <Randomizer.hpp>

Randomizer& Randomizer::getInstance()
{
    static Randomizer instance;
    return instance;
}

int Randomizer::nextInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

Randomizer::Randomizer()
    : seed(std::chrono::system_clock::now().time_since_epoch().count())
    , generator(seed)
{
}

// How to use:
// int main()
// {
//     std::cout << Randomizer::getInstance().nextInt(0, 100) << std::endl;
//     std::cout << Randomizer::getInstance().nextInt(0, 100) << std::endl;
//     std::cout << Randomizer::getInstance().nextInt(0, 100) << std::endl;
//     std::cout << Randomizer::getInstance().nextInt(0, 100) << std::endl;
//     return 0;
// }