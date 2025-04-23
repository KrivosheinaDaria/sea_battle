#include "Ship.h"

Ship::Ship(size_t len){
    this->len = len;
    for (size_t i = 0; i < len; i++){
        this->segments[i] = SegCondition::full;
    }
}

void Ship::attack(size_t num_seg, int attack_type) {
    if (this->segments[num_seg - 1] == SegCondition::full) {
        this->segments[num_seg - 1] = SegCondition::hit;
        if (attack_type == 2){
            this->segments[num_seg - 1] = SegCondition::damaged;
        }
    } else {
        this->segments[num_seg - 1] = SegCondition::damaged;
    }
}

void Ship::print_info(){
    std::cout << "The length is " << this->len << ".\n";
    std::cout << "The ship condition is ";
    for (size_t i = 0; i < this->len; i++){
        if (this->segments[i] == SegCondition::full){
            std::cout << 2 << "";
        } else if (this->segments[i] == SegCondition::hit){
            std::cout << 1 << "";
        } else if (this->segments[i] == SegCondition::damaged){
            std::cout << "x";
        }
    }
    std::cout << "\n";
}

int Ship::get_len(){
    return this->len;
}

Orientation Ship::get_orientation(){
    return this->orientation;
}

void Ship::set_orientation(char orient){
    if (orient == 'v') {
        this->orientation = Orientation::vertical;
    }
}

SegCondition Ship::get_segment(size_t num){
    return this->segments[num - 1];
}

bool Ship::check_damage(){
    for (size_t i = 0; i < this->len; i++){
        if (this->segments[i] != SegCondition::damaged){
            return false;
        }
    }
    return true;
}

std::string Ship::get_condition(){
    std::string condition;
    for (size_t i = 0; i < this->len; i++){
        if (this->segments[i] == SegCondition::full){
            condition += '2';
        } else if (this->segments[i] == SegCondition::hit){
            condition += '1';
        } else if (this->segments[i] == SegCondition::damaged){
            condition += 'x';
        }
    }
    return condition;
}

void Ship::set_condition(std::string& condition){
    for (size_t i = 0; i < len; i++){
        if (condition[i] == '2'){
            segments[i] = SegCondition::full;
        } else if (condition[i] == '1'){
            segments[i] = SegCondition::hit;
        } else if (condition[i] == 'x'){
            segments[i] = SegCondition::damaged;
        }
    }
}