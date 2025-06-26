#pragma once

#include "VM.h"
#include "IInterruptHandler.h"
#include "InterruptManager.h"
#include "Interrupt.h"
#include <iostream>

class REPL : public IInterruptHandler {
private:
    VM m_vm;
    bool m_is_halted = false;    
    InterruptManager m_interrupt_manager;
    std::unordered_map<InterruptType, std::function<void(const Registers& reg)>> m_dispatch;

public:
    REPL();
    ~REPL();
    void run();
    void handle_interrupt(const Interrupt& intr);
    
private:
    Instruction fetch_decode(const std::string& line);
    InstructionOpcode str_to_opcode(const std::string& instr);
    RegisterOpcode str_to_register_opcode(const std::string& reg);

    void intr_read_char_with_echo(const Registers&);
    void intr_write_char(const Registers& reg);
};