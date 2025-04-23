#pragma once
#include "Double_Damage.h"
#include "Scanner.h"
#include "Bombing.h"

class Ability_Manager{
public:
    Ability_Manager();

    ~Ability_Manager();

    void use(Game_Field* field, int x=0, int y=0);

    void add_ability(int type=-1);

    std::string get_top_ability();

    bool empty();

    void delete_ability();

    int get_length();

    std::string get_condition();
private:
    std::queue<std::pair<Special_Abilities*, std::string>> abilities;
};