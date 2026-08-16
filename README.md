# CS509 Laboratory Assignments

This repository contains my individual laboratory assignments for the **CS509** course as part of my **M.Tech in Computer Science and Engineering** at **Indian Institute of Technology (IIT) Ropar**.

The repository serves as a centralized collection of all programming assignments completed during the course. Each assignment is organized into independent tasks with their own source code, drivers, test cases, outputs, and build configurations.

---

# Repository Structure

```
CS509_2026CSM1006
│
├── master_wrapper/          # Unified Master Project Manager
│   └── master_wrapper.cpp
│ 
├── Assignment_01
│   ├── Task_01
│   ├── Task_02
│   ├── Task_03
│   ├── common_wrapper.cpp
│   └── README.md
│
├── Assignment_02
│   ├── Task_01
│   ├── Task_02
│   ├── tools/
│   ├── common_wrapper.cpp
│   └── README.md
│
├── Assignment_03
│   ├── Task_01
│   ├── tools/
│   ├── common_wrapper.cpp
│   └── README.md
│
├── ...
│
└── README.md
```

As the course progresses, new assignment directories will be added while maintaining a consistent project structure.

---

# Assignment Organization

Each assignment is divided into one or more independent tasks.

A typical task follows the structure:

```
Task_xx/
│
├── driver/        # Driver program (main application)
├── source/        # Source and header files
├── test/          # Input test cases
├── output/        # Generated outputs
└── Makefile       # Build instructions
```

This modular organization keeps each implementation self-contained and easy to build, test, and evaluate.

---

## Build & Execution Instructions

### 1. Using the Master Project Manager (Recommended)

The most efficient way to navigate, compile, and test the assignments is by using the centralized **Master Wrapper**.

Run the following commands from the **root directory** of the repository:

#### Compile the Master Manager

```bash
g++ master_wrapper/master_wrapper.cpp -o master_app
```

Run the Manager
```bash
./master_app
```

This will launch a unified, menu-driven CLI that dynamically routes you to the specific sub-wrappers for each assignment.

### 2. Running Individual Assignment Wrappers

If you want to focus solely on a specific assignment, navigate to its folder and run its local wrapper.

For example, for Assignment 01:
```bash
cd Assignment_01
g++ common_wrapper.cpp -o wrapper_app
./wrapper_app
```

Replace Assignment_01 with the appropriate assignment directory when needed.

### 3. Manual Task Execution

To manually compile and run a specific algorithm without using the wrapper interface, navigate to the exact task directory and utilize the provided Makefile.

For example:
```bash
cd Assignment_01/Task_01
make run-all
```

This allows you to directly build and execute all configured targets for the selected task.

---

# Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC (g++)
- **Build System:** GNU Make
- **Platform:** Linux

---

# Repository Objectives

The assignments in this repository cover various topics in computer science and high-performance computing, including but not limited to:

- Matrix Computations (Simple & Blocked GEMM)
- Graph Algorithms (Bellman-Ford, Floyd-Warshall)
- Minimum Spanning Trees (Kruskal's & Prim's Algorithms)
- Sparse Data Structures (CSR Representation)
- Parallel Programming
- Performance Optimization
- Memory-efficient Algorithms
- Algorithm Analysis

The list above will continue to expand as new assignments are added throughout the semester.

---

# Academic Information

**Course:** CS509

**Programme:** M.Tech in Computer Science and Engineering

**Institute:** Indian Institute of Technology (IIT) Ropar

**Student:** Anmol Pandey

**Roll Number:** 2026CSM1006

---

## License

This repository is maintained for academic and educational purposes. Unauthorized copying or submission of the solutions as one's own coursework is discouraged.
