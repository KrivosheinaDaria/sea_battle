#include "Game.h"

bool Game::check_type(std::string &str, int flag){
    if (str.size() >= 10){
        return false;
    }
    try {
        std::stoi(str);
        if (str.size() != std::to_string(std::stoi(str)).size()){
            return false;
        }
        if (flag == 1 && std::stoi(str) <= 0){
            return false;
        }
        if (flag == 0 && std::stoi(str) < 0){
            return false;
        }
    } catch (std::invalid_argument &inv){
        return false;
    }
    return true;
}

int Game::int_converter(std::string &str, int flag, UserAnswer& decision){
    if (str == "load"){
        decision = UserAnswer::load;
        return -1;
    }
    if (str == "save"){
        decision = UserAnswer::save;
        return -1;
    }
    if (str == "end"){
        decision = UserAnswer::end;
        return -1;
    }
    int converted_value;
    if (!check_type(str, flag)){
        bool value = false;
        if (flag == 0) {
            std::cout << "Invalid value: the value should be zero or not very large natural number. Try again:\n";
        } else {
            std::cout << "Invalid value: the value should be not very large natural number. Try again:\n";
        }
        while (!value){
            std::getline(std::cin, str);
            if (str == "load"){
                decision = UserAnswer::load;
                return -1;
            }
            if (str == "save"){
                decision = UserAnswer::save;
                return -1;
            }
            if (str == "end"){
                decision = UserAnswer::end;
                return -1;
            }
            if (check_type(str, flag)){
                if (flag == 0 && std::stoi(str) >= 0 && std::stoi(str) <= 1000) {
                    value = true;
                } else if (flag == 1 && std::stoi(str) > 0 && std::stoi(str) <= 1000){
                    value = true;
                } else {
                    std::cout << "Still wrong. Try again:\n";
                }
            } else {
                std::cout << "Still wrong. Try again:\n";
            }
        }
    }
    converted_value = std::stoi(str);
    return converted_value;
}

void Game::create_user_objects(){
    std::cout << "Let's start our game!\nEnter the length and the width of the game field:\nlength: ";
    std::string length_str, width_str;
    std::getline(std::cin, length_str);
    UserAnswer decision = UserAnswer::play;
    int length = int_converter(length_str, 1, decision);
    std::cout << "width: ";
    std::getline(std::cin, width_str);
    int width = int_converter(width_str, 1, decision);
    game_objects.user_field = new Game_Field(length, width, 0);
    std::cout << "Now let's create the ships! How many ships do you want to create?\n";
    std::string quantity_str;
    int quantity;
    std::getline(std::cin, quantity_str);
    quantity = int_converter(quantity_str, 1, decision);
    int lens[quantity];
    for (size_t i = 0; i < quantity; i++) {
        std::string lens_str;
        std::cout << "Enter the length of ship number " << i << " (the length should be from 1 to 4):\n";
        std::getline(std::cin, lens_str);
        lens[i] = int_converter(lens_str, 1, decision);
        if (lens[i] < 1 || lens[i] > 4){
            bool value = false;
            std:: cout << "Invalid value: the ship length can be from 1 to 4. Try again:\n";
            while (!value){
                std::getline(std::cin, lens_str);
                lens[i] = int(int_converter(lens_str, 1, decision));
                if (lens[i] >= 1 && lens[i] <= 4){
                    value = true;
                } else {
                    std::cout << "Same problem. Try again:\n";
                }
            }
        }
    }
    game_objects.user_manager = new Ship_Manager(quantity, lens);
    std::cout << "The ships were created successfully!\nNow it's time to place these ships on the game field.\n";
    std::vector <size_t> del;
    for (size_t i = 0; i < quantity; i++){
        std::cout << "Enter the orientation of the ship number " << i << " (it can be 'h' for horizontal or 'v' for vertical):\n";
        std::string orient_str;
        std::getline(std::cin, orient_str);
        char orient;
        if (orient_str.size() == 1){
            orient = orient_str[0];
        } else {
            orient = ' ';
        }
        std::cout << "Enter the coordinates where the ship number " << i << " should be placed (the numeration begins from 0).\nx: ";
        std::string x_str, y_str;
        std::getline(std::cin, x_str);
        int x = int_converter(x_str, 0, decision);
        std::cout << "y: ";
        std::getline(std::cin, y_str);
        int y = int_converter(y_str, 0, decision);
        int attempts = 3;
        try {
            game_objects.user_field->check(game_objects.user_manager->get_ship(i)->get_len(), orient, x, y);
        } catch (const Ship_Error& er) {
            std::cerr << er.what();
            bool value = false;
            std::cout << "Try to enter the values again.\n";
            while (!value && attempts != 0) {
                std::cout << "The orientation of the ship:\n";
                std::getline(std::cin, orient_str);
                if (orient_str.size() == 1) {
                    orient = orient_str[0];
                } else {
                    orient = ' ';
                }
                std::cout << "Coordinates.\nx: ";
                std::getline(std::cin, x_str);
                x = int_converter(x_str, 0, decision);
                std::cout << "y: ";
                std::getline(std::cin, y_str);
                y = int_converter(y_str, 0, decision);
                try {
                    game_objects.user_field->check(game_objects.user_manager->get_ship(i)->get_len(), orient, x, y);
                    value = true;
                    continue;
                } catch (const Ship_Error &er) {
                    std::cerr << er.what();
                }
                attempts--;
                if (attempts != 0) {
                    std::cout << "Still wrong! You have " << attempts << " attempts now. Try again.\n";
                } else {
                    std::cout << "This ship will be deleted.\n";
                }
            }
        }
        if (attempts != 0) {
            game_objects.user_manager->get_ship(i)->set_orientation(orient);
            game_objects.user_field->add_ship(game_objects.user_manager->get_ship(i), orient, x, y);
            game_objects.user_ships_coordinates.push_back({orient, {x, y}});
        } else {
            del.push_back(i);
        }
    }
    int minus = 0;
    for (size_t j = 0; j < del.size(); j++){
        game_objects.user_manager->delete_ship(del[j] - minus);
        minus++;
    }
    std::cout << "The field was created successfully!\n";
}

