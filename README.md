AC-Linux-External

Educational external project for studying game process interaction on Linux.
This project focuses on architecture, memory access techniques, and modular design of external tools.

This project is created strictly for **educational and research purposes** to explore how user-mode applications can interact with other processes in a controlled environment.


## Overview

AC-Linux-External is a **C++ Linux user-mode external application** designed as a learning project to research:

* Process memory interaction
* Modular software architecture
* Process management
* Rendering pipeline preparation
* Offset-based memory structures

The project is still in **early development stage** and serves as a foundation for experimenting with low-level interaction techniques.

---

## 🏗 Architecture

The project is structured with modularity in mind:

```
/features   → feature logic layer  
/memory     → process memory access & management  
/render     → rendering/overlay preparation layer  
/sdk        → data structures & game-related abstractions  
main.cpp    → application entry point  
Offsets.h   → static offset definitions  
```

Design goals:

* Fully **external (separate process)**
* **User-mode only** (no kernel components)
* Expandable module system
* Clean separation between memory, logic, and rendering layers

---

## 💾 Memory Research

This project explores Linux process interaction using:

* `process_vm_readv`
* `process_vm_writev`

Techniques used:

* Static offset-based access
* Structured memory reading
* External process communication patterns

Future plans include improving offset handling and memory abstraction.

---

## 🎛 Interface

Currently:

* No GUI (CLI-based execution)

Planned:

* ImGui-based interface
* Basic configuration system
* Runtime settings management

---

## ⚙ Technical Features

* Process manager
* Multi-component architecture
* Stable user-mode design
* Expandable rendering layer
* CMake-based build system

---

## 🎯 Purpose

This project is intended for:

* Learning low-level process interaction
* Understanding external application architecture
* Portfolio demonstration
* Researching software structure for real-time tools

---

## 🛠 Build

### Requirements

* Linux
* C++ compiler (GCC / Clang)
* CMake

### Build Steps

```bash
git clone <repo>
cd AC-Linux-External
mkdir build
cd build
cmake ..
make
```

---

## 📚 License

MIT License

---

## ⚠ Disclaimer

This repository is provided for **educational and research purposes only**.
The goal is to study software architecture and process interaction mechanisms, not to promote misuse.

---

## 🚧 Project Status

Early development. Architecture and core systems are being built.
