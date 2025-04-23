#include "Bombing.h"

Abilities_Status Bombing::use_ability(Game_Field* field, int x, int y) {
    std::vector<std::pair<size_t, size_t>> ships_coords;
    for (size_t y1 = 0; y1 < field->get_width(); y1++) {
        for (size_t x1 = 0; x1 < field->get_length(); x1++) {
            if (field->get_field()[y1][x1].ship != nullptr &&
                field->get_field()[y1][x1].seg_condition != SegCondition::damaged) {
                std::pair<size_t, size_t> cur_coord = {x1, y1};
                ships_coords.push_back(cur_coord);
            }
        }
    }
    if (ships_coords.empty()) {
        throw Attack_Error("Error: all ships are damaged.\n");
    }
    size_t id = rand() % ships_coords.size();
    int indicator = field->attack(ships_coords[id].first, ships_coords[id].second, 1);
    if (indicator == 1) {
        return Abilities_Status::damaged;
    }
    return Abilities_Status::minor_changes;
}