void Game::create_enemy_objects(){
    game_objects.enemy_field = new Game_Field(game_objects.user_field->get_length(), game_objects.user_field->get_width(), 1);
    int lens[game_objects.user_manager->get_length()];
    for (size_t i = 0; i < game_objects.user_manager->get_length(); i++){
        lens[i] = game_objects.user_manager->get_ship(i)->get_len();
    }
    game_objects.enemy_manager = new Ship_Manager(game_objects.user_manager->get_length(), lens);
    int rotate_number = 1;
    if (game_objects.enemy_field->get_width() == game_objects.enemy_field->get_length()) {
        std::srand(time(nullptr));
        rotate_number = rand() % 3;
    }
    if (rotate_number == 0) {
        this->rotate_the_field_90();
    } else if (rotate_number == 1) {
        this->rotate_the_field_180();
    } else {
        this->rotate_the_field_270();
    }
}

void Game::rotate_the_field_180(){
    int x, y;
    char orient;
    for (size_t i = 0; i < game_objects.enemy_manager->get_length(); i++){
        orient = game_objects.user_ships_coordinates[i].first;
        if (orient == 'h'){
            x = game_objects.user_field->get_length() - 1 - (game_objects.user_ships_coordinates[i].second.first + game_objects.user_manager->get_ship(i)->get_len() - 1);
            y = game_objects.user_field->get_width() - game_objects.user_ships_coordinates[i].second.second - 1;
        } else {
            x = game_objects.user_field->get_length() - game_objects.user_ships_coordinates[i].second.first - 1;
            y = game_objects.user_field->get_width() - 1 - (game_objects.user_ships_coordinates[i].second.second + game_objects.user_manager->get_ship(i)->get_len() - 1);
        }
        game_objects.enemy_field->add_ship(game_objects.enemy_manager->get_ship(i), orient, x, y);
        game_objects.enemy_ships_coordinates.push_back({orient, {x, y}});
    }
}

void Game::rotate_the_field_90(){
    int x, y;
    char orient;
    for (size_t i = 0; i < game_objects.enemy_manager->get_length(); i++){
        if (game_objects.user_ships_coordinates[i].first == 'h'){
            orient = 'v';
            x = game_objects.user_field->get_width() - 1 - game_objects.user_ships_coordinates[i].second.second;
        } else {
            orient = 'h';
            x = game_objects.user_field->get_width() - game_objects.user_ships_coordinates[i].second.second - game_objects.user_manager->get_ship(i)->get_len();
        }
        y = game_objects.user_ships_coordinates[i].second.first;
        game_objects.enemy_field->add_ship(game_objects.enemy_manager->get_ship(i), orient, x, y);
        game_objects.enemy_ships_coordinates.push_back({orient, {x, y}});
    }
}

void Game::rotate_the_field_270(){
    int x, y;
    char orient;
    for (size_t i = 0; i < game_objects.enemy_manager->get_length(); i++){
        if (game_objects.user_ships_coordinates[i].first == 'h'){
            orient = 'v';
            y = game_objects.user_field->get_width() - game_objects.user_ships_coordinates[i].second.first - game_objects.user_manager->get_ship(i)->get_len();

        } else {
            orient = 'h';
            y = game_objects.user_field->get_width() - 1 - game_objects.user_ships_coordinates[i].second.first;
        }
        x = game_objects.user_ships_coordinates[i].second.second;
        game_objects.enemy_field->add_ship(game_objects.enemy_manager->get_ship(i), orient, x, y);
        game_objects.enemy_ships_coordinates.push_back({orient, {x, y}});
    }
}

