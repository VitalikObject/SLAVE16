#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>
#include "Instruction.h"

class Registers {
private:
    uint32_t m_eax {}, m_ebx {}, m_ecx {}, m_edx {};
    uint32_t m_esi {}, m_edi {}, m_esp {}, m_ebp {};

    std::unordered_map<RegisterOpcode, std::function<uint32_t()>> m_reg_getters;
    std::unordered_map<RegisterOpcode, std::function<void(uint32_t)>> m_reg_setters;    

public:
    Registers();
    
    void init_register_maps();

    std::string info() const;

    uint32_t get(RegisterOpcode opcode) const;
    void set(RegisterOpcode opcode, uint32_t value);

    // ====== EAX ======
    uint32_t get_EAX() const { return m_eax; }
    void     set_EAX(uint32_t v) { m_eax = v; }

    uint16_t get_AX() const { return m_eax & 0xFFFF; }
    void     set_AX(uint16_t v) { m_eax = (m_eax & 0xFFFF0000) | v; }

    uint8_t  get_AH() const { return uint8_t((m_eax >> 8) & 0xFF); }
    void     set_AH(uint8_t v) { m_eax = (m_eax & 0xFFFF00FF) | (uint32_t(v) << 8); }

    uint8_t  get_AL() const { return uint8_t(m_eax & 0xFF); }
    void     set_AL(uint8_t v) { m_eax = (m_eax & 0xFFFFFF00) | v; }

    // ====== EBX ======
    uint32_t get_EBX() const { return m_ebx; }
    void     set_EBX(uint32_t v) { m_ebx = v; }

    uint16_t get_BX() const { return m_ebx & 0xFFFF; }
    void     set_BX(uint16_t v) { m_ebx = (m_ebx & 0xFFFF0000) | v; }

    uint8_t  get_BH() const { return uint8_t((m_ebx >> 8) & 0xFF); }
    void     set_BH(uint8_t v) { m_ebx = (m_ebx & 0xFFFF00FF) | (uint32_t(v) << 8); }

    uint8_t  get_BL() const { return uint8_t(m_ebx & 0xFF); }
    void     set_BL(uint8_t v) { m_ebx = (m_ebx & 0xFFFFFF00) | v; }

    // ====== ECX ======
    uint32_t get_ECX() const { return m_ecx; }
    void     set_ECX(uint32_t v) { m_ecx = v; }

    uint16_t get_CX() const { return m_ecx & 0xFFFF; }
    void     set_CX(uint16_t v) { m_ecx = (m_ecx & 0xFFFF0000) | v; }

    uint8_t  get_CH() const { return uint8_t((m_ecx >> 8) & 0xFF); }
    void     set_CH(uint8_t v) { m_ecx = (m_ecx & 0xFFFF00FF) | (uint32_t(v) << 8); }

    uint8_t  get_CL() const { return uint8_t(m_ecx & 0xFF); }
    void     set_CL(uint8_t v) { m_ecx = (m_ecx & 0xFFFFFF00) | v; }

    // ====== EDX ======
    uint32_t get_EDX() const { return m_edx; }
    void     set_EDX(uint32_t v) { m_edx = v; }

    uint16_t get_DX() const { return m_edx & 0xFFFF; }
    void     set_DX(uint16_t v) { m_edx = (m_edx & 0xFFFF0000) | v; }

    uint8_t  get_DH() const { return uint8_t((m_edx >> 8) & 0xFF); }
    void     set_DH(uint8_t v) { m_edx = (m_edx & 0xFFFF00FF) | (uint32_t(v) << 8); }

    uint8_t  get_DL() const { return uint8_t(m_edx & 0xFF); }
    void     set_DL(uint8_t v) { m_edx = (m_edx & 0xFFFFFF00) | v; }

    // ====== ESI ======
    uint32_t get_ESI() const { return m_esi; }
    void     set_ESI(uint32_t v) { m_esi = v; }

    uint16_t get_SI() const { return m_esi & 0xFFFF; }
    void     set_SI(uint16_t v) { m_esi = (m_esi & 0xFFFF0000) | v; }

    // ====== EDI ======
    uint32_t get_EDI() const { return m_edi; }
    void     set_EDI(uint32_t v) { m_edi = v; }

    uint16_t get_DI() const { return m_edi & 0xFFFF; }
    void     set_DI(uint16_t v) { m_edi = (m_edi & 0xFFFF0000) | v; }

    // ====== ESP ======
    uint32_t get_ESP() const { return m_esp; }
    void     set_ESP(uint32_t v) { m_esp = v; }

    uint16_t get_SP() const { return m_esp & 0xFFFF; }
    void     set_SP(uint16_t v) { m_esp = (m_esp & 0xFFFF0000) | v; }

    // ====== EBP ======
    uint32_t get_EBP() const { return m_ebp; }
    void     set_EBP(uint32_t v) { m_ebp = v; }

    uint16_t get_BP() const { return m_ebp & 0xFFFF; }
    void     set_BP(uint16_t v) { m_ebp = (m_ebp & 0xFFFF0000) | v; }
};