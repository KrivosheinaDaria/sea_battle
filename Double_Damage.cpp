#include "Double_Damage.h"

Abilities_Status Double_Damage::use_ability(Game_Field* field, int x, int y){
    if (x >= field->get_length() || y >= field->get_width()){
        throw Attack_Error("Error: the coordinates are out of field.\n");
    }
    int indicator1 = field->attack(x, y, 2);
    if (indicator1 == 1) {
        return Abilities_Status::damaged;
    }
    return Abilities_Status::minor_changes;
}