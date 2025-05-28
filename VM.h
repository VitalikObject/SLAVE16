#pragma once

#include "ParseUtils.h"
#include "Registers.h"
#include "Debugger.h"
#include <stdexcept>
#include <stack>
#include <vector>
#include <bit>

class VM {
private:
    Registers m_registers;
    uint32_t m_pc {};
    uint32_t m_eflags {};
    std::unordered_map<InstructionOpcode, std::function<void(const std::vector<InstructionArg>& operands)>> m_dispatch;
    std::stack<uint32_t> m_program_stack;
    std::vector<Instruction> m_program;

    template<typename F>
    uint32_t get_value(const InstructionArg& arg, F&& err);    

public:
    VM();
    void execute(const Instruction& instr);
private:
    void step(int step = 1);
    void process_instructions();

    void exec_MOV(const std::vector<InstructionArg>& operands);
    void exec_ADD(const std::vector<InstructionArg>& operands);
    void exec_SUB(const std::vector<InstructionArg>& operands); 
    void exec_MUL(const std::vector<InstructionArg>& operands);
    void exec_DIV(const std::vector<InstructionArg>& operands);
    void exec_AND(const std::vector<InstructionArg>& operands);
    void exec_OR(const std::vector<InstructionArg>& operands);
    void exec_XOR(const std::vector<InstructionArg>& operands);
    void exec_NOT(const std::vector<InstructionArg>& operands);
    void exec_PUSH(const std::vector<InstructionArg>& operands);
    void exec_POP(const std::vector<InstructionArg>& operands);
    void exec_JMP(const std::vector<InstructionArg>& operands);
    void exec_CMP(const std::vector<InstructionArg>& operands);
    void exec_JE(const std::vector<InstructionArg>& operands);
    void exec_JNE(const std::vector<InstructionArg>& operands);
    void exec_JZ(const std::vector<InstructionArg>& operands);
    void exec_JNZ(const std::vector<InstructionArg>& operands);
    void exec_INC(const std::vector<InstructionArg>& operands);
    void exec_DEC(const std::vector<InstructionArg>& operands);
    void exec_SAL(const std::vector<InstructionArg>& operands);
    void exec_SAR(const std::vector<InstructionArg>& operands);
    void exec_SHL(const std::vector<InstructionArg>& operands);
    void exec_SHR(const std::vector<InstructionArg>& operands);
    void exec_NOP() {}
};
