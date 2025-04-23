#pragma once
#include "Ship.h"
#include "Game_State.h"

class File{
    std::fstream file;
    friend class Game_State;
public:
    File(const std::string& filename, std::ios::openmode mode);

    ~File();

    File& operator<<(const Game_State& game_state);

    File& operator>>(Game_State& game_state);

    bool empty();
};