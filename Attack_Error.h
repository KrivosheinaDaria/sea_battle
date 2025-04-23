#pragma once
#include <iostream>

class Attack_Error : public std::exception {
public:
    Attack_Error(const std::string& message);
    const char* what() const noexcept;
private:
    std::string msg;
};