#pragma once

#include <string>
#include <sstream>
#include "Instruction.h"
#include "Registers.h"

class ParseUtils {
public:
    static const std::unordered_map<std::string, InstructionOpcode> instr_map;
    static const std::unordered_map<std::string, RegisterOpcode>    reg_map;

    static bool is_int(const std::string& str);
    static bool is_double(const std::string& str);
    static int string_to_int(const std::string& str);
    static double string_to_double(const std::string& str);
    static std::string to_upper(const std::string& str);
    static int32_t uint32_to_int32(uint32_t val);
    static std::string info_about_registers(const Registers& registers);
};