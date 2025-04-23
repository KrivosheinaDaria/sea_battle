#pragma once
#include "Ship.h"

class Ship_Manager{
public:
    Ship_Manager(size_t quantity, int lens[]);

    ~Ship_Manager();

    Ship* get_ship(size_t num);

    void delete_ship(size_t num);

    int get_length();

    int count_ships();
private:
    std::vector <Ship*> manager;
    size_t quantity;
};