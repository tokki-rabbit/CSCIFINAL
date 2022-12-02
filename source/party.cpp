//eric
#include<iostream>
#include"../headers/party.h"

void Inventory::addItem(Item item)
{
    treasureInventory.push_back(item);
}
void Inventory::addCookware(Cookware cookware)
{
    cookwareInventory.push_back(cookware);
}
void Inventory::addArmor(Armor armor)
{
    armorInventory.push_back(armor);
}
void Inventory::addWeapon(Weapon weapon)
{
    weaponInventory.push_back(weapon);
}
void Inventory::removeItem(std::vector<Item>::iterator i)
{
    treasureInventory.erase(i);
}
void Inventory::removeCookware(std::vector<Cookware>::iterator i)
{
    cookwareInventory.erase(i);
}
void Inventory::removeArmor(std::vector<Armor>::iterator i)
{
    armorInventory.erase(i);
}
void Inventory::removeWeapon(std::vector<Weapon>::iterator i)
{
    weaponInventory.erase(i);
}
void Inventory::displayInventory()
{
    std::cout << "+-------------+\n"<<
    "| INVENTORY   |\n"<<
    "+-------------+\n"<<
    "| Gold        | " << gold << '\n'<<
    "| Ingredients | " << food << " kg\n"<<
    "| Cookware    | ";
    for (auto& k : cookwareInventory)
        std::cout << "| " << k.name << ": " << k.num << " |";
    std::cout << "\n| Weapons     | ";
    for (auto& k : weaponInventory)
        std::cout << "| " << k.name << ": " << k.num << " |";
    std::cout<<"\n| Armor       | ";
    for (auto& k : armorInventory)
        std::cout << "| " << k.name << ": " << k.num << " |";
    std::cout<<"\n| Treasures   | ";
    for (auto& k : treasureInventory)
        std::cout << "| " << k.name << ": " << k.num << " |";
    std::cout <<'\n';
    
}

void Party::status()
{
    std::cout << "\n+-------------+\n"<<
    "| STATUS      |\n"<<
    "+-------------+\n"<<
    "| Rooms Cleared: " << roomscleared <<  " | Keys: " << keys << " | Anger Level: " << angerlevel << '\n';
    partyInventory.displayInventory();
    std::cout << "+-------------+\n"<<
    "| PARTY       |\n"<<
    "+-------------+\n";
    for (int i{}; i < players.size(); ++i)
    {
        std::cout << "| " << players[i].username << " | Fullness: " << players[i].fullness << '\n';
    }
    std::cout << "+-------------+\n";

}

void Party::decPartyMembersFullness(std::mt19937& mt)
{
    for (int i{}; i < players.size(); ++i)
    {
        if(Utils::randomBool(0.20, mt))
            players[i].fullness -=1;
    }
}

void Party::killPartyMember(int partyMemberID)
{
    for (std::vector<Player>::iterator it{players.begin()}; it != players.end();)
    {
        if (partyMemberID == std::distance(players.begin(), it))
        {
            players.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
