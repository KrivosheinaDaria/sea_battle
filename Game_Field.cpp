#include "Game_Field.h"

Game_Field::Game_Field(size_t length, size_t width, int field_type){
    this->length = length;
    this->width = width;
    if (field_type == 0) {
        this->field_type = FieldType::user;
    } else {
        this->field_type = FieldType::enemy;
    }
    std::vector <std::vector <Cell>> game_field (width, std::vector <Cell> (length));
    for (size_t i = 0; i < width; i++){
        for (size_t j = 0; j < length; j++){
            if (field_type == 0) {
                game_field[i][j].cell_condition = CellCondition::empty;
            } else {
                game_field[i][j].cell_condition = CellCondition::unknown;
            }
            game_field[i][j].ship = nullptr;
            game_field[i][j].seg_condition = SegCondition::empty;
            game_field[i][j].seg_number = 0;
        }
    }
    this->field = game_field;
}

Game_Field::Game_Field(const Game_Field& game_field): length(game_field.length), width(game_field.width), field_type(game_field.field_type){
    this->field = std::vector <std::vector <Cell>> (this->width, std::vector <Cell> (this->length));
    for (size_t y = 0; y < game_field.width; y++){
        for (size_t x = 0; x < game_field.length; x++){
            field[y][x].seg_condition = game_field.field[y][x].seg_condition;
            field[y][x].ship = game_field.field[y][x].ship;
            field[y][x].cell_condition = game_field.field[y][x].cell_condition;
        }
    }
}

Game_Field& Game_Field::operator = (const Game_Field& game_field){
    Game_Field temp(game_field);
    std::swap(this->length, temp.length);
    std::swap(this->width, temp.width);
    std::swap(this->field_type, temp.field_type);
    std::swap(this->field, temp.field);
    return *this;
}

Game_Field::Game_Field(Game_Field&& game_field): length(0), width(0), field_type(FieldType::user){
        this->field = std::vector <std::vector <Cell>> (this->width, std::vector <Cell>(this->length));
        std::swap(this->length, game_field.length);
        std::swap(this->width, game_field.width);
        std::swap(this->field_type, game_field.field_type);
        std::swap(this->field, game_field.field);
}

Game_Field& Game_Field::operator = (Game_Field&& game_field){
    if (this != &game_field){
        std::swap(this->length, game_field.length);
        std::swap(this->width, game_field.width);
        std::swap(this->field_type, game_field.field_type);
        std::swap(this->field, game_field.field);
    }
    return *this;
}

void Game_Field::add_ship(Ship* ship, char ship_orientation, size_t x, size_t y){
    ship->set_orientation(ship_orientation);
    if (ship_orientation == 'h') {
        for (size_t i = x, num = 1; i < x + ship->get_len(); i++, num++) {
            this->field[y][i].seg_condition = ship->get_segment(num);
            this->field[y][i].ship = ship;
            this->field[y][i].seg_number = num;
            if (this->field_type == FieldType::user){
                if (this->field[y][i].seg_condition == SegCondition::empty){
                    this->field[y][i].cell_condition = CellCondition::empty;
                } else {
                    this->field[y][i].cell_condition = CellCondition::ship;
                }
            }
        }
    } else if (ship_orientation == 'v') {
        for (size_t i = y, num = 1; i < y + ship->get_len(); i++, num++) {
            this->field[i][x].seg_condition = ship->get_segment(num);
            this->field[i][x].ship = ship;
            this->field[i][x].seg_number = num;
            if (this->field_type == FieldType::user){
                if (this->field[i][x].seg_condition == SegCondition::empty){
                    this->field[i][x].cell_condition = CellCondition::empty;
                } else {
                    this->field[i][x].cell_condition = CellCondition::ship;
                }
            }
        }
    }
}

