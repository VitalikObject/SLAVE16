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
    m_dispatch[InstructionOpcode::JA] = [this](const std::vector<InstructionArg>& operands){ exec_JA(operands); };
    m_dispatch[InstructionOpcode::JNBE] = [this](const std::vector<InstructionArg>& operands){ exec_JNBE(operands); };
    m_dispatch[InstructionOpcode::JAE] = [this](const std::vector<InstructionArg>& operands){ exec_JAE(operands); };
    m_dispatch[InstructionOpcode::JNB] = [this](const std::vector<InstructionArg>& operands){ exec_JNB(operands); };
    m_dispatch[InstructionOpcode::JB] = [this](const std::vector<InstructionArg>& operands){ exec_JB(operands); };
    m_dispatch[InstructionOpcode::JNAE] = [this](const std::vector<InstructionArg>& operands){ exec_JNAE(operands); };
    m_dispatch[InstructionOpcode::JBE] = [this](const std::vector<InstructionArg>& operands){ exec_JBE(operands); };
    m_dispatch[InstructionOpcode::JNA] = [this](const std::vector<InstructionArg>& operands){ exec_JNA(operands); };
    m_dispatch[InstructionOpcode::JG] = [this](const std::vector<InstructionArg>& operands){ exec_JG(operands); };
    m_dispatch[InstructionOpcode::JNLE] = [this](const std::vector<InstructionArg>& operands){ exec_JNLE(operands); };
    m_dispatch[InstructionOpcode::JGE] = [this](const std::vector<InstructionArg>& operands){ exec_JGE(operands); };
    m_dispatch[InstructionOpcode::JNL] = [this](const std::vector<InstructionArg>& operands){ exec_JNL(operands); };
    m_dispatch[InstructionOpcode::JL] = [this](const std::vector<InstructionArg>& operands){ exec_JL(operands); };
    m_dispatch[InstructionOpcode::JNGE] = [this](const std::vector<InstructionArg>& operands){ exec_JNGE(operands); };
    m_dispatch[InstructionOpcode::JLE] = [this](const std::vector<InstructionArg>& operands){ exec_JLE(operands); };
    m_dispatch[InstructionOpcode::JC] = [this](const std::vector<InstructionArg>& operands){ exec_JC(operands); };
    m_dispatch[InstructionOpcode::JNC] = [this](const std::vector<InstructionArg>& operands){ exec_JNC(operands); };
    m_dispatch[InstructionOpcode::JO] = [this](const std::vector<InstructionArg>& operands){ exec_JO(operands); };
    m_dispatch[InstructionOpcode::JNO] = [this](const std::vector<InstructionArg>& operands){ exec_JNO(operands); };
    m_dispatch[InstructionOpcode::JS] = [this](const std::vector<InstructionArg>& operands){ exec_JS(operands); };
    m_dispatch[InstructionOpcode::JNS] = [this](const std::vector<InstructionArg>& operands){ exec_JNS(operands); };
    m_dispatch[InstructionOpcode::JP] = [this](const std::vector<InstructionArg>& operands){ exec_JP(operands); };
    m_dispatch[InstructionOpcode::JPE] = [this](const std::vector<InstructionArg>& operands){ exec_JPE(operands); };
    m_dispatch[InstructionOpcode::JNP] = [this](const std::vector<InstructionArg>& operands){ exec_JNP(operands); };
    m_dispatch[InstructionOpcode::JPO] = [this](const std::vector<InstructionArg>& operands){ exec_JPO(operands); };
    m_dispatch[InstructionOpcode::INC] = [this](const std::vector<InstructionArg>& operands){ exec_INC(operands); };
    m_dispatch[InstructionOpcode::DEC] = [this](const std::vector<InstructionArg>& operands){ exec_DEC(operands); };
    m_dispatch[InstructionOpcode::SAL] = [this](const std::vector<InstructionArg>& operands){ exec_SAL(operands); };
    m_dispatch[InstructionOpcode::SAR] = [this](const std::vector<InstructionArg>& operands){ exec_SAR(operands); };
    m_dispatch[InstructionOpcode::SHL] = [this](const std::vector<InstructionArg>& operands){ exec_SHL(operands); };
    m_dispatch[InstructionOpcode::SHR] = [this](const std::vector<InstructionArg>& operands){ exec_SHR(operands); };
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

        if (!ParseUtils::jump_opcodes.contains(instr.opcode)) {
            step(1);
#if DEBUG           
            std::cerr << Debugger::info_about_registers(m_registers) << std::endl;
	    std::cerr << Debugger::info_about_flags(m_registers) << std::endl;
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
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("MOV first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"MOV: "} + why); });

    m_registers.set(dst, src);
}

void VM::exec_ADD(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("ADD requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("ADD first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"ADD: "} + why); });

    uint32_t result64 = static_cast<uint64_t>(dst_value) + static_cast<uint64_t>(src);
    uint32_t result = static_cast<uint32_t>(result64);
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);
    m_registers.set_flag(Flag::Carry, result64 > 0xFFFFFFFF);

    bool src_sign = (src & 0x80000000) != 0;
    bool dst_sign = (dst_value & 0x80000000) != 0;
    bool res_sign = (result & 0x80000000) != 0;
    bool overflow = (dst_sign == src_sign) && (res_sign != dst_sign);
    m_registers.set_flag(Flag::Overflow, overflow);
} 

