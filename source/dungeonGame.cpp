#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits.h>
#include "../headers/map.h"

void merchantMenu()
{
    short ans{};
    do
    {
        std::cout << "Merchant store enter number: \n"<<
        "Choose one of the following:\n"<<
        "1. Ingredients: To make food, you have to cook raw ingredients.\n"<<
        "2. Cookware: You will need something to cook those ingredients.\n"<<
        "3. Weapons: It's dangerous to go alone, take this!\n"<<
        "4. Armor: If you want to survive monster attacks, you will need some armor.\n"<<
        "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands.\n"<<
        "6. Leave: Make sure you get everything you need, I'm leaving after this sale!\n";
        std::cin >> ans;
    } while (ans != 6);
    
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
            }
        }
    }while(ans != 2);
}

int main()
{
    std::mt19937 mt{std::random_device{}()};
    merchantMenu();
    Map map(0, 0);
    map.resetMap();
    map.randomizeMap(mt);
    map.updateMap();
    map.displayMap();
    
    mainMenu(map);


    return 0;
}

