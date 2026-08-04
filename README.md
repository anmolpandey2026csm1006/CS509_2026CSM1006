# CS509 Laboratory Assignments

This repository contains my individual laboratory assignments for the **CS509** course as part of my **M.Tech in Computer Science and Engineering** at **Indian Institute of Technology (IIT) Ropar**.

The repository serves as a centralized collection of all programming assignments completed during the course. Each assignment is organized into independent tasks with their own source code, drivers, test cases, outputs, and build configurations.

---

# Repository Structure

```
CS509_2026CSM1006
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
│   ├── ...
│
├── Assignment_03
│   ├── ...
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
├── driver/        # Driver program
├── source/        # Source and header files
├── test/          # Input test cases
├── output/        # Generated outputs
└── Makefile       # Build instructions
```

This modular organization keeps each implementation self-contained and easy to build, test, and evaluate.

---

# Build Instructions

Navigate to the desired task directory.

Example:

```bash
cd Assignment_01/Task_01
```

Compile using the provided Makefile:

```bash
make
```

Run the generated executable:

```bash
./main
```

For assignments that provide a common wrapper, compile it using:

```bash
g++ common_wrapper.cpp -o wrapper_app
```

and execute

```bash
./wrapper_app
```

---

# Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC (g++)
- **Build System:** GNU Make
- **Platform:** Linux

---

# Repository Objectives

The assignments in this repository cover various topics in computer science and high-performance computing, including but not limited to:

- Matrix Computations
- Graph Algorithms
- Sparse Data Structures
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
