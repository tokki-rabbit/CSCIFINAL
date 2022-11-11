
#include<iostream>
#include<string>
#include "item.h"

class Player
{
private:
    std::string username;
    Weapon weapon;

public:
    
    void changeweapon(Weapon new_Weapon);
    void inventory(Cookware num_cock, Weapon num_weapon, Armor num_armor);
    void track_gold();
};