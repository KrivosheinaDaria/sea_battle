#include "File.h"
#include "Game_State.h"

void Game_State::save(){
    File file(this->filename, std::ios::out);
    file << *this;
}

void Game_State::load(){
    File file(this->filename, std::ios::in);
    file >> *this;
}