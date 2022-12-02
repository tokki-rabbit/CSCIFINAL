//eric 
#pragma once
#include<iostream>
#include<string>
#include <vector>
#include "item.h"

class Player
{
public:
    std::string username;
    int fullness;
    Weapon weapon;

    Player(std::string username = "", Weapon weapon = Weapon(), int fullness = 50)
    :username{username}, weapon{weapon}, fullness{fullness}
    {}
};