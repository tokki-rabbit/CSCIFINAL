#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits.h>
#include <fstream>

#include "../headers/map.h"
#include "../headers/party.h"
#include "../headers/utils.h"
#include "../headers/monster.h"

//forward declarations

//merchant functions
bool buyWeapon(Inventory& inv, int amount, Weapon weapon);
bool buyArmor(Inventory& inv, int amount, Armor armor);
bool buyCookware(Inventory& inv, int amount, Cookware cookware);
bool displayCookware(Inventory& inv);
void displayArmor(Inventory& inv);
void displayWeapons(Inventory& inv);

void initializeMonsterPool(std::vector<Monster>& monsterPool, std::string file)
{
    std::fstream f(file, std::ios_base::in);
    Monster monster;
    while(!f.eof())
    {
        std::string line{};
        std::getline(f, line,',');
        monster.setName(line);

        std::getline(f, line);
        monster.setDiff(std::stoi(line));

        monsterPool.push_back(monster);
    }
    f.close();
} 

void misfortune(Party& party, std::mt19937& mt, bool locked)
{
    std::cout << "\nOh no! Misfortune!!\n";
    int misfortuneType{Utils::randomInt(1, 10, mt)};

    if (misfortuneType == 1)
    {
        if (Utils::randomBool(0.5, mt))
        {
            int id{Utils::randomInt(0, party.partyInventory.weaponInventory.size()-1, mt)};
            std::cout << "Oh no! Your " << party.partyInventory.weaponInventory.at(id).name << " broke!\n";
            if (party.partyInventory.weaponInventory.at(id).num > 1)
                party.partyInventory.weaponInventory.at(id).num -= 1;
            else
            {
                std::vector<Weapon>::iterator it{party.partyInventory.weaponInventory.begin() + id};
                party.partyInventory.removeWeapon(it);
            }
        }
        else
        {
            int id{Utils::randomInt(0, party.partyInventory.armorInventory.size()-1, mt)};
            std::cout << "Oh no! Your " << party.partyInventory.armorInventory.at(id).name << " broke!\n";
            if (party.partyInventory.armorInventory.at(id).num > 1)
                party.partyInventory.armorInventory.at(id).num -= 1;
            else
            {
                std::vector<Armor>::iterator it{party.partyInventory.armorInventory.begin() + id};
                party.partyInventory.removeArmor(it);
            }
        }
    }
    else if(misfortuneType > 1 && misfortuneType < 4)
    {
        std::cout<< "You've been robbed! You lost 10kg of food!\n";
        party.partyInventory.food -= 10;
    }
    else if (misfortuneType >= 4 && misfortuneType < 7)
    {
        int partyID{Utils::randomInt(0, party.players.size()-1, mt)};
        std::cout << party.players.at(partyID).username << " has gotten food poisoning! -10 fullness!\n";
        party.players.at(partyID).fullness -= 10;
    }
    else if (misfortuneType >= 7 && misfortuneType <= 10 && locked)
    {
        int partyID{Utils::randomInt(1, party.players.size()-1, mt)};
        std::cout << party.players.at(partyID).username << " has been locked in the previous room with no escape!!\n";
        party.killPartyMember(partyID);
        std::cout << "Your party's size has been reduced to " << party.players.size() << " members.\n";
    }
}

