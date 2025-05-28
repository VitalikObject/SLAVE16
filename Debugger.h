#pragma once

#include <string>
#include <stdexcept>
#include "Registers.h"

class Debugger {
public:
    static std::string info_about_registers(const Registers& registers);

    [[noreturn]] static void throw_arg_error(const std::string& msg) {
        throw std::invalid_argument{msg};
    }    
};