void Game::print_rules(){
    for (size_t i = 0; i < 28; i++){
        std::cout << "-";
    }
    std::cout << "RULES";
    for (size_t i = 0; i < 28; i++){
        std::cout << "-";
    }
    std::cout << "\nBefore every attack you will have an opportunity to use some special ability.\n"
                 "Three abilities are available at the beginning in random order.\n"
                 "After every damaging of the ship one more will become available.\n"
                 "It can be double attack (hit the cell twice), scanner (check the square 2*2 for presence of the ship) and bombing (hit the random segment of random ship).\n"
                 "If you want to use double attack, it's necessary to enter the coordinates of the cell.\n"
                 "If you want to use scanner, it's necessary to enter the coordinates of the top left angle of the square.\n"
                 "If you want to use bombing, you don't need to enter anything.\n"
                 "If you want to use the ability, enter the word 'use'. Otherwise just press 'enter'.\n";
    for (size_t i = 0; i < 61; i++){
        std::cout << "-";
    }
    std::cout << "\n";
}

UserAnswer Game::user_move(){
    std::string x1_str, y1_str;
    int x1, y1, indicator;
    std::string ab;
    std::string answer;
    while (true) {
        if (!game_objects.abilities->empty()) {
            ab = game_objects.abilities->get_top_ability();
            std::cout << "Use " << ab << "? (enter 'use' or press 'enter')\n";
            std::getline(std::cin, answer);
            if (answer == "use") {
                if (ab == "bombing") {
                    try {
                        game_objects.abilities->use(game_objects.enemy_field);
                    } catch (const Attack_Error &er) {
                        std::cerr << er.what();
                        game_objects.abilities->delete_ability();
                    }
                    return UserAnswer::play;
                }
                break;
            } else if (answer == "load") {
                return UserAnswer::load;
            } else if (answer == "save") {
                return UserAnswer::save;
            } else if (answer == "end"){
                return UserAnswer::end;
            } else {
                if (answer != "") {
                    std::cout << "Unknown command. Try again.\n";
                    continue;
                }
                break;
            }
        } else {
            std::cout << "You don't have any special abilities.\n";
            break;
        }
    }
    std::cout << "Enter the coordinates (the numeration begins from 0).\nx: ";
    std::getline(std::cin, x1_str);
    UserAnswer decision = UserAnswer::play;
    x1 = int_converter(x1_str, 0, decision);
    if (decision != UserAnswer::play){
        return decision;
    }
    std::cout << "y: ";
    std::getline(std::cin, y1_str);
    y1 = int_converter(y1_str, 0, decision);
    if (decision != UserAnswer::play){
        return decision;
    }
    try {
        if (answer == "use") {
            game_objects.abilities->use(game_objects.enemy_field, x1, y1);
        } else {
            indicator = game_objects.enemy_field->attack(x1, y1, 1);
            if (indicator == 1) {
                game_objects.abilities->add_ability();
            }
        }
    } catch (const Attack_Error &er) {
        std::cerr << er.what();
        bool value = false;
        std::cout << "Try to attack again.\n";
        while (!value) {
            std::cout << "x: ";
            std::getline(std::cin, x1_str);
            x1 = int_converter(x1_str, 0, decision);
            if (decision != UserAnswer::play){
                return decision;
            }
            std::cout << "y: ";
            std::getline(std::cin, y1_str);
            y1 = int_converter(y1_str, 0, decision);
            if (decision != UserAnswer::play){
                return decision;
            }
            try {
                if (answer == "use") {
                    game_objects.abilities->use(game_objects.enemy_field, x1, y1);
                } else {
                    indicator = game_objects.enemy_field->attack(x1, y1, 1);
                    if (indicator == 1) {
                        game_objects.abilities->add_ability();
                    }
                }
                value = true;
                continue;
            } catch (const Ship_Error &er) {
                std::cerr << er.what();
            }
            std::cout << "Still wrong values. Try again.\n";
        }
    }
    return UserAnswer::play;
}

std::pair <int, int> Game::enemy_move(){
    std::srand(time(nullptr));
    int id = rand() % game_objects.coordinates_for_attack.size();
    std::pair <int, int> coordinate = {-1, -1};
    int attack = game_objects.user_field->attack(game_objects.coordinates_for_attack[id].first, game_objects.coordinates_for_attack[id].second, 1);
    if (attack == 2) {
        coordinate = {game_objects.coordinates_for_attack[id].first, game_objects.coordinates_for_attack[id].second};
    }
    game_objects.coordinates_for_attack.erase(game_objects.coordinates_for_attack.begin() + id);
    return coordinate;
}

