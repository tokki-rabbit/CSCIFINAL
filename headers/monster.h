#include <fstream>
#include <vector>
#include <string>

#include "utils.h"

class Monster{
private:
    std::string name;
    int difficulty;

public:
    //getters
    std::string getName();
    int getDiff();

    //setters
    void setName(std::string name);
    void setDiff(int difficulty);

    //constructor
    Monster(std::string name = "", int difficulty = 1)
    :name{name}, difficulty{difficulty}
    {}

};