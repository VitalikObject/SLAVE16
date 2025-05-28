#include "VM.h"
#include <iostream>

VM::VM() {
    m_dispatch[InstructionOpcode::MOV] = [this](const std::vector<InstructionArg>& operands){ exec_MOV(operands); };
    m_dispatch[InstructionOpcode::ADD] = [this](const std::vector<InstructionArg>& operands){ exec_ADD(operands); };
    m_dispatch[InstructionOpcode::SUB] = [this](const std::vector<InstructionArg>& operands){ exec_SUB(operands); };
    m_dispatch[InstructionOpcode::MUL] = [this](const std::vector<InstructionArg>& operands){ exec_MUL(operands); };
    m_dispatch[InstructionOpcode::DIV] = [this](const std::vector<InstructionArg>& operands){ exec_DIV(operands); };
    m_dispatch[InstructionOpcode::AND] = [this](const std::vector<InstructionArg>& operands){ exec_AND(operands); };
    m_dispatch[InstructionOpcode::OR] = [this](const std::vector<InstructionArg>& operands){ exec_OR(operands); };
    m_dispatch[InstructionOpcode::XOR] = [this](const std::vector<InstructionArg>& operands){ exec_XOR(operands); };
    m_dispatch[InstructionOpcode::NOT] = [this](const std::vector<InstructionArg>& operands){ exec_NOT(operands); };
    m_dispatch[InstructionOpcode::PUSH] = [this](const std::vector<InstructionArg>& operands){ exec_PUSH(operands); };
    m_dispatch[InstructionOpcode::POP] = [this](const std::vector<InstructionArg>& operands){ exec_POP(operands); };
    m_dispatch[InstructionOpcode::JMP] = [this](const std::vector<InstructionArg>& operands){ exec_JMP(operands); };
    m_dispatch[InstructionOpcode::CMP] = [this](const std::vector<InstructionArg>& operands){ exec_CMP(operands); };
    m_dispatch[InstructionOpcode::JE] = [this](const std::vector<InstructionArg>& operands){ exec_JE(operands); };
    m_dispatch[InstructionOpcode::JNE] = [this](const std::vector<InstructionArg>& operands){ exec_JNE(operands); };
    m_dispatch[InstructionOpcode::JZ] = [this](const std::vector<InstructionArg>& operands){ exec_JZ(operands); };
    m_dispatch[InstructionOpcode::JNZ] = [this](const std::vector<InstructionArg>& operands){ exec_JNZ(operands); };
    m_dispatch[InstructionOpcode::INC] = [this](const std::vector<InstructionArg>& operands){ exec_INC(operands); };
    m_dispatch[InstructionOpcode::DEC] = [this](const std::vector<InstructionArg>& operands){ exec_DEC(operands); };
    m_dispatch[InstructionOpcode::NOP] = [this](const std::vector<InstructionArg>&){ exec_NOP(); };
};  

void VM::execute(const Instruction& instr) {
    m_program.push_back(instr);

    process_instructions();
}

void VM::process_instructions() {
    while (m_pc < m_program.size()) {
        const Instruction& instr = m_program[m_pc];

        auto it = m_dispatch.find(instr.opcode);
        if (it == m_dispatch.end()) {
            throw std::invalid_argument("Unknown opcode!");
        }

        it->second(instr.operands);

        if (instr.opcode != InstructionOpcode::JMP && instr.opcode != InstructionOpcode::JE && 
            instr.opcode != InstructionOpcode::JNE && instr.opcode != InstructionOpcode::JZ &&
            instr.opcode != InstructionOpcode::JNZ) {
            step(1);
#if DEBUG           
            std::cout << Debugger::info_about_registers(m_registers) << std::endl;
#endif
        }
    }
}

void VM::step(int step) {
    m_pc += step;
}

