#pragma once
#include "Game_Field.h"
#include "File.h"
#include "Game_State.h"

class Game {
    Game_State game_objects;

    bool check_type(std::string &str, int flag);

    int int_converter(std::string &str, int flag, UserAnswer& decision);

    void create_user_objects();

    void create_enemy_objects();

    void rotate_the_field_180();

    void rotate_the_field_90();

    void rotate_the_field_270();

    void print_rules();

    UserAnswer user_move();

    std::pair <int, int> enemy_move();

    void clear();
public:
    Game();

    ~Game();

    void start_game();

    void start_new_game();

    void process();

};