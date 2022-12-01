#pragma once
#include<iostream>
#include"player.h"
#include <vector>

class Inventory
{
public:
    std::vector<Armor> armorInventory;
    std::vector<Cookware> cookwareInventory;
    std::vector<Item> treasureInventory;
    std::vector<Weapon> weaponInventory;
    int gold;
    int food;

    Inventory(std::vector<Armor> p_armorInventory, std::vector<Cookware> p_cookwareInventory, std::vector<Item> p_treasureInventory, std::vector<Weapon> p_weaponInventory, int gold = 100, int food = 0)
    :gold{gold}, food{food}
    {
        for (auto k : p_armorInventory)
            armorInventory.push_back(k);
        for (auto k : p_cookwareInventory)
            cookwareInventory.push_back(k);
        for (auto k : p_treasureInventory)
            treasureInventory.push_back(k);
        for (auto k : p_weaponInventory)
            weaponInventory.push_back(k);
    }

    void addItem(Item item);
    void addCookware(Cookware cookware);
    void addArmor(Armor armor);
    void addWeapon(Weapon weapon);
    void removeItem(std::vector<Item>::iterator i);
    void removeCookware(std::vector<Cookware>::iterator i);
    void removeArmor(std::vector<Armor>::iterator i);
    void removeWeapon(std::vector<Weapon>::iterator i);
    void displayInventory();


};

class Party
{
public:
    int fullness;
    Inventory partyInventory;
    Player player[4];

    Party(Inventory partyInventory, Player p_player[4], int fullness = 50)
    :partyInventory{partyInventory}, fullness{fullness}
    {
        for (int i{}; i < 4; ++i)
            player[i] = p_player[i];
    } 
};

