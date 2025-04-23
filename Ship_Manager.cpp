#include "Ship_Manager.h"

Ship_Manager::Ship_Manager(size_t quantity, int lens[]){
    this->quantity = quantity;
    for (size_t i = 0; i < quantity; i++){
        Ship* ship = new Ship(lens[i]);
        this->manager.push_back(ship);
    }
}
Ship_Manager::~Ship_Manager(){
    for (size_t i = 0; i < this->quantity; i++){
        delete this->manager[i];
    }
}
Ship* Ship_Manager::get_ship(size_t num){
    return this->manager[num];
}
void Ship_Manager::delete_ship(size_t num){
    delete this->manager[num];
    this->manager.erase(this->manager.begin() + num);
    quantity--;
}

int Ship_Manager::get_length(){
    return quantity;
}

int Ship_Manager::count_ships(){
    int counter = 0;
    for (size_t i = 0; i < quantity; i++){
        if (!this->manager[i]->check_damage()){
            counter++;
        }
    }
    return counter;
}