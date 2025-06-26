#pragma once

#include "Interrupt.h"

class IInterruptHandler {
public:
    virtual ~IInterruptHandler() = default;
    virtual void handle_interrupt(const Interrupt& intr) = 0;
};