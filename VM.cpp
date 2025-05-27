#include "VM.h"

VM::VM() {
    m_dispatch[InstructionOpcode::MOV] = [this](const std::vector<InstructionArg>& operands){ exec_MOV(operands); };
    m_dispatch[InstructionOpcode::ADD] = [this](const std::vector<InstructionArg>& operands){ exec_ADD(operands); };
    m_dispatch[InstructionOpcode::SUB] = [this](const std::vector<InstructionArg>& operands){ exec_SUB(operands); };
    m_dispatch[InstructionOpcode::MUL] = [this](const std::vector<InstructionArg>& operands){ exec_MUL(operands); };
    m_dispatch[InstructionOpcode::DIV] = [this](const std::vector<InstructionArg>& operands){ exec_DIV(operands); };
    m_dispatch[InstructionOpcode::XOR] = [this](const std::vector<InstructionArg>& operands){ exec_XOR(operands); };
    m_dispatch[InstructionOpcode::PUSH] = [this](const std::vector<InstructionArg>& operands){ exec_PUSH(operands); };
    m_dispatch[InstructionOpcode::POP] = [this](const std::vector<InstructionArg>& operands){ exec_POP(operands); };
};  

void VM::execute(const Instruction& instr) {
    auto it = m_dispatch.find(instr.opcode);
    if (it != m_dispatch.end()) {
        it->second(instr.operands);
        this->step();
    } else {
        throw std::invalid_argument("Unknown opcode!");
        return;
    }
}

void VM::step() {
    m_pc += 1;
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
        } else if constexpr (std::is_same_v<T, double>) {
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
        } else if constexpr (std::is_same_v<T, double>) {
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
        } else if constexpr (std::is_same_v<T, double>) {
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
        } else if constexpr (std::is_same_v<T, double>) {
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
        } else if constexpr (std::is_same_v<T, double>) {
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
        } else if constexpr (std::is_same_v<T, double>) {
            m_registers.set(dst, (dst_value ^ static_cast<uint32_t>(src))); 
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
        } else if constexpr (std::is_same_v<T, double>) {
            m_program_stack.push(static_cast<uint32_t>(src));
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