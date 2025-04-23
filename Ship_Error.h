#pragma once
#include <iostream>

class Ship_Error : public std::exception {
public:
    Ship_Error(const std::string& message);
    const char* what() const noexcept;
private:
    std::string msg;
};