#include "Scanner.h"

Abilities_Status Scanner::use_ability(Game_Field* field, int x, int y){
    if (x >= field->get_length() || y >= field->get_width()){
        throw Attack_Error("Error: the coordinates are out of field.\n");
    }
    int flag = 0;
    for (size_t i = y; i < y + 2; i++){
        for (size_t j = x; j < x + 2; j++){
            if (j < field->get_length() && i < field->get_width() && field->get_field()[i][j].seg_condition != SegCondition::damaged){
                if (field->get_field()[i][j].ship != nullptr){
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1){
            break;
        }
    }
    if (flag == 1){
        return Abilities_Status::found_ship;
    }
    return Abilities_Status::empty;
}