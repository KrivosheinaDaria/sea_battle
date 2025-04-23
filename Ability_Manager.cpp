#include "Ability_Manager.h"

Ability_Manager::Ability_Manager(){
    std::vector <int> order = {0, 1, 2};
    std::srand(time(nullptr));
    int id = rand() % order.size();
    this->add_ability(order[id]);
    order.erase(order.begin() + id);
    std::srand(time(nullptr));
    id = rand() % order.size();
    this->add_ability(order[id]);
    order.erase(order.begin() + id);
    this->add_ability(order[0]);
}

Ability_Manager::~Ability_Manager(){
    while (!this->empty()) {
        delete this->abilities.front().first;
        abilities.pop();
    }
}

void Ability_Manager::use(Game_Field* field, int x, int y){
    Abilities_Status output = this->abilities.front().first->use_ability(field, x, y);
    if (output == Abilities_Status::found_ship){
        std::cout << "There is a ship!\n";
    } else if (output == Abilities_Status::empty){
        std::cout << "There aren't any ships.\n";
    } else if (output == Abilities_Status::damaged){
        this->delete_ability();
        this->add_ability();
        return;
    }
    this->delete_ability();
}

void Ability_Manager::add_ability(int type){
    size_t ab = type;
    if (type == -1) {
        std::srand(time(nullptr));
        ab = rand() % 3;
    }
    if (ab == 0) {
        Double_Damage* new_ab = new Double_Damage;
        std::string name = "double_damage";
        abilities.emplace(new_ab, name);
    } else if (ab == 1) {
        Scanner* new_ab = new Scanner;
        std::string name = "scanner";
        abilities.emplace(new_ab, name);
    } else if (ab == 2) {
        Bombing* new_ab = new Bombing;
        std::string name = "bombing";
        abilities.emplace(new_ab, name);
    }
}

std::string Ability_Manager::get_top_ability(){
    return this->abilities.front().second;
}

bool Ability_Manager::empty(){
    if (abilities.empty()){
        return true;
    }
    return false;
}

void Ability_Manager::delete_ability(){
    if (!this->empty()){
        delete this->abilities.front().first;
        this->abilities.pop();
    }
}

int Ability_Manager::get_length(){
    return this->abilities.size();
}

std::string Ability_Manager::get_condition(){
    std::string condition;
    while (!this->empty()){
        if (this->get_top_ability() == "double_damage"){
            condition += "0 ";
        } else if (this->get_top_ability() == "scanner") {
            condition += "1 ";
        } else if (this->get_top_ability() == "bombing") {
            condition += "2 ";
        }
        this->delete_ability();
    }
    return condition;
}