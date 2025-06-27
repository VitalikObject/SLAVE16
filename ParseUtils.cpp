#include "ParseUtils.h"

#include <string>
#include <algorithm>
#include <cctype>

bool ParseUtils::is_int(const std::string& str) {
    if (str.empty()) 
        return false;

    size_t start = 0;

    if (str[0] == '-' || str[0] == '+') {
        start = 1;
        if (start == str.size()) 
            return false; 
    }

    size_t end = str.size();
    bool isHex = false;
    char suf = std::tolower(static_cast<unsigned char>(str.back()));

    if (suf == 'h' && end - start > 1) {
        isHex = true;
        --end;
    }
    else if (suf == 'd' && end - start > 1) {
        --end;
    }

    if (isHex) {
        return std::all_of(
            str.begin() + start,
            str.begin() + end,
            [](char c) {
                return std::isxdigit(static_cast<unsigned char>(c));
            }
        );
    } else {
        return std::all_of(
            str.begin() + start,
            str.begin() + end,
            [](char c) {
                return std::isdigit(static_cast<unsigned char>(c));
            }
        );
    }
}


bool ParseUtils::is_double(const std::string& str) {
    if (str.empty()) return false;

    std::istringstream iss(str);
    double val;
    char c;
    if (!(iss >> val)) return false;
    return !(iss >> c); 
}

bool ParseUtils::is_char(const std::string& str) {
    if (str.size() < 3 || str.front() != '\'' || str.back() != '\'')
        return false;
    
    std::string inner = str.substr(1, str.size() - 2);
    
    if (inner.size() == 1)
        return true;
    
    if (inner.size() == 2 && inner[0] == '\\')
        return true;

    return false;
}

int ParseUtils::string_to_int(const std::string& str) {
    if (str.empty())
        throw std::invalid_argument("Empty string");

    char suf = std::tolower(str.back());
    int base = 10;
    std::string num = str;

    if (suf == 'h') {
        base = 16;
        num = str.substr(0, str.size() - 1);
    }
    else if (suf == 'd') {
        base = 10;
        num = str.substr(0, str.size() - 1);
    }

    return std::stoi(num, nullptr, base);
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

char ParseUtils::string_to_char(const std::string& str) {
    if (!is_char(str)) {
        throw std::invalid_argument("Invalid character literal: " + str);
    }

    std::string inner = str.substr(1, str.size() - 2);

    if (inner.size() == 1) {
        return inner[0];
    }

    static const std::unordered_map<char, char> esc_map = {
        {'a', '\a'}, {'b', '\b'}, {'f', '\f'}, {'n', '\n'},
        {'r', '\r'}, {'t', '\t'}, {'v', '\v'},
        {'\'', '\''}, {'"', '"'}, {'?', '\?'}, {'\\', '\\'},
        {'0', '\0'}
    };

    char type = inner[1];
    auto it = esc_map.find(type);
    if (it != esc_map.end()) {
        return it->second;
    }

    if (type == 'x' && inner.size() > 2) {
        unsigned int code = std::stoul(inner.substr(2), nullptr, 16);
        return static_cast<char>(code);
    } else if (inner[1] >= '0' && inner[1] <= '7') {
        unsigned int code = std::stoul(inner.substr(1), nullptr, 8);
        return static_cast<char>(code);
    }

    if ((inner[1] == 'u' && inner.size() == 5) || (inner[1] == 'U' && inner.size() == 9)) {
        unsigned int code = std::stoul(inner.substr(2), nullptr, 16);
        return static_cast<char>(code);
    }

    throw std::invalid_argument("Unsupported escape sequence: '" + inner + "'");
}


int32_t ParseUtils::uint32_to_int32(uint32_t val) {
    return static_cast<int32_t>(val);
}

const std::unordered_map<std::string, InstructionOpcode> ParseUtils::instr_map = {
    { "MOV", InstructionOpcode::MOV },
    { "ADD", InstructionOpcode::ADD },
    { "SUB", InstructionOpcode::SUB },
    { "MUL", InstructionOpcode::MUL },
    { "DIV", InstructionOpcode::DIV },
    { "AND", InstructionOpcode::AND },
    { "OR", InstructionOpcode::OR },
    { "XOR", InstructionOpcode::XOR },
    { "NOT", InstructionOpcode::NOT },
    { "PUSH", InstructionOpcode::PUSH },
    { "POP", InstructionOpcode::POP },
    { "JMP", InstructionOpcode::JMP },
    { "CMP", InstructionOpcode::CMP },
    { "JE", InstructionOpcode::JE },
    { "JNE", InstructionOpcode::JNE },
    { "JZ", InstructionOpcode::JZ },
    { "JNZ", InstructionOpcode::JNZ },
    { "JA", InstructionOpcode::JA },
    { "JNBE", InstructionOpcode::JNBE },
    { "JAE", InstructionOpcode::JAE },
    { "JNB", InstructionOpcode::JNB },
    { "JB", InstructionOpcode::JB },
    { "JNAE", InstructionOpcode::JNAE },
    { "JBE", InstructionOpcode::JBE },
    { "JNA", InstructionOpcode::JNA },
    { "JG", InstructionOpcode::JG },
    { "JNLE", InstructionOpcode::JNLE },
    { "JGE", InstructionOpcode::JGE },
    { "JNL", InstructionOpcode::JNL },
    { "JL", InstructionOpcode::JL },
    { "JNGE", InstructionOpcode::JNGE },
    { "JC", InstructionOpcode::JC },
    { "JNC", InstructionOpcode::JNC },
    { "JO", InstructionOpcode::JO },
    { "JNO", InstructionOpcode::JNO },
    { "JS", InstructionOpcode::JS },
    { "JNS", InstructionOpcode::JNS },
    { "JP", InstructionOpcode::JP },
    { "JPE", InstructionOpcode::JPE },
    { "JNP", InstructionOpcode::JNP },
    { "JPO", InstructionOpcode::JPO },
    { "JLE", InstructionOpcode::JLE },
    { "JNG", InstructionOpcode::JNG },
    { "NOP", InstructionOpcode::NOP },
    { "INC", InstructionOpcode::INC },
    { "DEC", InstructionOpcode::DEC },
    { "SAL", InstructionOpcode::SAL },
    { "SAR", InstructionOpcode::SAR },
    { "SHL", InstructionOpcode::SHL },
    { "SHR", InstructionOpcode::SHR },
    { "INT", InstructionOpcode::INT}
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

const std::unordered_set<InstructionOpcode> ParseUtils::jump_opcodes = {
	InstructionOpcode::JMP,
	InstructionOpcode::JE,
	InstructionOpcode::JNE,
	InstructionOpcode::JZ,
	InstructionOpcode::JNZ,
	InstructionOpcode::JA,
	InstructionOpcode::JNBE,
	InstructionOpcode::JAE,
	InstructionOpcode::JNB,
	InstructionOpcode::JB,
	InstructionOpcode::JNAE,
	InstructionOpcode::JBE,
	InstructionOpcode::JNA,
	InstructionOpcode::JG,
	InstructionOpcode::JNLE,
	InstructionOpcode::JGE,
	InstructionOpcode::JNL,
	InstructionOpcode::JL,
	InstructionOpcode::JNGE,
	InstructionOpcode::JLE,
	InstructionOpcode::JC,
	InstructionOpcode::JNC,
	InstructionOpcode::JO,
	InstructionOpcode::JNO,
	InstructionOpcode::JS,
	InstructionOpcode::JNS,
	InstructionOpcode::JP,
	InstructionOpcode::JPE,
	InstructionOpcode::JNP,
	InstructionOpcode::JPO
};
