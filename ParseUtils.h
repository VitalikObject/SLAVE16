#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "Instruction.h"

class ParseUtils {
public:
    static const std::unordered_map<std::string, InstructionOpcode> instr_map;
    static const std::unordered_map<std::string, RegisterOpcode>      reg_map;
    static const std::unordered_set<InstructionOpcode>           jump_opcodes;

    static bool is_int(const std::string& str);
    static bool is_double(const std::string& str);
    static bool is_char(const std::string& str);
    static int string_to_int(const std::string& str);
    static double string_to_double(const std::string& str);
    static char string_to_char(const std::string& str);
    static std::string to_upper(const std::string& str);
    static int32_t uint32_to_int32(uint32_t val);
};