template<typename F>
uint32_t VM::get_value(const InstructionArg& arg, F&& err) {
    return std::visit([&](auto&& v) -> uint32_t {
           using T = std::decay_t<decltype(v)>;
           if constexpr (std::is_same_v<T, RegisterOpcode>) return m_registers.get(v);
           else if constexpr (std::is_same_v<T, int>) return static_cast<uint32_t>(v);
           else { err("Unsupported operand type"); __builtin_unreachable(); }
    }, arg);
}

void VM::exec_MOV(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("MOV requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("MOV first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"MOV: "} + why); });

    m_registers.set(dst, src);
}

void VM::exec_ADD(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("ADD requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("ADD first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"ADD: "} + why); });

    m_registers.set(dst, (dst_value + src));
}

void VM::exec_SUB(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SUB requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SUB first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SUB: "} + why); });

    m_registers.set(dst, (dst_value - src));
}

void VM::exec_MUL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("MUL requires 1 operand");
        return;
    }

    RegisterOpcode dst = RegisterOpcode::EAX;
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"MUL: "} + why); });

    m_registers.set(dst, (dst_value * src));
}

void VM::exec_DIV(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("DIV requires 1 operand");
        return;
    }

    RegisterOpcode dst = RegisterOpcode::EAX;
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"DIV: "} + why); });

    m_registers.set(dst, (dst_value / src));
}

void VM::exec_AND(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("AND requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("AND first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"AND: "} + why); });

    m_registers.set(dst, (dst_value & src));
}

void VM::exec_OR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("OR requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("OR first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"OR: "} + why); });

    m_registers.set(dst, (dst_value | src));
}

void VM::exec_XOR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("XOR requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("XOR first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"XOR: "} + why); });

    m_registers.set(dst, (dst_value ^ src));
}

void VM::exec_NOT(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("NOT requires 1 operand");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("NOT first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, ~dst_value);
}

void VM::exec_PUSH(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("PUSH requires 1 operand");
        return;
    }

    uint32_t src = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"PUSH: "} + why); });

    m_program_stack.push(src);
}

void VM::exec_POP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("PUSH requires 1 operand");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("POP first operand must be a register");
        return;
    }    

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    m_registers.set(dst, m_program_stack.top());
    m_program_stack.pop();
}

void VM::exec_JMP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JMP requires 1 operand");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("JMP first operand must be a register");
        return;
    }    

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    m_pc = m_registers.get(dst);
}

void VM::exec_CMP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("CMP requires 2 operands");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("CMP first operand must be a register");
        return;
    }  
    
    RegisterOpcode a = std::get<RegisterOpcode>(operands[0]);
    auto a_value = m_registers.get(a);

    uint32_t b_value = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"CMP: "} + why); });   

    uint32_t result = a_value - b_value;

    set_ZF(result == 0);
    set_CF(a_value < b_value);
    set_SF((result & 0x80000000) != 0);
    bool sign_a = (a_value & 0x80000000) != 0;
    bool sign_b = (b_value & 0x80000000) != 0;
    bool sign_r = (result & 0x80000000) != 0;
    set_OF((sign_a != sign_b) && (sign_r != sign_a));
}

void VM::exec_JE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JE requires 1 operand");
        return;
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JE: "} + why); });

    if (get_ZF()) m_pc = dst;
}

void VM::exec_JNE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNE requires 1 operand");
        return;
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNE: "} + why); });   

    if (!get_ZF()) m_pc = dst;
}

void VM::exec_JZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JZ requires 1 operand");
        return;
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JZ: "} + why); }); 

    if (get_ZF()) m_pc = dst;
}

void VM::exec_JNZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNZ requires 1 operand");
        return;
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNZ: "} + why); });    

    if (!get_ZF()) m_pc = dst;
}

void VM::exec_INC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("INC requires 1 operand");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("INC first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, ++dst_value);
}

void VM::exec_DEC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("DEC requires 1 operand");
        return;
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("DEC first operand must be a register");
        return;
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, --dst_value);
}