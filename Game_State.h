#pragma once
#include "Ship_Manager.h"
#include "Game_Field.h"
#include "Ability_Manager.h"
#include "File.h"

class Game_State{
    friend class File;
public:
    Ship_Manager* user_manager;
    Ship_Manager* enemy_manager;
    Game_Field* user_field;
    Game_Field* enemy_field;
    Ability_Manager* abilities;
    std::vector <std::pair <int, int>> coordinates_for_attack;
    std::vector <std::pair <char, std::pair<int, int>>> user_ships_coordinates;
    std::vector <std::pair <char, std::pair<int, int>>> enemy_ships_coordinates;
    std::string filename = "saving_game";

    void save();

    void load();
};