void Game::clear(){
    delete game_objects.user_field;
    delete game_objects.enemy_field;
    delete game_objects.user_manager;
    delete game_objects.enemy_manager;
    delete game_objects.abilities;
    game_objects.enemy_ships_coordinates.clear();
    game_objects.user_ships_coordinates.clear();
}

Game::Game(){
    game_objects.abilities = new Ability_Manager();
}

Game::~Game(){
    this->clear();
}

void Game::start_game(){
    File file(game_objects.filename, std::ios::in);
    if (!file.empty()){
        std::cout << "Do you want to continue last game? ('yes' or 'no')\n";
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == "yes"){
            game_objects.load();
            std::cout << "\t\tENEMY FIELD\t\n";
            game_objects.enemy_field->print_field();
            std::cout << "\t\tYOUR FIELD\t\n";
            game_objects.user_field->print_field();
            this->process();
            return;
        } else if (answer == "no"){
            this->start_new_game();
            return;
        } else {
            while (true) {
                std::cout << "Unknown command. Try again.\n";
                std::getline(std::cin, answer);
                if (answer == "yes"){
                    game_objects.load();
                    std::cout << "\t\tENEMY FIELD\t\n";
                    game_objects.enemy_field->print_field();
                    std::cout << "\t\tYOUR FIELD\t\n";
                    game_objects.user_field->print_field();
                    this->process();
                    return;
                } else if (answer == "no"){
                    this->start_new_game();
                    return;
                }
            }
        }
    } else {
        this->start_new_game();
        return;
    }

}


void Game::start_new_game(){
    this->create_user_objects();
    this->create_enemy_objects();
    for (size_t x = 0; x < game_objects.user_field->get_length(); x++){
        for (size_t y = 0; y < game_objects.user_field->get_width(); y++){
            std::pair <int, int> current = {x, y};
            game_objects.coordinates_for_attack.push_back(current);
        }
    }
    std::cout << "\t\tENEMY FIELD\t\n";
    game_objects.enemy_field->print_field();
    std::cout << "\t\tYOUR FIELD\t\n";
    game_objects.user_field->print_field();
    this->process();

}

void Game::process() {
    std::cout << "Let's start!\n";
    this->print_rules();
    std::pair <int, int> coordinate = {-1, -1};
    while (game_objects.user_manager->count_ships()){
        UserAnswer answer = this->user_move();
        if (answer == UserAnswer::load){
            this->clear();
            game_objects.load();
            std::cout << "The game was successfully loaded.\n";
            std::cout << "\t\tENEMY FIELD\t\n";
            game_objects.enemy_field->print_field();
            std::cout << "\t\tYOUR FIELD\t\n";
            game_objects.user_field->print_field();
            std::cout << game_objects.enemy_field->get_width() << " " << game_objects.enemy_field->get_length() << "\n";
            continue;
        }
        if (answer == UserAnswer::save){
            if (coordinate.first != -1 || coordinate.second != -1){
                game_objects.coordinates_for_attack.push_back(coordinate);
            }
            game_objects.save();
            std::cout << "The game was successfully saved.\n";
        }
        if (answer == UserAnswer::end){
            std::cout << "Goodbye!\n";
            return;
        }
        if (!game_objects.enemy_manager->count_ships()){
            std::cout << "The enemy is defeated!\nBe ready for the new one.\n";
            delete game_objects.enemy_field;
            delete game_objects.enemy_manager;
            game_objects.enemy_ships_coordinates.clear();
            this->create_enemy_objects();
            std::cout << "\t\tENEMY FIELD\t\n";
            game_objects.enemy_field->print_field();
            continue;
        }
        if (coordinate.first == -1 && coordinate.second == -1){
            coordinate = this->enemy_move();
        } else {
            game_objects.user_field->attack(coordinate.first, coordinate.second, 1);
            coordinate = {-1, -1};
        }
        std::cout << "\t\tENEMY FIELD\t\n";
        game_objects.enemy_field->print_field();
        std::cout << "\t\tYOUR FIELD\t\n";
        game_objects.user_field->print_field();

    }
    std::cout << "You are defeated!\nGAME OVER\n";
    int value = false;
    std::ofstream file(game_objects.filename, std::ios::trunc);
    file << "empty";
    file.close();
    std::cout << "Do you want to start new game? ('yes' or 'no')\n";
    std::string answer;
    while (!value){
        std::getline(std::cin, answer);
        if (answer == "yes"){
            this->clear();
            this->start_new_game();
            value = true;
        } else if (answer == "no"){
            return;
        } else {
            std::cout << "Unknown command. Try again.\n";
        }
    }
}