void VM::exec_SUB(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SUB requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SUB first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SUB: "} + why); });

    uint32_t result = dst_value - src;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);
    m_registers.set_flag(Flag::Carry, dst_value >= src);

    bool src_sign = (src & 0x80000000) != 0;
    bool dst_sign = (dst_value & 0x80000000) != 0;
    bool res_sign = (result & 0x80000000) != 0;
    bool overflow = (dst_sign != src_sign) && (res_sign != dst_sign);
    m_registers.set_flag(Flag::Overflow, overflow);
}

void VM::exec_MUL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("MUL requires 1 operand");
    }

    RegisterOpcode dst = RegisterOpcode::EAX;
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"MUL: "} + why); });

    uint64_t result64 = static_cast<uint64_t>(dst_value) * static_cast<uint64_t>(src);
    uint32_t result = static_cast<uint32_t>(result64);
    m_registers.set(dst, result);

    bool upper_nonzero = (result64 >> 32) != 0;
    m_registers.set_flag(Flag::Carry, upper_nonzero);
    m_registers.set_flag(Flag::Overflow, upper_nonzero);
}

void VM::exec_DIV(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("DIV requires 1 operand");
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
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("AND first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"AND: "} + why); });

    uint32_t result = dst_value & src;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);

    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count % 2) == 0);

    m_registers.set_flag(Flag::Carry, false);
    m_registers.set_flag(Flag::Overflow, false);
}

void VM::exec_OR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("OR requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("OR first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"OR: "} + why); });

    uint32_t result = dst_value | src;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);
    
    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count & 2) == 0);

    m_registers.set_flag(Flag::Carry, false);
    m_registers.set_flag(Flag::Overflow, false);
}

void VM::exec_XOR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("XOR requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("XOR first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    uint32_t src = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"XOR: "} + why); });

    uint32_t result = dst_value ^ src;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);
    
    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count & 2) == 0);

    m_registers.set_flag(Flag::Carry, false);
    m_registers.set_flag(Flag::Overflow, false);
}

void VM::exec_NOT(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("NOT requires 1 operand");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("NOT first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, ~dst_value);
}

void VM::exec_PUSH(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("PUSH requires 1 operand");
    }

    uint32_t src = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"PUSH: "} + why); });

    m_program_stack.push(src);
}

void VM::exec_POP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("PUSH requires 1 operand");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("POP first operand must be a register");
    }    

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    m_registers.set(dst, m_program_stack.top());
    m_program_stack.pop();
}

void VM::exec_JMP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JMP requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNG: "} + why); });  

    m_pc = dst;
}

