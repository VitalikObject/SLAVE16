#include "Debugger.h"

std::string Debugger::info_about_registers(const Registers& registers) {
    return "EAX: " + std::to_string(registers.get_EAX()) + ", EBX: " + std::to_string(registers.get_EBX()) +
           ", ECX: " + std::to_string(registers.get_ECX()) + ", EDX: " + std::to_string(registers.get_EDX()) +
           ", ESI: " + std::to_string(registers.get_ESI()) + ", EDI: " + std::to_string(registers.get_EDI()) +
           ", ESP: " + std::to_string(registers.get_ESP()) + ", EBP: " + std::to_string(registers.get_EBP()); 
}