int Game_Field::attack(int x, int y, int attack_type){
    if (x >= this->length || y >= this->width){
        throw Attack_Error("Error: the coordinates are out of field.\n");
    }
    if (this->field[y][x].ship == nullptr) {
        if (this->field_type == FieldType::enemy) {
            this->field[y][x].cell_condition = CellCondition::empty;
        }
        return 0;
    } else {
        if (this->field[y][x].seg_condition == SegCondition::damaged) {
            return 0;
        }
        this->field[y][x].cell_condition = CellCondition::ship;
        if (this->field[y][x].seg_condition == SegCondition::full) {
            this->field[y][x].seg_condition = SegCondition::hit;
            if (attack_type == 2){
                this->field[y][x].seg_condition = SegCondition::damaged;
            }
        } else {
            this->field[y][x].seg_condition = SegCondition::damaged;
        }
        this->field[y][x].ship->attack(this->field[y][x].seg_number, attack_type);
        if (this->field[y][x].ship->check_damage()) {
            return 1;
        }
    }
    return 2;
}

void Game_Field::print_field(){
    for (size_t i = 0; i < this->length; i++){
        if (i == 0){
            std::cout << "\t";
        }
        std::cout << i << ".\t";
    }
    std::cout << "\n";
    for (size_t y = 0; y < this->width; y++){
        std::cout << y << ".\t";
        for (size_t x = 0; x < this->length; x++){
            if (this->field[y][x].cell_condition != CellCondition::unknown){
                if (this->field[y][x].seg_condition == SegCondition::empty){
                    std::cout << "0\t";
                } else if (this->field[y][x].seg_condition == SegCondition::hit){
                    std::cout << "1\t";
                } else if (this->field[y][x].seg_condition == SegCondition::full){
                    std::cout << "2\t";
                } else {
                    std::cout << "x\t";
                }
            } else {
                std::cout << "?\t";
            }
        }
        std::cout << "\n";
    }
}

bool Game_Field::check(int len, char orient, int x, int y){
    if (orient != 'h' && orient != 'v'){
        throw Ship_Error("Error: incorrect orientation (should be 'h' or 'v').\n");
    }
    if (x >= this->length || y >= this->width){
        throw Ship_Error("Error: the coordinates are out of game field.\n");
    }
    if (orient == 'h' && (x + len - 1 >= this->length)){
        throw Ship_Error("Error: the ship is going to be placed out of game field.\n");
    }
    if (orient == 'v' && (y + len - 1 >= this->width)){
        throw Ship_Error("Error: the ship is going to be placed out of game field.\n");
    }
    int len1, wid1;
    if (orient == 'h'){
        len1 = len + 2;
        wid1 = 3;
    } else {
        len1 = 3;
        wid1 = len + 2;
    }
    int flag = 0;
    for (int i = y - 1; i < y - 1 + wid1; i++){
        for (int j = x - 1; j < x - 1 + len1; j++){
            if (i >= 0 && i < this->width && j >= 0 && j < this->length){
                if (this->field[i][j].seg_condition != SegCondition::empty){
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
        throw Ship_Error("Error: the ship can't be placed at these coordinates (there is other ship nearby).\n");
    }
    return true;
}

size_t Game_Field::get_length(){
    return this->length;
}

size_t Game_Field::get_width(){
    return this->width;
}
std::vector <std::vector <Cell>>& Game_Field::get_field(){
    return this->field;
}

std::string Game_Field::get_condition(){
    std::string condition;
    for (size_t y = 0; y < this->width; y++){
        for (size_t x = 0; x < this->length; x++){
            if (field[y][x].cell_condition != CellCondition::unknown) {
                if (field[y][x].seg_condition == SegCondition::empty) {
                    condition += '0';
                } else if (field[y][x].seg_condition == SegCondition::full) {
                    condition += '2';
                } else if (field[y][x].seg_condition == SegCondition::hit) {
                    condition += '1';
                }
                if (field[y][x].seg_condition == SegCondition::damaged) {
                    condition += 'x';
                }
            } else {
                condition += '?';
            }
        }
    }
    return condition;
}


void Game_Field::set_condition(std::string& condition){
    size_t id = 0;
    for (size_t y = 0; y < this->width; y++){
        for (size_t x = 0; x < this->length; x++){
            if (condition[id] == '0'){
                if (this->field_type == FieldType::enemy){
                    this->field[y][x].cell_condition = CellCondition::empty;
                }
            } else if (condition[id] != '?'){
                if (this->field_type == FieldType::enemy){
                    this->field[y][x].cell_condition = CellCondition::ship;
                }
            } else if (condition[id] == '?') {
                if (this->field_type == FieldType::enemy){
                    this->field[y][x].cell_condition = CellCondition::unknown;
                }
            }
            id++;
        }
    }
}