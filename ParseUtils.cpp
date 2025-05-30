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
    { "SHR", InstructionOpcode::SHR }
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
