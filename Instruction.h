#pragma once

#include <variant>

enum class InstructionOpcode {
    MOV,
    ADD,
    SUB,
    NOP,
    MUL,
    DIV,
    AND,
    OR,
    XOR,
    NOT,
    PUSH,
    POP,
    JMP,
    CMP,
    JE,
    JNE,
    JZ,
    JNZ,
    INC,
    DEC,
    INVALID
};

enum class RegisterOpcode {
    EAX, AX, AH, AL,
    EBX, BX, BH, BL,
    ECX, CX, CH, CL,
    EDX, DX, DH, DL,
    ESI, SI,
    EDI, DI,
    ESP, SP,
    EBP, BP,
    INVALID_REG
};

using InstructionArg = std::variant<int, double, RegisterOpcode>;

struct Instruction {
	InstructionOpcode opcode;
	std::vector<InstructionArg> operands;
};
