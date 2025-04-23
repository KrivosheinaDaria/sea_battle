#pragma once
#include "Special_Abilities.h"

class Bombing : public Special_Abilities{
public:
    Abilities_Status use_ability(Game_Field* field, int x=0, int y=0) override;
};