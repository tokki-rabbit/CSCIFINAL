#include<iostream>
#include "../headers/monster.h"

//getters 
std::string Monster::getName()
{
    return name;
}
int Monster::getDiff()
{
    return difficulty;
}

//setters
void Monster::setName(std::string new_name)
{
    name = new_name;
}
void Monster::setDiff(int new_difficulty)
{
    difficulty = new_difficulty;
}
