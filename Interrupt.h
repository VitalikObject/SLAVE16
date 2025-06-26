#pragma once

#include "Registers.h"
#include <cstdint>
#include <variant>
#include <functional>

enum class InterruptType : uint8_t {
    // --- Console I/O ---
    ReadCharWithEcho        = 0x01, // AH=01h: read character with echo (stdin)
    WriteChar               = 0x02, // AH=02h: write character (DL contains character)
    DirectConsoleIO         = 0x06, // AH=06h: direct console I/O (AL=0 for input)
    ReadCharNoEcho          = 0x07, // AH=07h: read character without echo
    WriteString             = 0x09, // AH=09h: write "$"-terminated string (DS:DX -> string)
    BufferedInput           = 0x0A, // AH=0Ah: buffered input (DS:DX -> input buffer)

    // --- Interrupt vector manipulation ---
    SetInterruptVector      = 0x25, // AH=25h: set interrupt handler address
    GetInterruptVector      = 0x35, // AH=35h: get current interrupt handler address

    // --- Date/Time operations ---
    GetSystemDate           = 0x2A, // AH=2Ah: get current date
    SetSystemDate           = 0x2B, // AH=2Bh: set current date
    GetSystemTime           = 0x2C, // AH=2Ch: get current time
    SetSystemTime           = 0x2D, // AH=2Dh: set current time

    // --- DOS version, environment, PSP, etc. ---
    GetDOSVersion           = 0x30, // AH=30h: get DOS version

    // --- Directory and path operations ---
    SetCurrentDirectory     = 0x3B, // AH=3Bh: set current directory (DS:DX -> ASCIIZ path)
    GetCurrentDirectory     = 0x47, // AH=47h: get current directory (prepare buffer)

    // --- File operations ---
    CreateFile              = 0x3C, // AH=3Ch: create file (DS:DX -> ASCIIZ name, CX=attributes)
    OpenFile                = 0x3D, // AH=3Dh: open file (DS:DX -> name, AL=mode)
    CloseFile               = 0x3E, // AH=3Eh: close file (BX = file handle)
    ReadFile                = 0x3F, // AH=3Fh: read from file (BX=handle, CX=size, DS:DX=buffer)
    WriteFile               = 0x40, // AH=40h: write to file (BX=handle, CX=size, DS:DX=buffer)
    DeleteFile              = 0x41, // AH=41h: delete file (DS:DX -> ASCIIZ name)
    MoveFilePointer         = 0x42, // AH=42h: move file pointer (BX=handle, CX:DX=offset, AL=method)
    GetSetFileAttr          = 0x43, // AH=43h: get/set file attributes (AL=0 get, AL=1 set)
    FindFirst               = 0x4E, // AH=4Eh: find first file matching pattern (DS:DX -> pattern, CX=attributes)
    FindNext                = 0x4F, // AH=4Fh: find next matching file (BX = search handle)
    RenameFile              = 0x56, // AH=56h: rename file (DS:DX -> old name, ES:DI -> new name)
    GetDateTime             = 0x57, // AH=57h: get/set file date/time (AL=0 get, AL=1 set; BX=handle)
    DuplicateFileHandle     = 0x58, // AH=58h: duplicate file handle (BX=source, CX=new handle)
    GetReturnCode           = 0x59, // AH=59h: get return code of terminated program

    // --- Memory operations ---
    AllocateMemory          = 0x48, // AH=48h: allocate memory block in paragraphs (BX = number of paragraphs)
    FreeMemory              = 0x49, // AH=49h: free memory block (ES = segment of block)

    // --- Program termination ---
    TerminateProcess        = 0x4C, // AH=4Ch: terminate program with return code (AL = code)

    // --- Disk and filesystem info ---
    GetDiskFree             = 0x36, // AH=36h: get disk free space info (DL = drive number)
};


struct Interrupt {
    static constexpr int API = 0x21;

    InterruptType type;
    const Registers& registers;

    Interrupt(InterruptType t, const Registers& reg) : type(t), registers(reg) {}
};