void VM::exec_CMP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("CMP requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("CMP first operand must be a register");
    }  
    
    RegisterOpcode a = std::get<RegisterOpcode>(operands[0]);
    auto a_value = m_registers.get(a);

    uint32_t b_value = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"CMP: "} + why); });   

    uint32_t result = a_value - b_value;

    m_registers.set_flag(Flag::Zero, result == 0);
    m_registers.set_flag(Flag::Carry, a_value < b_value);
    m_registers.set_flag(Flag::Sign, (result & 0x80000000) != 0);
    bool sign_a = (a_value & 0x80000000) != 0;
    bool sign_b = (b_value & 0x80000000) != 0;
    bool sign_r = (result & 0x80000000) != 0;
    m_registers.set_flag(Flag::Overflow, (sign_a != sign_b) && (sign_r != sign_a));
}

void VM::exec_JE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JE: "} + why); });

    if (m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JNE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNE: "} + why); });   

    if (!m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JZ requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JZ: "} + why); }); 

    if (m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JNZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNZ requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNZ: "} + why); });    

    if (!m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JA(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JA requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JA: "} + why); });    

    if (!m_registers.get_flag(Flag::Carry) && !m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JNBE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNBE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNBE: "} + why); });    

    if (!m_registers.get_flag(Flag::Carry) && !m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JAE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JAE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JAE: "} + why); });    

    if (!m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JNB(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNB requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNB: "} + why); });    

    if (!m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JB(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JB requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JB: "} + why); });    

    if (m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JNAE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNAE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNAE: "} + why); });    

    if (m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JBE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JBE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JBE: "} + why); });    

    if (m_registers.get_flag(Flag::Carry) || m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JNA(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNA requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNA: "} + why); });    

    if (m_registers.get_flag(Flag::Carry) || m_registers.get_flag(Flag::Zero)) m_pc = dst;
}

void VM::exec_JG(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JG requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JG: "} + why); });    

    if (!m_registers.get_flag(Flag::Zero) && 
	m_registers.get_flag(Flag::Sign) == m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JNLE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNLE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNLE: "} + why); });    

    if (!m_registers.get_flag(Flag::Zero) && 
	m_registers.get_flag(Flag::Sign) == m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JGE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JGE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JGE: "} + why); });    

    if (m_registers.get_flag(Flag::Sign) == m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JNL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNL requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNL: "} + why); });    

    if (m_registers.get_flag(Flag::Sign) == m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JL requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JL: "} + why); });    

    if (m_registers.get_flag(Flag::Sign) != m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JNGE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNGE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNFE: "} + why); });    

    if (m_registers.get_flag(Flag::Sign) != m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JLE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JLE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JLE: "} + why); });    

    if (m_registers.get_flag(Flag::Zero) && 
	m_registers.get_flag(Flag::Sign) != m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JNG(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNG requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNG: "} + why); });    

    if (m_registers.get_flag(Flag::Zero) && 
	m_registers.get_flag(Flag::Sign) != m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JC requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JC: "} + why); });    

    if (m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JNC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNC requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNC: "} + why); });    

    if (!m_registers.get_flag(Flag::Carry)) m_pc = dst;
}

void VM::exec_JO(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JO requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JO: "} + why); });    

    if (m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JNO(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNO requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNO: "} + why); });    

    if (!m_registers.get_flag(Flag::Overflow)) m_pc = dst;
}

void VM::exec_JS(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JS requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JS: "} + why); });    

    if (m_registers.get_flag(Flag::Sign)) m_pc = dst;
}

void VM::exec_JNS(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNS requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNS: "} + why); });    

    if (!m_registers.get_flag(Flag::Sign)) m_pc = dst;
}

void VM::exec_JP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JP requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JP: "} + why); });    

    if (m_registers.get_flag(Flag::Parity)) m_pc = dst;
}

void VM::exec_JPE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JPE requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JPE: "} + why); });    

    if (m_registers.get_flag(Flag::Parity)) m_pc = dst;
}

void VM::exec_JNP(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNP requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JNP: "} + why); });    

    if (!m_registers.get_flag(Flag::Parity)) m_pc = dst;
}

void VM::exec_JPO(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JPO requires 1 operand");
    }

    uint32_t dst = get_value(operands[0], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"JPO: "} + why); });    

    if (!m_registers.get_flag(Flag::Parity)) m_pc = dst;
}

void VM::exec_INC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("INC requires 1 operand");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("INC first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, ++dst_value);
}

void VM::exec_DEC(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("DEC requires 1 operand");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("DEC first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    auto dst_value = m_registers.get(dst);

    m_registers.set(dst, --dst_value);
}

void VM::exec_SAL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SAL requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SAL first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    int32_t dst_value = static_cast<int32_t>(m_registers.get(dst));

    int32_t shift = static_cast<int32_t>(get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SAL: "} + why); }));
 
    if (shift == 0) return;

    shift = shift & 0x1F;

    bool carry = (dst_value >> (32 - shift)) & 0x1;

    uint32_t result = static_cast<uint32_t>(dst_value << shift);
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Carry, carry);

    bool bit31 = (result >> 31) & 0x1;
    bool bit30 = (result >> 30) & 0x1;
    m_registers.set_flag(Flag::Overflow, bit31 ^ bit30);

    m_registers.set_flag(Flag::Sign, bit31);
    m_registers.set_flag(Flag::Zero, result == 0);

    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count % 2) == 0);
}

void VM::exec_SAR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SAL requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SAL first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    int32_t dst_value = static_cast<int32_t>(m_registers.get(dst));

    int32_t shift = static_cast<int32_t>(get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SAL: "} + why); }));

    if (shift == 0) return;

    shift = shift & 0x1F;

    bool carry = (dst_value >> (shift - 1)) & 0x1;

    uint32_t result = static_cast<uint32_t>(dst_value >> shift);
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Carry, carry);
    m_registers.set_flag(Flag::Overflow, false);

    m_registers.set_flag(Flag::Sign, (result >> 31) & 0x1);
    m_registers.set_flag(Flag::Zero, result == 0);

    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count % 2) == 0);
}

void VM::exec_SHL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SHL requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SHL first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    uint32_t dst_value = m_registers.get(dst);

    uint32_t shift = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SHL: "} + why); });

    if (shift == 0) return;

    shift = shift & 0x1F;

    bool carry = (dst_value >> (32 - shift)) & 0x1;

    uint32_t result = dst_value << shift;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Carry, carry);

    bool bit31 = (result >> 31) & 0x1;
    bool bit30 = (result >> 30) & 0x1;
    m_registers.set_flag(Flag::Overflow, bit31 ^ bit30);

    m_registers.set_flag(Flag::Sign, bit31);
    m_registers.set_flag(Flag::Zero, result == 0);

    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count % 2) == 0);
}

void VM::exec_SHR(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 2) {
        throw std::invalid_argument("SHR requires 2 operands");
    }

    if (!std::holds_alternative<RegisterOpcode>(operands[0])) {
        throw std::invalid_argument("SHR first operand must be a register");
    }

    RegisterOpcode dst = std::get<RegisterOpcode>(operands[0]);
    uint32_t dst_value = m_registers.get(dst);

    uint32_t shift = get_value(operands[1], 
        [&](auto why){ Debugger::throw_arg_error(std::string{"SHR: "} + why); });

    if (shift == 0) return;

    shift = shift & 0x1F;

    bool carry = (dst_value >> (shift - 1)) & 0x1;
    bool overflow = (dst_value >> 31) & 0x1;

    uint32_t result = dst_value >> shift;
    m_registers.set(dst, result);

    m_registers.set_flag(Flag::Carry, carry);
    m_registers.set_flag(Flag::Overflow, overflow);

    m_registers.set_flag(Flag::Sign, (result >> 31) & 0x1);
    m_registers.set_flag(Flag::Zero, result == 0);

    uint8_t low_byte = result & 0xFF;
    uint8_t bit_count = std::popcount(low_byte);
    m_registers.set_flag(Flag::Parity, (bit_count % 2) == 0);
}
