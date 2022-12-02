#include "../headers/utils.h"

bool Utils::randomBool(double odds, std::mt19937& mt)
{
    std::uniform_real_distribution<> distrib(0.0, 1.0);

    return (distrib(mt) <=  odds);
}

int Utils::randomInt(int lowerBound, int upperBound, std::mt19937& mt)
{
    std::uniform_int_distribution<> distrib(lowerBound, upperBound);

    return distrib(mt);
}

void Utils::ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}