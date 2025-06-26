#include "REPL.h"
#include <iostream>

REPL::REPL() {
    m_interrupt_manager.register_handler(*this);

    m_dispatch[InterruptType::ReadCharWithEcho] = [this](const Registers& reg){ intr_read_char_with_echo(reg); };
    m_dispatch[InterruptType::WriteChar] = [this](const Registers& reg){ intr_write_char(reg); };
}

REPL::~REPL() {
    m_interrupt_manager.unregister_handler(*this);
}

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
        } else if (ParseUtils::is_char(token)) {
            instr.operands.push_back((int)ParseUtils::string_to_char(token));
        } else {
            throw std::invalid_argument("Unknown type of operand: " + token);
        }
    }

	return instr;
};

void REPL::run() {
    m_vm.set_interrupt_manager(&m_interrupt_manager);
    std::string line;
    int line_number = 0;

    while (!m_is_halted) {
        std::cerr << line_number << ": ";
        if (!std::getline(std::cin, line)) break;
        
        if (line.empty()) continue;

        auto instr = fetch_decode(line);
        m_vm.execute(instr);
        ++line_number;
    }
}

void REPL::handle_interrupt(const Interrupt& intr) {
    auto it = m_dispatch.find(intr.type);
    if (it == m_dispatch.end()) {
        throw std::invalid_argument("Unknown interruption type!");
    }

    it->second(intr.registers);
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

void REPL::intr_read_char_with_echo(const Registers&) {
    std::cout << ">> ";

    char ch;
    std::cin.get(ch);       
    std::cin.get();

    m_vm.on_read_char_with_echo(ch);
}

void REPL::intr_write_char(const Registers& reg) {
    char ch = reg.get(RegisterOpcode::DL);

    std::cout << ch << std::endl;
}