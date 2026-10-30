# 🎓 Dynamic Weight Random Topic Picker

A smart and fair random topic picker designed for classroom use. Built with a high-performance C++ core algorithm and a friendly Python CLI interface.

## 🧠 Core Algorithm Rules

Unlike traditional random pickers, this system utilizes a **Dynamic Weighted Roulette Wheel** algorithm with a unique **Dual-Removal** mechanism:

1. **Pick**: Randomly select a number based on the current weights.
2. **Remove Self**: The picked number's weight immediately drops to 0.
3. **Remove Another**: The system silently picks and removes *another* random number (its weight also drops to 0) without returning it to the user.
4. **Boost**: All remaining numbers in the pool get a **+2%** weight boost (`weight *= 1.02`).
5. **Loop**: Repeat the process until the pool is empty.

*This ensures absolute fairness: no repeated numbers, and the remaining topics become progressively easier to be picked.*

## 📁 Project Structure

*   `random_algorithm.cpp`: The core C++ algorithm (exports standard C functions).
*   `main.py`: The Python console interface (uses `ctypes` to call the DLL).
*   `.gitignore`: Excludes compiled binaries (`*.dll`, `*.exe`) and Python cache from version control.

## 🚀 How to Use

### 1. Compile the C++ Core
Before running the Python script, you must compile the C++ code into a dynamic library.

**For Windows (using MinGW):**
```bash
g++ -shared -o random_algorithm.dll random_algorithm.cpp
```

### 📦 Quick Start (For Non-Developers)
If you just want to use the tool without compiling the code, I have provided the pre-compiled binaries:
1. Download `main.exe` and `random_algorithm.dll`.
2. Make sure **both files are in the same folder**.
3. Double-click `main.exe` to run.
