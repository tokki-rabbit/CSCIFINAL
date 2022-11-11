// matt
#pragma once
#include <string>

struct Item{
    std::string name;
    unsigned int price;

    //constructor
    Item(std::string p_name = "", unsigned int p_price = 0)
    :name{p_name}, price{p_price}
    {}
};

struct Food
{
    unsigned int weight{};
};

struct Cookware : Item
{
    unsigned short breakChance;
    
    //constructor
    Cookware(std::string p_name = "", unsigned int p_price = 0, unsigned short p_breakChance = 0)
    :Item{p_name, p_price}, breakChance{p_breakChance}
    {}
};

struct Weapon : Item{
    unsigned int attackStat;
    bool equipped;

    //constructor
    Weapon(std::string p_weaponName = "", unsigned int p_attackStat = 0, unsigned int p_price = 0, bool p_equipped = false)
    :Item{p_weaponName, p_price}, attackStat{p_attackStat}, equipped{p_equipped}
    {}
};

struct Armor : Item{
    unsigned int defenseStat;
    bool equipped;

    //constructor
    Armor(std::string p_armorName = "", unsigned int p_defenseStat = 0, unsigned int p_price = 0, bool p_equipped = false)
    :Item{p_armorName, p_price}, defenseStat{p_defenseStat}, equipped{p_equipped}
    {}
};