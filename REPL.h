#pragma once

#include "VM.h"
#include <iostream>

class REPL {
private:
    VM m_vm;
    bool m_is_halted = false;    

public:
    REPL() = default;
    void run();
private:
    Instruction fetch_decode(const std::string& line);
    InstructionOpcode str_to_opcode(const std::string& instr);
    RegisterOpcode str_to_register_opcode(const std::string& reg);
};