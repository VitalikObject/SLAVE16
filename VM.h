#pragma once

#include "InterruptManager.h"
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
    std::unordered_map<InstructionOpcode, std::function<void(const std::vector<InstructionArg>& operands)>> m_dispatch;
    std::stack<uint32_t> m_program_stack;
    std::vector<Instruction> m_program;
    InterruptManager* m_interrupt_manager;

    template<typename F>
    uint32_t get_value(const InstructionArg& arg, F&& err);    

public:
    VM();
    void execute(const Instruction& instr);
    void set_interrupt_manager(InterruptManager* intr);

    // --- Interruptions ---
    void on_read_char(char c);
    void on_get_system_date(int year, int month, int day, int day_of_week);
        
private:
    void step(int step = 1);
    void process_instructions();

    // --- Instructions ---
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
    void exec_JA(const std::vector<InstructionArg>& operands);
    void exec_JNBE(const std::vector<InstructionArg>& operands);
    void exec_JAE(const std::vector<InstructionArg>& operands);
    void exec_JNB(const std::vector<InstructionArg>& operands);
    void exec_JB(const std::vector<InstructionArg>& operands);
    void exec_JNAE(const std::vector<InstructionArg>& operands);
    void exec_JBE(const std::vector<InstructionArg>& operands);
    void exec_JNA(const std::vector<InstructionArg>& operands);
    void exec_JG(const std::vector<InstructionArg>& operands);
    void exec_JNLE(const std::vector<InstructionArg>& operands);
    void exec_JGE(const std::vector<InstructionArg>& operands);
    void exec_JNL(const std::vector<InstructionArg>& operands);
    void exec_JL(const std::vector<InstructionArg>& operands);
    void exec_JNGE(const std::vector<InstructionArg>& operands);
    void exec_JLE(const std::vector<InstructionArg>& operands);
    void exec_JNG(const std::vector<InstructionArg>& operands);
    void exec_JC(const std::vector<InstructionArg>& operands);
    void exec_JNC(const std::vector<InstructionArg>& operands);
    void exec_JO(const std::vector<InstructionArg>& operands);
    void exec_JNO(const std::vector<InstructionArg>& operands);
    void exec_JS(const std::vector<InstructionArg>& operands);
    void exec_JNS(const std::vector<InstructionArg>& operands);
    void exec_JP(const std::vector<InstructionArg>& operands);
    void exec_JPE(const std::vector<InstructionArg>& operands);
    void exec_JNP(const std::vector<InstructionArg>& operands);
    void exec_JPO(const std::vector<InstructionArg>& operands);
    void exec_INC(const std::vector<InstructionArg>& operands);
    void exec_DEC(const std::vector<InstructionArg>& operands);
    void exec_SAL(const std::vector<InstructionArg>& operands);
    void exec_SAR(const std::vector<InstructionArg>& operands);
    void exec_SHL(const std::vector<InstructionArg>& operands);
    void exec_SHR(const std::vector<InstructionArg>& operands);
    void exec_INT(const std::vector<InstructionArg>& operands);
    void exec_NOP() {}
};
