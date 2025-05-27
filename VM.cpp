#include "VM.h"
#include <iostream>

VM::VM() {
    m_dispatch[InstructionOpcode::MOV] = [this](const std::vector<InstructionArg>& operands){ exec_MOV(operands); };
    m_dispatch[InstructionOpcode::ADD] = [this](const std::vector<InstructionArg>& operands){ exec_ADD(operands); };
    m_dispatch[InstructionOpcode::SUB] = [this](const std::vector<InstructionArg>& operands){ exec_SUB(operands); };
    m_dispatch[InstructionOpcode::MUL] = [this](const std::vector<InstructionArg>& operands){ exec_MUL(operands); };
    m_dispatch[InstructionOpcode::DIV] = [this](const std::vector<InstructionArg>& operands){ exec_DIV(operands); };
    m_dispatch[InstructionOpcode::XOR] = [this](const std::vector<InstructionArg>& operands){ exec_XOR(operands); };
    m_dispatch[InstructionOpcode::PUSH] = [this](const std::vector<InstructionArg>& operands){ exec_PUSH(operands); };
    m_dispatch[InstructionOpcode::POP] = [this](const std::vector<InstructionArg>& operands){ exec_POP(operands); };
    m_dispatch[InstructionOpcode::JMP] = [this](const std::vector<InstructionArg>& operands){ exec_JMP(operands); };
    m_dispatch[InstructionOpcode::CMP] = [this](const std::vector<InstructionArg>& operands){ exec_CMP(operands); };
    m_dispatch[InstructionOpcode::JE] = [this](const std::vector<InstructionArg>& operands){ exec_JE(operands); };
    m_dispatch[InstructionOpcode::JNE] = [this](const std::vector<InstructionArg>& operands){ exec_JNE(operands); };
    m_dispatch[InstructionOpcode::JZ] = [this](const std::vector<InstructionArg>& operands){ exec_JZ(operands); };
    m_dispatch[InstructionOpcode::JNZ] = [this](const std::vector<InstructionArg>& operands){ exec_JNZ(operands); };
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
            std::cout << ParseUtils::info_about_registers(m_registers) << std::endl;
#endif
        }
    }
}

void VM::step(int step) {
    m_pc += step;
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

    std::visit([this, dst](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, src);
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, val);
        } else {
            throw std::invalid_argument("Unsupported operand type in MOV");
        }
    }, operands[1]);
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

    std::visit([this, dst, dst_value](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, (dst_value + src));
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, (dst_value + val));
        } else {
            throw std::invalid_argument("Unsupported operand type in ADD");
        }
    }, operands[1]);
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

    std::visit([this, dst, dst_value](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, (dst_value - src));
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, (dst_value - val));
        } else {
            throw std::invalid_argument("Unsupported operand type in SUB");
        }
    }, operands[1]);
}

void VM::exec_MUL(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("MUL requires 1 operand");
        return;
    }

    RegisterOpcode dst = RegisterOpcode::EAX;
    auto dst_value = m_registers.get(dst);

    std::visit([this, dst, dst_value](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, (dst_value * src));
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, (dst_value * val));
        } else {
            throw std::invalid_argument("Unsupported operand type in MUL");
        }
    }, operands[0]);
}

void VM::exec_DIV(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("DIV requires 1 operand");
        return;
    }

    RegisterOpcode dst = RegisterOpcode::EAX;
    auto dst_value = m_registers.get(dst);

    std::visit([this, dst, dst_value](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, (dst_value / src));
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, (dst_value / val));
        } else {
            throw std::invalid_argument("Unsupported operand type in DIV");
        }
    }, operands[0]);
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

    std::visit([this, dst, dst_value](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_registers.set(dst, (dst_value ^ src));
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_registers.set(dst, (dst_value ^ val));
        } else {
            throw std::invalid_argument("Unsupported operand type in XOR");
        }
    }, operands[1]); 
}

void VM::exec_PUSH(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("PUSH requires 1 operand");
        return;
    }

    std::visit([this](auto&& src) {
        using T = std::decay_t<decltype(src)>;
        
        if constexpr (std::is_same_v<T, int>) {
            m_program_stack.push(src);
        } else if constexpr (std::is_same_v<T, RegisterOpcode>) {
            auto val = m_registers.get(src);
            m_program_stack.push(val);
        } else {
            throw std::invalid_argument("Unsupported operand type in PUSH");
        }
    }, operands[0]);
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

    uint32_t b_value = std::visit([this](auto&& arg) -> uint32_t {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RegisterOpcode>) {
            return m_registers.get(arg);
        } else if constexpr (std::is_same_v<T, int>) {
            return static_cast<uint32_t>(arg);
        } else {
            throw std::invalid_argument("Unsupported operand type in CMP");
        }
    }, operands[1]);    

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

    uint32_t dst = std::visit([this](auto&& arg) -> uint32_t {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RegisterOpcode>) {
            return m_registers.get(arg);
        } else if constexpr (std::is_same_v<T, int>) {
            return static_cast<uint32_t>(arg);
        } else {
            throw std::invalid_argument("Unsupported operand type in JE");
        }
    }, operands[0]);  

    if (get_ZF()) m_pc = dst;
}

void VM::exec_JNE(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNE requires 1 operand");
        return;
    }

    uint32_t dst = std::visit([this](auto&& arg) -> uint32_t {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RegisterOpcode>) {
            return m_registers.get(arg);
        } else if constexpr (std::is_same_v<T, int>) {
            return static_cast<uint32_t>(arg);
        } else {
            throw std::invalid_argument("Unsupported operand type in JNE");
        }
    }, operands[0]);    

    if (!get_ZF()) m_pc = dst;
}

void VM::exec_JZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JZ requires 1 operand");
        return;
    }

    uint32_t dst = std::visit([this](auto&& arg) -> uint32_t {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RegisterOpcode>) {
            return m_registers.get(arg);
        } else if constexpr (std::is_same_v<T, int>) {
            return static_cast<uint32_t>(arg);
        } else {
            throw std::invalid_argument("Unsupported operand type in JZ");
        }
    }, operands[0]);    

    if (get_ZF()) m_pc = dst;
}

void VM::exec_JNZ(const std::vector<InstructionArg>& operands) {
    if (operands.size() != 1) {
        throw std::invalid_argument("JNZ requires 1 operand");
        return;
    }

    uint32_t dst = std::visit([this](auto&& arg) -> uint32_t {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, RegisterOpcode>) {
            return m_registers.get(arg);
        } else if constexpr (std::is_same_v<T, int>) {
            return static_cast<uint32_t>(arg);
        } else {
            throw std::invalid_argument("Unsupported operand type in JNZ");
        }
    }, operands[0]);    

    if (!get_ZF()) m_pc = dst;
}