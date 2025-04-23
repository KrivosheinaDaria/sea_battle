#include "Attack_Error.h"

Attack_Error::Attack_Error(const std::string& message) : msg(message){}

const char* Attack_Error::what() const noexcept{
    return msg.c_str();
}