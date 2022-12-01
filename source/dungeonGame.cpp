#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits.h>
#include "../headers/map.h"
#include "../headers/party.h"

//forward declarations

//merchant functions
bool buyWeapon(Inventory& inv, int amount, Weapon weapon);
bool buyArmor(Inventory& inv, int amount, Armor armor);
bool buyCookware(Inventory& inv, int amount, Cookware cookware);
bool displayCookware(Inventory& inv);
void displayArmor(Inventory& inv);
void displayWeapons(Inventory& inv);

void merchantMenu(Party& party, Inventory& merchantInv)
{
    short ans{};
    do
    {
        std::cout << "If you're looking to get supplies, you've come to the right place.\nI would be happy to part with some of my wares...for the proper price! \n";

        party.partyInventory.displayInventory();

        std::cout << "Choose one of the following:\n"<<
        "1. Ingredients: To make food, you have to cook raw ingredients.\n"<<
        "2. Cookware: You will need something to cook those ingredients.\n"<<
        "3. Weapons: It's dangerous to go alone, take this!\n"<<
        "4. Armor: If you want to survive monster attacks, you will need some armor.\n"<<
        "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands.\n"<<
        "6. Leave: Make sure you get everything you need, I'm leaving after this sale!\n";
        std::cin >> ans;
        switch (ans)
        {
            case(1):
            {
                std::cout<<"How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)\n";
                int amount{};
                std::cin >> amount;
                if (amount > 0 && amount % 5 == 0 && amount <= party.partyInventory.gold)
                {
                    party.partyInventory.food = amount;
                    party.partyInventory.gold -= amount;
                }
                break;
            }
            case(2):
            {
                std::cout<<"I have a several types of cookware, which one would you like?\nEach type has a different probability of breaking when used, marked with (XX%).\nChoose one of the following:\n";
                displayCookware(merchantInv);
                short input{};
                std::cin >> input;
                if (input <= merchantInv.cookwareInventory.size() && input > 0)
                {
                    short num{};
                    std::cout << "How many do you want to buy?\n";
                    std::cin >> num;
                    if (buyCookware(party.partyInventory, num, merchantInv.cookwareInventory.at(input-1)))
                        std::cout << "bought " << num << " for " << merchantInv.cookwareInventory.at(input-1).price*num;
                }
                break;
            }
            case(3):
            {
                break;
            }
            case(4):
            {
                break;
            }
            case(5):
            {
                break;
            }
            default:
            {
                break;
            }
        }
    } while (ans != 6);
    
}

void update(Map& map, Party& party)
{

}

void npcMenu()
{

}

void roomMenu()
{
    
}

void mainMenu(Map& map)
{
    short ans{};
    do{
        std::cout << "Choose an option: \n"<<
        "1. Move\n"<<
        "2. Exit\n";
        std::cin >> ans;
        if (ans == 1)
        {
            bool moveVar{true};
            while(moveVar)
            {
                char dir{};
                std::cin >> dir;
                moveVar = map.move(dir);
                map.updateMap();
                map.displayMap();
            }
        }
    }while(ans != 2);
}

int main()
{
    std::mt19937 mt{std::random_device{}()}; //random device to seed random number gen

    Player players[4] {};
    std::cout <<"Please enter your name: ";
    std::string mainChar{};
    std::getline(std::cin, mainChar);
    players[0].username = mainChar;

    for (int i{1}; i < 4; ++i)
    {
        std::cout << "Please enter the name of party member " << i;
        std::getline(std::cin, mainChar);
        players[i].username = mainChar;
    }

    std::vector<Armor> playerArmorInv;
    std::vector<Cookware> playerCookwareInv;
    std::vector<Item> playerTreasureInv;
    std::vector<Weapon> playerWeaponInv;
    Inventory playerInventory(playerArmorInv, playerCookwareInv, playerTreasureInv, playerWeaponInv);
    Party party(playerInventory, players);

    std::vector<Armor> merchArmorInv{{"Leather", 10, 5, 100}, {"Chain Mail", 20, 10, 100}, {"Steel", 30, 20, 100}};
    std::vector<Cookware> merchCookwareInv{{"Ceramic Pot", 2, 100, 25}, {"Frying Pan", 10, 100, 10}, {"Cauldron", 20, 100, 2}};
    std::vector<Item> merchTreasureInv;
    std::vector<Weapon> merchWeaponInv{{"Stone Club", 0, 2, 100}, {"IronSpear", 0, 2, 100}, {"Mythril Rapier", 1, 5, 100}, {"Flaming Battle-Axe", 2, 15, 100}, {"Vorpal Longsword", 3, 50, 100}};

    Inventory merchantInv(merchArmorInv, merchCookwareInv, merchTreasureInv, merchWeaponInv);

    merchantMenu(party, merchantInv);


    Map map{0, 0};
    map.resetMap();
    map.randomizeMap(mt);
    map.updateMap();
    map.displayMap();
    
    mainMenu(map);


    return 0;
}

