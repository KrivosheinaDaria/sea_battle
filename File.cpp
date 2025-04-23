#include "File.h"
#include "Game_State.h"

File::File(const std::string& filename, std::ios::openmode mode) {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the file.\n");
    }
}

File::~File(){
    if (file.is_open()) {
        file.close();
    }
}

File& File::operator<<(const Game_State& game_state){
    file << "not empty\n";
    file << game_state.user_field->get_length() << " " << game_state.user_field->get_width() << "\n";
    file << game_state.user_manager->get_length() << "\n";
    for (size_t i = 0; i < game_state.user_manager->get_length(); i++){
        file << game_state.user_manager->get_ship(i)->get_len() << " ";
    }
    file << "\n";
    for (size_t i = 0; i < game_state.user_manager->get_length(); i++){
        file << game_state.user_manager->get_ship(i)->get_condition() << "\n";
    }
    for (size_t i = 0; i < game_state.user_manager->get_length(); i++){
        file << game_state.enemy_manager->get_ship(i)->get_condition() << "\n";
    }
    for (size_t i = 0; i < game_state.user_ships_coordinates.size(); i++){
        file << game_state.user_ships_coordinates[i].first << " ";
        file << game_state.user_ships_coordinates[i].second.first << " ";
        file << game_state.user_ships_coordinates[i].second.second << "\n";
    }
    for (size_t i = 0; i < game_state.enemy_ships_coordinates.size(); i++){
        file << game_state.enemy_ships_coordinates[i].first << " ";
        file << game_state.enemy_ships_coordinates[i].second.first << " ";
        file << game_state.enemy_ships_coordinates[i].second.second << "\n";
    }
    file << game_state.enemy_field->get_condition() << "\n";
    for (size_t i = 0; i < game_state.coordinates_for_attack.size(); i++){
        file << game_state.coordinates_for_attack[i].first << " " << game_state.coordinates_for_attack[i].second << " ";
    }
    file << "\n";
    file << game_state.abilities->get_length() << "\n";
    file << game_state.abilities->get_condition() << "\n";
    return *this;
}

File& File::operator>>(Game_State& game_state){
    std::string file_condition;
    std::getline(file, file_condition);
    int length, width;
    file >> length >> width;
    game_state.user_field = new Game_Field(length, width, 0);
    game_state.enemy_field = new Game_Field(length, width, 1);
    int ship_quantity;
    file >> ship_quantity;
    int lens[ship_quantity];
    for (size_t i = 0; i < ship_quantity; i++){
        file >> lens[i];
    }
    game_state.user_manager = new Ship_Manager(ship_quantity, lens);
    game_state.enemy_manager = new Ship_Manager(ship_quantity, lens);
    std::string str;
    std::getline(file, str);
    for (size_t i = 0; i < ship_quantity; i++){
        std::getline(file, str);
        game_state.user_manager->get_ship(i)->set_condition(str);
    }
    for (size_t i = 0; i < ship_quantity; i++){
        std::getline(file, str);
        game_state.enemy_manager->get_ship(i)->set_condition(str);
    }
    for (size_t i = 0; i < ship_quantity; i++){
        std::getline(file, str);
        char orient = str[0];
        std::vector <int> coords;
        size_t begin = 2;
        for (size_t j = 2; j < str.size(); j++){
            if (str[j] == ' '){
                coords.push_back(std::stoi(str.substr(begin, j - begin)));
                begin = j + 1;
                continue;
            }
            if (j == str.size() - 1){
                coords.push_back(std::stoi(str.substr(begin, str.size() - begin)));
            }
        }
        game_state.user_field->add_ship(game_state.user_manager->get_ship(i), orient, coords[0], coords[1]);
        game_state.user_ships_coordinates.push_back({orient, {coords[0], coords[1]}});
    }
    for (size_t i = 0; i < ship_quantity; i++){
        std::getline(file, str);
        char orient = str[0];
        std::vector <int> coords;
        size_t begin = 2;
        for (size_t j = 2; j < str.size(); j++){
            if (str[j] == ' '){
                coords.push_back(std::stoi(str.substr(begin, j - begin)));
                begin = j + 1;
                continue;
            }
            if (j == str.size() - 1){
                coords.push_back(std::stoi(str.substr(begin, str.size() - begin)));
            }
        }
        game_state.enemy_field->add_ship(game_state.enemy_manager->get_ship(i), orient, coords[0], coords[1]);
        game_state.enemy_ships_coordinates.push_back({orient, {coords[0], coords[1]}});
    }
    std::getline(file, str);
    game_state.enemy_field->set_condition(str);
    std::getline(file, str);
    int first = 0, counter = 0, found;
    for (size_t i = 0; i < str.size(); i++){
        if (str[i] == ' '){
            if (counter % 2 == 0) {
                found = std::stoi(str.substr(first, i - first));
                counter++;
                first = i + 1;
                continue;
            }
            game_state.coordinates_for_attack.push_back({found, std::stoi(str.substr(first, i - first))});
            first = i + 1;
            counter++;
            continue;
        }
        if (i == str.size() - 1 && str[i] != ' '){
            game_state.coordinates_for_attack.push_back({found, std::stoi(str.substr(first, str.size() - first))});
            break;
        }
    }
    int quantity_of_abilities;
    file >> quantity_of_abilities;
    int ab;
    game_state.abilities = new Ability_Manager();
    while (!game_state.abilities->empty()){
        game_state.abilities->delete_ability();
    }
    for (size_t i = 0; i < quantity_of_abilities; i++){
        file >> ab;
        game_state.abilities->add_ability(ab);
    }
    return *this;
}

bool File::empty(){
    std::string check;
    std::getline(file, check);
    if (check == "empty"){
        return true;
    }
    return false;
}