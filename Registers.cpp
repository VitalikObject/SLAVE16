#include "Registers.h"

Registers::Registers() {
    init_register_maps();
}

uint32_t Registers::get(RegisterOpcode opcode) const {
    auto it = m_reg_getters.find(opcode);
    if (it != m_reg_getters.end()) {
        return it->second();
    }
    throw std::out_of_range("Invalid register opcode for get");
}

void Registers::set(RegisterOpcode opcode, uint32_t value) {
    auto it = m_reg_setters.find(opcode);
    if (it != m_reg_setters.end()) {
        it->second(value);
    } else {
        throw std::out_of_range("Invalid register opcode for set");
    }
}

void Registers::init_register_maps() {
    m_reg_getters.clear();
    m_reg_setters.clear();

    // EAX family
    m_reg_getters[RegisterOpcode::EAX] = [this]() { return get_EAX(); };
    m_reg_setters[RegisterOpcode::EAX] = [this](uint32_t v) { set_EAX(v); };
    m_reg_getters[RegisterOpcode::AX]  = [this]() { return static_cast<uint32_t>(get_AX()); };
    m_reg_setters[RegisterOpcode::AX]  = [this](uint32_t v) { set_AX(static_cast<uint16_t>(v)); };
    m_reg_getters[RegisterOpcode::AH]  = [this]() { return static_cast<uint32_t>(get_AH()); };
    m_reg_setters[RegisterOpcode::AH]  = [this](uint32_t v) { set_AH(static_cast<uint8_t>(v)); };
    m_reg_getters[RegisterOpcode::AL]  = [this]() { return static_cast<uint32_t>(get_AL()); };
    m_reg_setters[RegisterOpcode::AL]  = [this](uint32_t v) { set_AL(static_cast<uint8_t>(v)); };

    // EBX family
    m_reg_getters[RegisterOpcode::EBX] = [this]() { return get_EBX(); };
    m_reg_setters[RegisterOpcode::EBX] = [this](uint32_t v) { set_EBX(v); };
    m_reg_getters[RegisterOpcode::BX]  = [this]() { return static_cast<uint32_t>(get_BX()); };
    m_reg_setters[RegisterOpcode::BX]  = [this](uint32_t v) { set_BX(static_cast<uint16_t>(v)); };
    m_reg_getters[RegisterOpcode::BH]  = [this]() { return static_cast<uint32_t>(get_BH()); };
    m_reg_setters[RegisterOpcode::BH]  = [this](uint32_t v) { set_BH(static_cast<uint8_t>(v)); };
    m_reg_getters[RegisterOpcode::BL]  = [this]() { return static_cast<uint32_t>(get_BL()); };
    m_reg_setters[RegisterOpcode::BL]  = [this](uint32_t v) { set_BL(static_cast<uint8_t>(v)); };

    // ECX family
    m_reg_getters[RegisterOpcode::ECX] = [this]() { return get_ECX(); };
    m_reg_setters[RegisterOpcode::ECX] = [this](uint32_t v) { set_ECX(v); };
    m_reg_getters[RegisterOpcode::CX]  = [this]() { return static_cast<uint32_t>(get_CX()); };
    m_reg_setters[RegisterOpcode::CX]  = [this](uint32_t v) { set_CX(static_cast<uint16_t>(v)); };
    m_reg_getters[RegisterOpcode::CH]  = [this]() { return static_cast<uint32_t>(get_CH()); };
    m_reg_setters[RegisterOpcode::CH]  = [this](uint32_t v) { set_CH(static_cast<uint8_t>(v)); };
    m_reg_getters[RegisterOpcode::CL]  = [this]() { return static_cast<uint32_t>(get_CL()); };
    m_reg_setters[RegisterOpcode::CL]  = [this](uint32_t v) { set_CL(static_cast<uint8_t>(v)); };

    // EDX family
    m_reg_getters[RegisterOpcode::EDX] = [this]() { return get_EDX(); };
    m_reg_setters[RegisterOpcode::EDX] = [this](uint32_t v) { set_EDX(v); };
    m_reg_getters[RegisterOpcode::DX]  = [this]() { return static_cast<uint32_t>(get_DX()); };
    m_reg_setters[RegisterOpcode::DX]  = [this](uint32_t v) { set_DX(static_cast<uint16_t>(v)); };
    m_reg_getters[RegisterOpcode::DH]  = [this]() { return static_cast<uint32_t>(get_DH()); };
    m_reg_setters[RegisterOpcode::DH]  = [this](uint32_t v) { set_DH(static_cast<uint8_t>(v)); };
    m_reg_getters[RegisterOpcode::DL]  = [this]() { return static_cast<uint32_t>(get_DL()); };
    m_reg_setters[RegisterOpcode::DL]  = [this](uint32_t v) { set_DL(static_cast<uint8_t>(v)); };

    // ESI/SI
    m_reg_getters[RegisterOpcode::ESI] = [this]() { return get_ESI(); };
    m_reg_setters[RegisterOpcode::ESI] = [this](uint32_t v) { set_ESI(v); };
    m_reg_getters[RegisterOpcode::SI]  = [this]() { return static_cast<uint32_t>(get_SI()); };
    m_reg_setters[RegisterOpcode::SI]  = [this](uint32_t v) { set_SI(static_cast<uint16_t>(v)); };

    // EDI/DI
    m_reg_getters[RegisterOpcode::EDI] = [this]() { return get_EDI(); };
    m_reg_setters[RegisterOpcode::EDI] = [this](uint32_t v) { set_EDI(v); };
    m_reg_getters[RegisterOpcode::DI]  = [this]() { return static_cast<uint32_t>(get_DI()); };
    m_reg_setters[RegisterOpcode::DI]  = [this](uint32_t v) { set_DI(static_cast<uint16_t>(v)); };

    // ESP/SP
    m_reg_getters[RegisterOpcode::ESP] = [this]() { return get_ESP(); };
    m_reg_setters[RegisterOpcode::ESP] = [this](uint32_t v) { set_ESP(v); };
    m_reg_getters[RegisterOpcode::SP]  = [this]() { return static_cast<uint32_t>(get_SP()); };
    m_reg_setters[RegisterOpcode::SP]  = [this](uint32_t v) { set_SP(static_cast<uint16_t>(v)); };

    // EBP/BP
    m_reg_getters[RegisterOpcode::EBP] = [this]() { return get_EBP(); };
    m_reg_setters[RegisterOpcode::EBP] = [this](uint32_t v) { set_EBP(v); };
    m_reg_getters[RegisterOpcode::BP]  = [this]() { return static_cast<uint32_t>(get_BP()); };
    m_reg_setters[RegisterOpcode::BP]  = [this](uint32_t v) { set_BP(static_cast<uint16_t>(v)); };
}