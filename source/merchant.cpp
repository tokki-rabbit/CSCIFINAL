#include <iostream>
#include <string>
#include <vector>

#include "../headers/party.h"

void sellTreasure(Inventory& inv)
{

}
bool buyWeapon(Inventory& inv, int amount, Weapon weapon)
{
    if (amount > 0 && weapon.price*amount <= inv.gold)
    {
        weapon.num = amount;
        inv.addWeapon(weapon);
        inv.gold -= amount*weapon.price;
        return true;
    }
    return false;
}
bool buyArmor(Inventory& inv, int amount, Armor armor)
{
    if (amount>0 && armor.price*amount <= inv.gold)
    {
        armor.num = amount;
        inv.addArmor(armor);
        inv.gold -= amount*armor.price;
        return true;
    }
    return false;
}
bool buyCookware(Inventory& inv, int amount, Cookware cookware)
{
    if (amount>0 && cookware.price*amount <= inv.gold)
    {
        cookware.num = amount;
        inv.addCookware(cookware);
        inv.gold -= amount*cookware.price;
        return true;
    }
    return false;
}
void displayCookware(Inventory& inv)
{
    for(int i{}; i < inv.cookwareInventory.size(); ++i)
        std::cout << i+1 << ". " <<  inv.cookwareInventory.at(i).name <<  " [" << inv.cookwareInventory.at(i).price << " gold] " << inv.cookwareInventory.at(i).breakChance << "% break chance\n";
}
void displayArmor(Inventory& inv)
{
    for(int i{}; i < inv.cookwareInventory.size(); ++i)
        std::cout << i+1 << ". " <<  inv.armorInventory.at(i).name <<  " [" << inv.armorInventory.at(i).price << " gold] " << inv.armorInventory.at(i).defenseStat << "defense\n";
}
void displayWeapons(Inventory& inv)
{
    for(int i{}; i < inv.weaponInventory.size(); ++i)
        std::cout << i+1 << ". " <<  inv.weaponInventory.at(i).name <<  " [" << inv.weaponInventory.at(i).price << " gold] " << inv.weaponInventory.at(i).attackStat << "attack\n";
}