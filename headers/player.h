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
    Weapon weapon;

    Player(std::string username = "", Weapon weapon = Weapon())
    :username{username}, weapon{weapon}
    {}
    void changeweapon(Weapon new_Weapon);
    void track_gold();
};