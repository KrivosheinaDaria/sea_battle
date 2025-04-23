#include "Ship_Error.h"

Ship_Error::Ship_Error(const std::string& message) : msg(message){}

const char* Ship_Error::what() const noexcept{
    return msg.c_str();
}