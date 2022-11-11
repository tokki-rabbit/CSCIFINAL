#pragma once

#include <iostream>
#include <string>
#include <random>

class Map{
private:
    const char UNEXPLORED {'-'}; // marker for unexplored spaces
    const char EXPLORED {' '};   // marker for explored spaces
    const char ROOM{'R'};       // marker for room locations
    const char NPC{'N'};        // marker for NPC locations
    const char PARTY{'X'};      // marker for party position
    const char EXIT{'E'};       // marker for dungeon exit

    static const int num_rows_{12}; // number of rows in map
    static const int num_cols_{12}; // number of columns in map
    static const int max_npcs_{12};  // max non-player characters
    static const int max_rooms_{12}; // max number of rooms

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    struct pos{
        unsigned short x{};
        unsigned short y{};
    };
    std::vector<pos> npc_positions_;
    std::vector<pos> room_positions_;
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map

public:
    Map(int p_npc_count, int p_room_count);

    void resetMap();

    //getters
    int getPlayerRow();
    int getPlayerCol();
    int getDungeonExitRow();
    int getDungeonExitCol();
    int getRoomCount();
    int getNPCCount();
    int getNumRows();
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isNPCLocation(int row, int col);
    bool isRoomLocation(int row, int col);
    bool isExplored(int row, int col);
    bool isFreeSpace(int row, int col);
    bool isDungeonExit(int row, int col);

    //setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col);

    //other
    void displayMap();
    bool move(char);
    bool addNPC(int row, int col);
    bool addRoom(int row, int col);
    bool removeNPC(int row, int col);
    bool removeRoom(int row, int col);
    void randomizeMap(std::mt19937& mt);
    void exploreSpace(int row, int col);
};