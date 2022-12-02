
#pragma once
#include <random>
#include <limits>
#include <iostream>

namespace Utils{
    bool randomBool(double odds, std::mt19937& mt); //takes a double value between 0-1 and randomly chooses a number between 0-1 returns true if number is under passed odds
    int randomInt(int lowerBound, int upperBound, std::mt19937& mt); // takes an upper and lower bound and generates an int between them.
    void ignoreLine();
}  