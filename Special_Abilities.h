#pragma once
#include "Game_Field.h"
#include "Attack_Error.h"

class Special_Abilities{
public:
    virtual Abilities_Status use_ability(Game_Field* field, int x=0, int y=0) = 0;
    virtual ~Special_Abilities() = default;
};
