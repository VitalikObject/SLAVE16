#pragma once

#include "ParseUtils.h"
#include "Registers.h"
#include <stdexcept>
#include <stack>
#include <vector>

class VM {
private:
	Registers m_registers;
    uint32_t m_pc {};
    std::unordered_map<InstructionOpcode, std::function<void(const std::vector<InstructionArg>& operands)>> m_dispatch;
    std::stack<uint32_t> m_program_stack;
public:
	VM();
    void execute(const Instruction& instr);
private:
    void step();

	void exec_MOV(const std::vector<InstructionArg>& operands);
	void exec_ADD(const std::vector<InstructionArg>& operands);
	void exec_SUB(const std::vector<InstructionArg>& operands); 
    void exec_MUL(const std::vector<InstructionArg>& operands);
    void exec_DIV(const std::vector<InstructionArg>& operands);
    void exec_XOR(const std::vector<InstructionArg>& operands);
    void exec_PUSH(const std::vector<InstructionArg>& operands);
    void exec_POP(const std::vector<InstructionArg>& operands);
};