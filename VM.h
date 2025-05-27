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
    uint32_t m_eflags {};
    std::unordered_map<InstructionOpcode, std::function<void(const std::vector<InstructionArg>& operands)>> m_dispatch;
    std::stack<uint32_t> m_program_stack;
    std::vector<Instruction> m_program;

    static constexpr uint32_t ZF_MASK = 1 << 6; 
    static constexpr uint32_t SF_MASK = 1 << 7; 
    static constexpr uint32_t CF_MASK = 1 << 0;  
    static constexpr uint32_t OF_MASK = 1 << 11; 

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
    void exec_XOR(const std::vector<InstructionArg>& operands);
    void exec_PUSH(const std::vector<InstructionArg>& operands);
    void exec_POP(const std::vector<InstructionArg>& operands);
    void exec_JMP(const std::vector<InstructionArg>& operands);
    void exec_CMP(const std::vector<InstructionArg>& operands);
    void exec_JE(const std::vector<InstructionArg>& operands);
    void exec_JNE(const std::vector<InstructionArg>& operands);
    void exec_JZ(const std::vector<InstructionArg>& operands);
    void exec_JNZ(const std::vector<InstructionArg>& operands);
    void exec_NOP() {}

    void set_ZF(bool value) { value ? m_eflags |= ZF_MASK : m_eflags &= ~ZF_MASK; }
    bool get_ZF() const { return m_eflags & ZF_MASK; }
    void set_SF(bool value) { value ? m_eflags |= SF_MASK : m_eflags &= ~SF_MASK; }
    bool get_SF() const { return m_eflags & SF_MASK; }
    void set_CF(bool value) { value ? m_eflags |= CF_MASK : m_eflags &= ~CF_MASK; }
    bool get_CF() const { return m_eflags & CF_MASK; }
    void set_OF(bool value) { value ? m_eflags |= OF_MASK : m_eflags &= ~OF_MASK; }
    bool get_OF() const { return m_eflags & OF_MASK; }
};