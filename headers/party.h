#pragma once
#include<iostream>
#include"player.h"
#include <vector>
#include "utils.h"
#include <random>

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
    int roomscleared;
    int angerlevel;
    int keys;

    Inventory partyInventory;
    std::vector<Player> players = std::vector<Player>(5);

    Party(Inventory partyInventory, std::vector<Player> p_player = std::vector<Player>(5), int roomscleared = 0, int angerlevel = 0, int keys = 0)
    :partyInventory{partyInventory}, roomscleared{roomscleared}, angerlevel{angerlevel}, keys{keys}
    {
        for (int i{}; i < 5; ++i)
            players[i] = p_player[i];
    } 

    void status();

    void decPartyMembersFullness(std::mt19937& mt);
    void killPartyMember(int partyMemberID);

};