void merchantMenu(Party& party, Inventory& merchantInv, std::mt19937& mt)
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
        Utils::ignoreLine();
        switch (ans)
        {
            case(1):
            {
                std::cout<<"How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)\n";
                int amount{};
                std::cin >> amount;
                Utils::ignoreLine();
                if (amount > 0 && amount % 5 == 0 && amount <= party.partyInventory.gold)
                {
                    party.partyInventory.food += amount;
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
                Utils::ignoreLine();
                if (input <= merchantInv.cookwareInventory.size() && input > 0)
                {
                    short num{};
                    std::cout << "How many do you want to buy?\n";
                    std::cin >> num;
                    Utils::ignoreLine();
                    if (buyCookware(party.partyInventory, num, merchantInv.cookwareInventory.at(input-1)))
                        std::cout << "bought " << num << " for " << merchantInv.cookwareInventory.at(input-1).price*num;
                }
                break;
            }
            case(3):
            {
                std::cout<<"I have a plentiful collection of weapons to choose from, what would you like?\nNote that some of them provide you a special bonus in combat, marked by an attack stat.\nChoose one of the following:\n";
                displayWeapons(merchantInv);
                short input{};
                std::cin >> input;
                Utils::ignoreLine();
                if (input <= merchantInv.weaponInventory.size() && input > 0)
                {
                    short num{};
                    std::cout << "How many do you want to buy?\n";
                    std::cin >> num;
                    Utils::ignoreLine();
                    if (buyWeapon(party.partyInventory, num, merchantInv.weaponInventory.at(input-1)))
                        std::cout << "bought " << num << " for " << merchantInv.weaponInventory.at(input-1).price*num;
                }
                break;
            }
            case(4):
            {
                std::cout<<"I have a plentiful collection of armor to choose from, what would you like?\nNote that some of them provide you a special bonus in combat, marked by a defense stat.\nChoose one of the following:\n";
                displayArmor(merchantInv);
                short input{};
                std::cin >> input;
                Utils::ignoreLine();
                if (input <= merchantInv.armorInventory.size() && input > 0)
                {
                    short num{};
                    std::cout << "How many do you want to buy?\n";
                    std::cin >> num;
                    Utils::ignoreLine();
                    if (buyArmor(party.partyInventory, num, merchantInv.armorInventory.at(input-1)))
                        std::cout << "bought " << num << " for " << merchantInv.armorInventory.at(input-1).price*num;
                }
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
bool monsterFight(Party& party, std::vector<Monster>& monsterPool, std::mt19937& mt, int diffLevel)
{
    bool temp{false}, win{false};
    int lowerMonsterIDBound{};
    int higherMonsterIDBound{};

    for(int i{}; i < monsterPool.size(); ++i)
    {
        if (!temp && monsterPool.at(i).getDiff() == diffLevel)
        {
            lowerMonsterIDBound = i;
            higherMonsterIDBound= i;
            temp = true;
        }
        else if (temp && monsterPool.at(i).getDiff() == diffLevel)
            ++higherMonsterIDBound;
    }

    int randomizedMonsterID{Utils::randomInt(lowerMonsterIDBound, higherMonsterIDBound, mt)};

    std::cout << "You've encountered a " << monsterPool[randomizedMonsterID].getName() << "! What do you do?\n"; 
    std::cout << "1. Attack\n2. Surrender\n";
    short choice{};
    do
    {
        std::cin >> choice;
        Utils::ignoreLine();
        if (choice == 1)
        {
            double totalNumWeapons{};
            double totalAttackStat{};
            double numUnique{};
            double d{};
            double a{};
            for (const auto k : party.partyInventory.weaponInventory)
            {
                totalAttackStat += k.attackStat*k.num;
                totalNumWeapons += k.num;
                ++numUnique;
            }
            if (numUnique >= 4)
                d = 4;
            for (const auto k : party.partyInventory.armorInventory)
            {
                a += k.defenseStat*k.num;
            }
            double attack{((double)Utils::randomInt(1, 6, mt)*totalNumWeapons+totalAttackStat)-(((double)Utils::randomInt(1, 6, mt)*monsterPool.at(randomizedMonsterID).getDiff())/a)};
            std::cout << "You've attacked for a value of " << attack << "!\n";
            if (attack > 0)
            {
                win = true;
                bool keydrop{Utils::randomBool(0.1, mt)};
                std::cout << "It was enough! From the battle you've gained: 10 gold, 5 kg of ingedients, and " << keydrop << " keys!\n";
                party.partyInventory.gold += 10;
                party.partyInventory.food += 5;
                if (keydrop)
                    party.keys += 1;
            }
            else
            {
                int maxFoodLost = party.partyInventory.food > 30 ? 30 : party.partyInventory.food;
                int ingredientsLost{Utils::randomInt(0, maxFoodLost, mt)};
                std::cout << "You were defeated by the monster!\nYou have lost: " << 0.25*party.partyInventory.gold << " gold, " << ingredientsLost << " kg of ingredients, and ";
                int playersLost{};
                for (int i{1}; i < party.players.size(); ++i)
                {
                    if (Utils::randomBool(0.1, mt))
                    {
                        ++playersLost;
                        party.killPartyMember(i);
                    }
                }
                std::cout << playersLost << " party member(s)!\n";
            }
            choice = 2;
        }
        else if (choice == 2)
        {
            std::cout << "One of your party members has fallen to the monster!\n";
            int partyMemberID{Utils::randomInt(1, party.players.size()-1, mt)};
            std::cout << "RIP " << party.players[partyMemberID].username << "!\n";
            party.killPartyMember(partyMemberID);
        }
    } while (choice != 2);
    return win;
}

void NPCpuzzle(Party& party, Inventory& merchantInv, std::vector<Monster>& monsterpool, std::mt19937& mt)
{
    std::fstream f("npcpuzzle.txt", std::ios_base::in);
    
    std::vector<std::string> questions;
    std::vector<std::string> answers;

    bool answered{false};
    
    while (!f.eof())
    {
        std::string line;
        std::getline(f,line,'~');
        questions.push_back(line);

        std::getline(f,line);
        answers.push_back(line);
    }
    f.close();

    int questionID{Utils::randomInt(0, questions.size()-1, mt)};

    std::cout << "Answer this riddle for me:\n";

    std::cout << questions[questionID] << '\n';
    short ans{};
    do{
        std::string answer{};
        std::getline(std::cin, answer);
        Utils::ignoreLine;
        //std::cout << answer << " = " << answers[questionID] << '\n';
        if (answer != answers[questionID])
        {
            std::cout << "Thats wrong do you want to try again?\n1. Yes\n2. No\n";
            std::cin >> ans;
            Utils::ignoreLine();
        }
        else
        {
            std::cout << "Correct!\n";
            answered = true;
            ans = 2;
        }
    }while (ans != 2);   
    if (!answered){
        std::cout << "If you are not going to answer my riddle why waste my time!\n";
        monsterFight(party, monsterpool, mt, party.roomscleared+1);
    }
    else
    {
        short mm{};
        std::cout << "Do you want to shop at the merchant?\n1. Yes\n 2. No\n";
        std::cin >> mm;
        Utils::ignoreLine();
        if (mm == 1)
            merchantMenu(party, merchantInv, mt);
    }
}

bool doorPuzzle(std::mt19937& mt)
{
    std::vector<std::string> rps{"Rock", "Paper", "Scisscors"};

    bool passed{false};

    for (int i{}; i < 3; ++i)
    {
        int ans{};
        std::cout << "Tries left: " << 3 - i<< ".\n";
        std::cout<<"Rock: 1"<<"\nPaper: 2"<<"\nScissor: 3\n";
        int choice {Utils::randomInt(0, 2, mt)};
        do{
            std::cin>>ans;
            Utils::ignoreLine();
        }while(!(ans > 0 && ans < 4));
        std::cout << "You chose: " << rps[ans-1] << '\n';
        std::cout << "I chose: " << rps[choice] << '\n';
        
        if ((rps[choice] == "Rock" && rps[ans-1] == "Paper") 
        || (rps[choice] == "Paper" && rps[ans-1] == "Scissors")
        || (rps[choice] == "Scissors" && rps[ans-1] == "Rock"))
        {
            passed = true;
            break;
        }
    }
    return passed;
}

void exploring(Map& map, Party& party, Pos& playerLocation, std::vector<Monster>& monsterPool, std::mt19937& mt)
{
    if (map.isExplored(playerLocation.y, playerLocation.y))
    {
        std::cout << "You can't investigate in the same spot twice!\n";
        return;
    }
    map.explore();
    if (Utils::randomBool(0.1, mt))
    {  
        std::cout << "You found a key!\n";
        party.keys += 1;
        for (auto& k : party.players)
        {
            if (Utils::randomBool(0.5, mt))
                k.fullness -= 1;
        }
    }
    else if (Utils::randomBool(0.2, mt))
    {
        Item treasure("Treasure Clump", Utils::randomInt(party.roomscleared*2+10, party.roomscleared*2+30, mt), 1);
        std::cout << "You found a Treasure Clump worth: " << treasure.price << "gold!\n";
        party.partyInventory.addItem(treasure);
        for (auto& k : party.players)
        {
            if (Utils::randomBool(0.5, mt))
                k.fullness -= 1;
        }
    }
    else if (Utils::randomBool(0.2, mt))
        monsterFight(party, monsterPool, mt, party.roomscleared+1);
    for (auto& k : party.players)
    {
        if (Utils::randomBool(0.5, mt))
            k.fullness -= 1;
    }
}

void npcMenu(Map& map, Party& party, Inventory& merchantInv, std::vector<Monster>& monsterpool, bool& run, std::mt19937& mt)
{
    short ans{};

    std::cout << "NPC: Choose an option: \n"<<
    "1. Move\n"<<
    "2. Speak to NPC\n"<<
    "3. Give up\n";
    std::cin >> ans;
    Utils::ignoreLine();
    if (ans == 1)
    {
        bool moveVar{true};
        while(moveVar)
        {
            char dir{};
            std::cin >> dir;
            Utils::ignoreLine();
            moveVar = map.move(dir);
            map.updateMap();
            map.displayMap();
            if (moveVar)
            {
                party.decPartyMembersFullness(mt);
                ++party.angerlevel;
            }
        }
    }
    else if (ans == 2)
    {
        NPCpuzzle(party, merchantInv, monsterpool, mt);
        map.explore();
    }
    else if (ans == 3)
    {
        run = false;
        std::cout <<"GAME OVER!\n";
        return;
    }
}

void roomMenu(Map& map, Party& party, Inventory& merchantInv, std::vector<Monster>& monsterPool, bool& run, std::mt19937& mt)
{
    short ans{};

    std::cout << "Room: Choose an option: \n"<<
    "1. Move\n"<<
    "2. Open door\n"<<
    "3. Give up\n";
    std::cin >> ans;
    Utils::ignoreLine();
    if (ans == 1)
    {
        bool moveVar{true};
        while(moveVar)
        {
            char dir{};
            std::cin >> dir;
            Utils::ignoreLine();
            moveVar = map.move(dir);
            map.updateMap();
            map.displayMap();
            if (moveVar)
            {
                party.decPartyMembersFullness(mt);
                ++party.angerlevel;
            }
        }
    }
    else if (ans == 2)
    {
        if (party.keys > 0)
        {
            if(monsterFight(party, monsterPool, mt, party.roomscleared+2))
            {
                ++party.roomscleared;
                map.explore();
                if (Utils::randomBool(0.6, mt))
                    misfortune(party, mt, true);
            }
            else
            {
                if (Utils::randomBool(0.6, mt))
                    misfortune(party, mt, true);
            }
            --party.keys;
        }
        else
        {
            std::cout << "You have no key to open the door instead you are faced with a puzzle to solve!\n";
            if(doorPuzzle(mt))
            {
                if(monsterFight(party, monsterPool, mt, party.roomscleared+2))
                {
                    ++party.roomscleared;
                    map.explore();
                    if (Utils::randomBool(0.6, mt))
                        misfortune(party, mt, true);
                }
                else 
                {
                    if (Utils::randomBool(0.6, mt))
                    misfortune(party, mt, true);
                }
                --party.keys;
            }
            else 
            {
                int partyID{Utils::randomInt(1, party.players.size()-1, mt)};
                std::cout << party.players.at(partyID).username << " has been locked in the puzzle room with no escape!!\n";
                party.killPartyMember(partyID);
                std::cout << "Your party's size has been reduced to " << party.players.size() << " members.\n";
            }
        }
    }
    else if (ans == 3)
    {
        run = false;
        std::cout <<"GAME OVER!\n";
        return;
    }
}

bool cookEat(Party& party, std::mt19937& mt)
{
    bool flag{false};
    int ans{};
    std::cout<<"How many kg of ingredients are you using(product of 5)?\n";
    do
    {
        std::cin>>ans;
        Utils::ignoreLine();
    }while (!(ans > 0 && ans < party.partyInventory.food && ans % 5 == 0));
    int cookwareID{Utils::randomInt(0, party.partyInventory.cookwareInventory.size()-1, mt)};
    if (Utils::randomBool((double)party.partyInventory.cookwareInventory.at(cookwareID).breakChance/100.0, mt) && ans <= party.partyInventory.food)
    {
        std::cout << "Your " << party.partyInventory.cookwareInventory.at(cookwareID).name << " broke!\n";
        std::cout << "You lost " << ans << " kg of food!\n";
        party.partyInventory.food -= ans;
        if (party.partyInventory.cookwareInventory.at(cookwareID).num > 1)
            party.partyInventory.cookwareInventory.at(cookwareID).num -= 1;
        else
        {
            std::vector<Cookware>::iterator it{party.partyInventory.cookwareInventory.begin() + cookwareID};
            party.partyInventory.removeCookware(it);
        }
        return false;
    }
    if(ans > 0 && ans % 5 == 0 && ans <= party.partyInventory.food)
    {
        flag = true;
        for(auto& k : party.players)
        {
            k.fullness+=ans/5;
        }
    }
    return flag;
}

void mainMenu(Map& map, Party& party, Inventory& merchantInv, Pos& partyLocation, std::vector<Monster>& monsterPool, bool& run, std::mt19937& mt)
{
    short ans{};
    std::cout << "Main: Choose an option: \n"<<
    "1. Move\n"<<
    "2. Investigate\n"<<
    "3. Pick a Fight\n"<<
    "4. Cook and Eat\n"<<
    "5. Give up\n";
    std::cin >> ans;
    std::cin.ignore(std::numeric_limits<short>::max(),'\n');
    Utils::ignoreLine();
    if (ans == 1)
    {
        bool moveVar{true};
        while(moveVar)
        {
            char dir{};
            std::cin >> dir;
            Utils::ignoreLine();
            moveVar = map.move(dir);
            map.updateMap();
            map.displayMap();
            if (moveVar)
            {
                party.decPartyMembersFullness(mt);
                ++party.angerlevel;
            }
        }
    }
    else if (ans == 2)
    {
        exploring(map, party, partyLocation, monsterPool, mt);
    }
    else if (ans == 3)
    {
        monsterFight(party, monsterPool, mt, party.roomscleared+1);
    }
    else if (ans == 4)
    {
        cookEat(party, mt);
    }
    else if (ans == 5)
    {
        run = false;
        std::cout <<"GAME OVER!\n";
        return;
    }
}

void update(Map& map, Party& party, Inventory& merchantInv, Pos& partyLocation, std::vector<Monster>& monsterPool, bool& run, std::mt19937& mt)
{
    map.updateMap();
    party.status();
    map.displayMap();

    if (party.angerlevel >= 100)
    {
        std::cout << "Oh no! The socerer has grown too angry and destroyed the party!\nGAME OVER!\n";
        run = false;
        return;
    }
    if (party.players.at(0).fullness <= 0)
    {
        std::cout << "Oh no! You've died of hunger!\n GAME OVER!\n";
        run = false;
        return;
    }
    for (int i{1}; i < party.players.size(); ++i)
    {
        if (party.players.at(i).fullness <= 0)
        {
            std::cout << "Oh no! " << party.players.at(i).username <<  " has died of hunger!!\n";
            party.killPartyMember(i);
        }
    }
    if (party.players.size() < 2)
    {
        std::cout << "You've lost too many friends to go on!\nGAME OVER!\n";
        run = false;
        return;
    }

    if (party.roomscleared >= 5)
        map.setDungeonExit(11, 11);
    partyLocation = map.getPlayerLocation();
    
    if (map.isDungeonExit(partyLocation.y, partyLocation.x))
    {
        run = false;
        std::cout << "Congrats!!!! YOU WON!\n";
    }


    if (Utils::randomBool(0.4, mt))
        misfortune(party, mt, false);

    if (map.isNPCLocation(partyLocation.y, partyLocation.x) && map.isDiscovered(partyLocation.y, partyLocation.x))
        npcMenu(map, party, merchantInv, monsterPool, run, mt);
    else if (map.isRoomLocation(partyLocation.y, partyLocation.x) && map.isDiscovered(partyLocation.y, partyLocation.x))
        roomMenu(map, party, merchantInv, monsterPool, run, mt);
    else
        mainMenu(map, party, merchantInv, partyLocation, monsterPool, run, mt);

}

int main()
{
    std::mt19937 mt{std::random_device{}()}; //random device to seed random number gen


    // Party initialization
    std::vector<Player> players = std::vector<Player>(5);
    std::cout <<"Please enter your name: ";
    std::string mainChar{};
    std::getline(std::cin, mainChar);
    players[0].username = mainChar;

    for (int i{1}; i < 5; ++i)
    {
        std::cout << "Please enter the name of party member " << i << ": ";
        std::getline(std::cin, mainChar);
        players[i].username = mainChar;
    }

    // player Inventory initialization
    std::vector<Armor> playerArmorInv;
    std::vector<Cookware> playerCookwareInv;
    std::vector<Item> playerTreasureInv;
    std::vector<Weapon> playerWeaponInv;
    Inventory playerInventory(playerArmorInv, playerCookwareInv, playerTreasureInv, playerWeaponInv);
    Party party(playerInventory, players);

    //monster pool initialization
    std::vector<Monster> monsterPool;
    initializeMonsterPool(monsterPool, "monsters.txt");


    //merchant initialization
    std::vector<Armor> merchArmorInv{{"Leather", 1, 5, 100}, {"Chain Mail", 2, 10, 100}, {"Steel", 3, 15, 100}};
    std::vector<Cookware> merchCookwareInv{{"Ceramic Pot", 2, 100, 25}, {"Frying Pan", 10, 100, 10}, {"Cauldron", 20, 100, 2}};
    std::vector<Item> merchTreasureInv;
    std::vector<Weapon> merchWeaponInv{{"Stone Club", 0, 2, 100}, {"IronSpear", 0, 2, 100}, {"Mythril Rapier", 1, 5, 100}, {"Flaming Battle-Axe", 2, 15, 100}, {"Vorpal Longsword", 3, 50, 100}};

    Inventory merchantInv(merchArmorInv, merchCookwareInv, merchTreasureInv, merchWeaponInv);

    merchantMenu(party, merchantInv, mt);

    // Map initialization
    Map map{0, 0};

    map.resetMap();
    map.randomizeMap(mt);
    map.updateMap();

    Pos partyLocation;


    bool run{true};
    // Main game loop
    while (run)
    {
        update(map, party, merchantInv, partyLocation, monsterPool, run, mt);
    }

    return 0;
}

