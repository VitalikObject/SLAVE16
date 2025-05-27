#include "ParseUtils.h"

bool ParseUtils::is_int(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') start = 1;
    if (start == str.size()) return false;

    return std::all_of(str.begin() + start, str.end(), ::isdigit);
}

bool ParseUtils::is_double(const std::string& str) {
    if (str.empty()) return false;

    std::istringstream iss(str);
    double val;
    char c;
    if (!(iss >> val)) return false;
    return !(iss >> c); 
}

int ParseUtils::string_to_int(const std::string& str) {
    return std::stoi(str);
}

double ParseUtils::string_to_double(const std::string& str) {
    return std::stod(str);
}

std::string ParseUtils::to_upper(const std::string& str) {
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(),
                    [](unsigned char c){ return std::toupper(c); });
    return out;
}

const std::unordered_map<std::string, InstructionOpcode> ParseUtils::instr_map = {
    { "MOV", InstructionOpcode::MOV },
    { "ADD", InstructionOpcode::ADD },
    { "SUB", InstructionOpcode::SUB },
    { "MUL", InstructionOpcode::MUL },
    { "DIV", InstructionOpcode::DIV },
    { "XOR", InstructionOpcode::XOR },
    { "PUSH", InstructionOpcode::PUSH },
    { "POP", InstructionOpcode::POP }
};

const std::unordered_map<std::string, RegisterOpcode> ParseUtils::reg_map = {
    { "EAX", RegisterOpcode::EAX }, { "AX",  RegisterOpcode::AX },
    { "AH",  RegisterOpcode::AH  }, { "AL",  RegisterOpcode::AL },
    { "EBX", RegisterOpcode::EBX }, { "BX",  RegisterOpcode::BX },
    { "BH",  RegisterOpcode::BH  }, { "BL",  RegisterOpcode::BL },
    { "ECX", RegisterOpcode::ECX }, { "CX",  RegisterOpcode::CX },
    { "CH",  RegisterOpcode::CH  }, { "CL",  RegisterOpcode::CL },
    { "EDX", RegisterOpcode::EDX }, { "DX",  RegisterOpcode::DX },
    { "DH",  RegisterOpcode::DH  }, { "DL",  RegisterOpcode::DL },
    { "ESI", RegisterOpcode::ESI }, { "SI",  RegisterOpcode::SI },
    { "EDI", RegisterOpcode::EDI }, { "DI",  RegisterOpcode::DI },
    { "ESP", RegisterOpcode::ESP }, { "SP",  RegisterOpcode::SP },
    { "EBP", RegisterOpcode::EBP }, { "BP",  RegisterOpcode::BP }
};