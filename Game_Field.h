#pragma once
#include "Ship.h"
#include "Ship_Error.h"
#include "Attack_Error.h"

struct Cell{
    CellCondition cell_condition;
    Ship* ship;
    SegCondition seg_condition;
    int seg_number;
};

class Game_Field{
public:
    Game_Field(size_t length, size_t width, int field_type);

    Game_Field(const Game_Field& game_field);

    Game_Field& operator = (const Game_Field& game_field);

    Game_Field(Game_Field&& game_field);

    Game_Field& operator = (Game_Field&& game_field);

    void add_ship(Ship* ship, char ship_orientation, size_t x, size_t y);

    int attack(int x, int y, int attack_type);

    void print_field();

    bool check(int len, char orient, int x, int y);

    size_t get_length();

    size_t get_width();

    std::vector <std::vector <Cell>>& get_field();

    std::string get_condition();

    void set_condition(std::string& condition);
private:
    size_t length;
    size_t width;
    FieldType field_type;
    std::vector <std::vector <Cell>> field;
};