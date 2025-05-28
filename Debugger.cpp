#include "Debugger.h"

std::string Debugger::info_about_registers(const Registers& registers) {
    return "[DEBUG] EAX: " + std::to_string(registers.get_EAX()) + ", EBX: " + std::to_string(registers.get_EBX()) +
           ", ECX: " + std::to_string(registers.get_ECX()) + ", EDX: " + std::to_string(registers.get_EDX()) +
           ", ESI: " + std::to_string(registers.get_ESI()) + ", EDI: " + std::to_string(registers.get_EDI()) +
           ", ESP: " + std::to_string(registers.get_ESP()) + ", EBP: " + std::to_string(registers.get_EBP()); 
}

std::string Debugger::info_about_flags(const Registers& registers) {
    return "[DEBUG] CF: " + std::to_string(registers.get_flag(Flag::Carry)) + ", PF: " + std::to_string(registers.get_flag(Flag::Parity)) +
	   ", AF: " + std::to_string(registers.get_flag(Flag::Auxiliary)) + ", ZF: " + std::to_string(registers.get_flag(Flag::Zero)) +
	   ", SF: " + std::to_string(registers.get_flag(Flag::Sign)) + ", OF: " + std::to_string(registers.get_flag(Flag::Overflow));
}
