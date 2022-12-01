// matt
#pragma once
#include <string>

struct Item{
    std::string name;
    unsigned int price;
    unsigned int num;

    //constructor
    Item(std::string p_name = "", unsigned int p_price = 0, unsigned int p_num = 0)
    :name{p_name}, price{p_price}, num{p_num}
    {}
};

struct Cookware : Item
{
    unsigned short breakChance;
    
    //constructor
    Cookware(std::string p_name = "", unsigned int p_price = 0, unsigned int p_num = 0, unsigned short p_breakChance = 0)
    :Item{p_name, p_price, p_num}, breakChance{p_breakChance}
    {}
};

struct Weapon : Item{
    unsigned int attackStat;
    bool equipped;

    //constructor
    Weapon(std::string p_weaponName = "", unsigned int p_attackStat = 0, unsigned int p_price = 0, unsigned int p_num = 0,  bool p_equipped = false)
    :Item{p_weaponName, p_price, p_num}, attackStat{p_attackStat}, equipped{p_equipped}
    {}
};

struct Armor : Item{
    unsigned int defenseStat;
    bool equipped;

    //constructor
    Armor(std::string p_armorName = "", unsigned int p_defenseStat = 0, unsigned int p_price = 0, unsigned int p_num = 0,  bool p_equipped = false)
    :Item{p_armorName, p_price, p_num}, defenseStat{p_defenseStat}, equipped{p_equipped}
    {}
};