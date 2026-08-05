# Assignment 01 – General Matrix Multiplication (GEMM) & CSR Graph

This assignment is a part of the **CS509** laboratory coursework and consists of the following individual tasks:

- **Task 01:** Simple General Matrix Multiplication (GEMM)
- **Task 02:** Blocking (Tiled) General Matrix Multiplication
- **Task 03:** Compressed Sparse Row (CSR) Graph Conversion

---

# Assignment Structure

```
Assignment_01
│
├── Task_01
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── Task_02
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── Task_03
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── common_wrapper.cpp
└── README.md
```

---

# Tasks

## Task 01 – Simple GEMM

Implements the conventional three-loop General Matrix Multiplication algorithm.

### Features

- Standard matrix multiplication
- Dynamic matrix input
- Execution time measurement

---

## Task 02 – Blocking GEMM

Implements blocked (tiled) matrix multiplication to improve cache locality and execution performance.

### Features

- Loop blocking
- Cache-aware implementation
- Performance comparison with Simple GEMM

---

## Task 03 – CSR Graph

Converts a graph stored as an adjacency list into the **Compressed Sparse Row (CSR)** representation.

### Features

- Sparse graph representation
- Efficient memory usage
- CSR preprocessing

---

# Compilation & Execution

Navigate to the Assignment directory.

```bash
cd Assignment_01
```

Compile the common wrapper.

```bash
g++ common_wrapper.cpp -o wrapper_app
```

Run the wrapper.

```bash
./wrapper_app
```

The wrapper provides a menu-driven interface to:

- Compile individual tasks
- Execute selected test cases
- Execute all available test cases
- Clean generated binaries

---

# GEMM Results

| Test File | Input Type / Size | Expected Output | Actual Output | Simple Time | Blocking Time | Block Size | Status |
|-----------|-------------------|-----------------|---------------|------------:|--------------:|-----------:|:------:|
| test_01.txt | 2×3 and 3×2 | Result Matrix | Result Matrix | 0.001247 ms | 0.000424 ms | 2 | ✅ Pass |
| test_02.txt (Simple) | 3×4 and 4×3 | Result Matrix | Result Matrix | 0.001443 ms | — | — | ✅ Pass |
| test_02.txt (Blocking) | 4×4 and 4×4 | Result Matrix | Result Matrix | — | 0.001229 ms | 2 | ✅ Pass |
| test_03.txt (Simple) | 4×4 and 4×5 | Result Matrix | Result Matrix | 0.001573 ms | — | — | ✅ Pass |
| test_03.txt (Blocking) | 3×5 and 5×2 | Result Matrix | Result Matrix | — | 0.001930 ms | 2 | ✅ Pass |
| test_03.txt (Blocking) | 3×5 and 5×2 | Result Matrix | Result Matrix | — | 0.001930 ms | 2 | ✅ Pass |
| test_250x250x250.txt (Simple) | 250x250 and 250x250 | Result Matrix | Result Matrix | 45.7471 ms | — | — | ✅ Pass |
| test_250x250x250.txt (Blocking) | 250x250 and 250x250 | Result Matrix | Result Matrix | — | 17.8189 ms | 64 | ✅ Pass |
| test_1000x1000x1000.txt (Simple) | 1000x1000 and 1000x1000 | Result Matrix | Result Matrix | 1656.36 ms | — | — | ✅ Pass |
| test_1000x1000x1000.txt (Blocking) | 1000x1000 and 1000x1000 | Result Matrix | Result Matrix | — | 935.576 ms | 64 | ✅ Pass |


> **Note:** The input matrices for `test_02.txt` and `test_03.txt` differ between the Simple GEMM and Blocking GEMM implementations. Therefore, they are reported as separate entries.

---

# CSR Graph Results

| Test File | Input Type / Size | Expected Output | Actual Output | Conversion Time | Status |
|-----------|-------------------|-----------------|---------------|----------------:|:------:|
| test_01.txt | Graph (V = 5, E = 5) | CSR Representation | CSR Representation | 0.001062 ms | ✅ Pass |
| test_02.txt | Graph (V = 4, E = 4) | CSR Representation | CSR Representation | 0.001941 ms | ✅ Pass |
| test_500.txt | Graph (V = 500, E = 499) | CSR Representation | CSR Representation | 0.005 ms | ✅ Pass |
| test_1000.txt | Graph (V = 1000, E = 999) | CSR Representation | CSR Representation | 0.014 ms | ✅ Pass |


---

# Performance Notes

Execution time measurements include **only the algorithm execution time**.

The following operations are **excluded** from timing:

- File reading
- Input parsing
- Memory allocation during setup
- Output generation
- CSR preprocessing (where applicable)

This follows the evaluation guidelines specified in the assignment document.

---

# Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC (g++)
- **Build System:** GNU Make
- **Platform:** Linux
