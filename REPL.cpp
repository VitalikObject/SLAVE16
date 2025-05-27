#include "REPL.h"

Instruction REPL::fetch_decode(const std::string& line) {
	std::istringstream iss(line);
	std::string op;
	iss >> op;
	
	Instruction instr;
	instr.opcode = str_to_opcode(op);

	std::string token;
	while (iss >> token) {
		if (token.back() == ',')
			token.pop_back();

        RegisterOpcode reg_op = str_to_register_opcode(token);
		if (reg_op != RegisterOpcode::INVALID_REG) {
            instr.operands.push_back(reg_op);
        } else if (ParseUtils::is_int(token)) {
            instr.operands.push_back(ParseUtils::string_to_int(token));
        } else if (ParseUtils::is_double(token)) {
            instr.operands.push_back(ParseUtils::string_to_double(token));
        } else {
            throw std::invalid_argument("Unknown type of operand: " + token);
        }
	}

	return instr;
};

void REPL::run() {
	std::string line;
	while (!m_is_halted && getline(std::cin, line)) {
		if(line.empty()) continue;
		auto instr = fetch_decode(line);
		m_vm.execute(instr);
	}
}

InstructionOpcode REPL::str_to_opcode(const std::string& instr) {
    auto up = ParseUtils::to_upper(instr);
    auto it = ParseUtils::instr_map.find(up);
    return it != ParseUtils::instr_map.end() ? it->second : InstructionOpcode::INVALID;
}

RegisterOpcode REPL::str_to_register_opcode(const std::string& reg) {
    auto up = ParseUtils::to_upper(reg);
    auto it = ParseUtils::reg_map.find(up);
    return it != ParseUtils::reg_map.end() ? it->second : RegisterOpcode::INVALID_REG;
}