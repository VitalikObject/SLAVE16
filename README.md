# SLAVE16

![Status: Under Development](https://img.shields.io/badge/status-under%20development-yellow)
![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue)

## Overview

This project implements a simple x86-inspired virtual machine (VM) and interactive REPL (Read–Eval–Print Loop) written in C++. It supports a subset of common instructions (`MOV`, `ADD`, `SUB`, `MUL`, `DIV`, `XOR`, `PUSH`, `POP`) and register operations on 32-bit, 16-bit, and 8-bit registers (`EAX`, `AX`, `AH`, `AL`, etc.).

## Features

- **Instruction Set:** `MOV`, `ADD`, `SUB`, `MUL`, `DIV`, `XOR`, `PUSH`, `POP`.
- **Register Bank:** 32-bit registers (`EAX`, `EBX`, `ECX`, `EDX`, `ESI`, `EDI`, `ESP`, `EBP`) plus their 16-bit and 8-bit subdivisions.
- **Stack Operations:** Push and pop values to/from an internal program stack.
- **Interactive REPL:** Read–Eval–Print Loop for entering assembly-like instructions at runtime.

## Why?

Because coding is fun! 

## Building

```bash
make
./slave16
```

## Usage

Just start writing instructions in the console. Keep it simple, stupid!

## License

This project is released under the GNU General Public License v3.0. See [LICENSE](https://github.com/VitalikObject/SLAVE16/blob/master/LICENSE.txt) for details.
