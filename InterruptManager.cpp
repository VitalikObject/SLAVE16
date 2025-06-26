#include "InterruptManager.h"
#include "Interrupt.h"

void InterruptManager::register_handler(IInterruptHandler& handler) {
    std::lock_guard<std::mutex> lk(m_mtx);
    m_handlers.push_back(&handler);
}

void InterruptManager::unregister_handler(IInterruptHandler& handler) {
    std::lock_guard<std::mutex> lk(m_mtx);
    m_handlers.erase(
        std::remove(m_handlers.begin(), m_handlers.end(), &handler),
        m_handlers.end()
    );
}

void InterruptManager::notify(const Interrupt& intr) {
    std::lock_guard<std::mutex> lk(m_mtx);
    for (auto handler : m_handlers) {
        handler->handle_interrupt(intr);
    }
}