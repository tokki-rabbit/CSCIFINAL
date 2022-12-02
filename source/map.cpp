#include "../headers/map.h"
#include <vector>
#include <random>

 
Map::Map(int p_npc_count = 0, int p_room_count = 0)
:npc_count_{p_npc_count}, room_count_{p_room_count}
{
    player_position_ = Pos();
}

void Map::resetMap()
{
    npc_positions_.clear();
    room_positions_.clear();
    for(int row{}; row < num_rows_; ++row)
    {
        for(int col{}; col < num_cols_; ++col)
        {
            map_data_[row][col] =  UNEXPLORED;
        }
    }
}

bool Map::isNPCLocation(int row, int col)
{
    for (const auto& pos : npc_positions_)
    {
        if (pos.y == row && pos.x == col)
            return true;
    }
    return false;
}

bool Map::addNPC(int row, int col)
{
    npc_positions_.push_back(Pos(col, row, false));
    return true;
}

bool Map::addRoom(int row, int col)
{
    room_positions_.push_back(Pos(col,row,true));
    return true;
}

bool Map::isRoomLocation(int row, int col)
{
    for (const auto& pos : room_positions_)
    {
        if (pos.y == row && pos.x == col)
            return true;
    }
    return false;
}

void Map::updateMap()
{
    //update the shown npc locations
    for (auto& pos : npc_positions_)
    {
        if (player_position_.y == pos.y && player_position_.x == pos.x && map_data_[pos.y][pos.x] != NPC)
            pos.discovered = true;
        if (pos.discovered)
            map_data_[pos.y][pos.x] = NPC;
        else if (!pos.discovered && map_data_[pos.y][pos.x] != UNEXPLORED)
            map_data_[pos.y][pos.x] = EXPLORED;
    }
    //update the shown room locations
    for (auto& pos : room_positions_)
    {
        if (!pos.discovered)
            map_data_[pos.y][pos.x] = EXPLORED;
        else
            map_data_[pos.y][pos.x] = ROOM;
    }
}

void Map::explore()
{
    bool flag{false};
    for(auto& k : room_positions_)
    {
        if (k.y == player_position_.y && k.x == player_position_.x)
        {
            k.discovered = false;
            flag = true;
        }
    }
    for(auto& k : npc_positions_)
    {
        if (k.y == player_position_.y && k.x == player_position_.x)
        {
            k.discovered = false;
            flag = true;
        }
    }
    if (!flag)
    {
        map_data_[player_position_.y][player_position_.x] = EXPLORED;
    }
}

void Map::randomizeMap(std::mt19937& mt)
{
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    double probability{5.0/144.0};
    //randomize the npc locations
    while(npc_count_ < max_npcs_)
    {
        for (int i{}; i < num_rows_; ++i)
        {
            for (int j{}; j < num_cols_; ++j)
            {
                if (distrib(mt) < probability && !isNPCLocation(i, j) && npc_count_ < max_npcs_)
                {
                    this->addNPC(i, j);
                    ++npc_count_;
                }
            }
        }
    }
    //randomize the room locations
    while(room_count_ < max_rooms_)
    {
        for (int i{}; i < num_rows_; ++i)
        {
            for (int j{}; j < num_cols_; ++j)
            {
                if (distrib(mt) < probability && !isNPCLocation(i, j) && !isRoomLocation(i, j) && room_count_ < max_rooms_)
                {
                    this->addRoom(i, j);
                    ++room_count_;
                }
            }
        }
    }
}

void Map::displayMap()
{
    for(int i{}; i < num_rows_; ++i)
    {
        for (int j{}; j < num_cols_; ++j)
        {
            if (j == player_position_.x && i == player_position_.y)
                std::cout << PARTY;
            else
                std::cout << map_data_[i][j];
        }
        std::cout << '\n';
    }
}

void Map::setDungeonExit(int row, int col)
{
    map_data_[row][col] = EXIT;
}

bool Map::isDungeonExit(int row, int col)
{
    if (map_data_[row][col] == 'E')
        return true;
    return false;
}

int Map::getRoomCount()
{
    return room_count_;
}
int Map::getNPCCount()
{
    return npc_count_;
}
int Map::getNumRows()
{
    return num_rows_;
}
int Map::getNumCols()
{
    return num_cols_;
}

Pos Map::getPlayerLocation()
{
    return player_position_;
}

bool Map::isOnMap(int row, int col)
{
    if(row<0 || row>11 || col<0 || col>11)
    {
        return false;
    }
    return true;
}
bool Map::isExplored(int row, int col)
{
    if (map_data_[row][col] == EXPLORED)
        return true;
    return false;
}
bool Map::isDiscovered(int row, int col)
{
    for (const auto& k : room_positions_)
    {
        if (k.y == row && k.x == col)
        {
            return k.discovered;
        }
    }
    for (const auto& k : npc_positions_)
    {
        if (k.y == row && k.x == col)
        {
            return k.discovered;
        }
    }
    return false;
}

bool Map::move(char dir)
{
    switch (dir)
    {
        case('w'):
        {
            if (this->isOnMap(player_position_.x, player_position_.y-1))
                player_position_.y = player_position_.y-1;
            break;
        }
        case('a'):
        {
            if (this->isOnMap(player_position_.x-1, player_position_.y))
                player_position_.x = player_position_.x-1;
            break;
        }
        case('s'):
        {
            if (this->isOnMap(player_position_.x, player_position_.y+1))
                player_position_.y = player_position_.y+1;
            break;
        }
        case('d'):
        {
            if (this->isOnMap(player_position_.x+1, player_position_.y))
                player_position_.x = player_position_.x+1;
            break;
        }
        case('q'):
        {
            return false;
        }
        default:
        {
            break;
        }
    }
    return true;
}