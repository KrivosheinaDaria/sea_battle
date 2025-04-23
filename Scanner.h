#pragma once
#include "Special_Abilities.h"

class Scanner : public Special_Abilities{
public:
    Abilities_Status use_ability(Game_Field* field, int x, int y) override;
};