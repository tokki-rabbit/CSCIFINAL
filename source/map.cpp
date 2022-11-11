#include "../headers/map.h"
#include <random>

 
Map::Map(int p_npc_count = 5, int p_room_count = 5)
:npc_count_{p_npc_count}, room_count_{p_npc_count}
{}

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
    if 
}

void Map::randomizeMap(std::mt19937& mt)
{
    std::uniform_int_distribution<> distrib(0, 11);
    for (int i{}; i < npc_count_; i)
    {
        int randCol{distrib(mt)}, randRow{distrib(mt)};
        if (map_data_[randRow][randCol] )
    }
}