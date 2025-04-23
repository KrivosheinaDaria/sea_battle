#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

enum class Orientation{horizontal, vertical};
enum class SegCondition{empty, damaged, hit, full};
enum class CellCondition{unknown, empty, ship};
enum class FieldType{enemy, user};
enum class Abilities_Status{damaged, found_ship, minor_changes, empty};
enum class UserAnswer{save, play, load, end};

class Ship{
public:
    Ship(size_t len);

    void attack(size_t num_seg, int attack_type);

    void print_info();

    int get_len();

    Orientation get_orientation();

    void set_orientation(char orient);

    SegCondition get_segment(size_t num);

    bool check_damage();

    std::string get_condition();

    void set_condition(std::string& condition);
private:
    size_t len;
    Orientation orientation = Orientation::horizontal;
    SegCondition segments[4];
};
