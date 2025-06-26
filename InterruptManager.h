#pragma once

#include "IInterruptHandler.h"
#include <vector>
#include <mutex>

class InterruptManager {
public:
    void register_handler(IInterruptHandler& handler);
    void unregister_handler(IInterruptHandler& handler);
    void notify(const Interrupt& intr);
private:
    std::vector<IInterruptHandler*> m_handlers;
    std::mutex m_mtx;
};