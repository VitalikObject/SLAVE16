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
    JA,
    JNBE,
    JAE,
    JNB,
    JB,
    JNAE,
    JBE,
    JNA,
    JG,
    JNLE,
    JGE,
    JNL,
    JL,
    JNGE,
    JLE,
    JNG,
    JC,
    JNC,
    JO,
    JNO,
    JS,
    JNS,
    JP,
    JPE,
    JNP,
    JPO,
    INC,
    DEC,
    SAL,
    SAR,
    SHL,
    SHR,
    INT,
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

enum class Flag : uint8_t {
    Carry     = 0,
    Parity    = 2,
    Auxiliary = 4,
    Zero      = 6,
    Sign      = 7,
    Overflow = 11
};

using InstructionArg = std::variant<int, double, RegisterOpcode>;

struct Instruction {
	InstructionOpcode opcode;
	std::vector<InstructionArg> operands;
};
