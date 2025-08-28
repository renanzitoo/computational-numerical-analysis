# Computational Numerical Analysis

This repository contains C implementations of various numerical methods for solving linear systems, developed as part of Computational Numerical Analysis studies.

## 📚 Implemented Methods

### 1. Triangular System
- **File**: [`triangularsystem.c`](triangularsystem.c)
- **Description**: Solves upper triangular systems using back substitution
- **Compilation**: `gcc -o triangularsystem triangularsystem.c`

### 2. Simple Gaussian Elimination
- **File**: [`simple-gauss.c`](simple-gauss.c)
- **Description**: Basic Gauss method without pivoting
- **Compilation**: `gcc -o simple-gauss simple-gauss.c`

### 3. Gaussian Elimination with Partial Pivoting
- **File**: [`parcial-gauss.c`](parcial-gauss.c)
- **Description**: Gauss with partial pivoting (row swapping)
- **Compilation**: `gcc -o parcial-gauss parcial-gauss.c -lm`

### 4. Gaussian Elimination with Complete Pivoting
- **File**: [`complete-gauss.c`](complete-gauss.c)
- **Description**: Gauss with complete pivoting (row and column swapping)
- **Compilation**: `gcc -o complete-gauss complete-gauss.c -lm`

### 5. Gauss-Jordan Method
- **File**: [`jordan-gauss.c`](jordan-gauss.c)
- **Description**: Complete elimination producing identity matrix
- **Compilation**: `gcc -o jordan-gauss jordan-gauss.c -lm`

### 6. LU Factorization
- **File**: [`lu-factorization.c`](lu-factorization.c)
- **Description**: Decomposes matrix A into lower (L) and upper (U) triangular matrices
- **Compilation**: `gcc -o lu-factorization lu-factorization.c`

## 🚀 How to Use

### Prerequisites
- GCC compiler
- Linux/Unix system (tested on Ubuntu)

### Compilation
```bash
# For basic methods
gcc -o program file.c

# For methods with mathematical functions
gcc -o program file.c -lm
```

### Execution
```bash
./program
```

### Input Format
All programs follow the same input format:

1. **System order**: integer n
2. **Coefficient matrix**: n×n numbers in matrix format
3. **Independent terms**: n numbers (vector b)

**Example for 2×2 system:**
```
System order: 2
Coefficient matrix:
2 3
1 4
Independent terms:
7
6
```

## 📊 Usage Example

### Example system:
```
2x + 3y = 7
1x + 4y = 6
```

### Input:
```
2
2 3
1 4
7
6
```

### Expected output:
```
Matrix L:
   1.000    0.000 
   0.500    1.000 

Matrix U:
   2.000    3.000 
   0.000    2.500 

The solution of the system is:
x1 = 2.000
x2 = 1.000
```

## 🔧 Method Characteristics

| Method | Pivoting | Stability | Complexity | Notes |
|--------|----------|-----------|------------|-------|
| Triangular | N/A | High | O(n²) | Triangular systems only |
| Simple Gauss | None | Low | O(n³) | May fail with zero pivots |
| Partial Gauss | Rows | Medium | O(n³) | Improves stability |
| Complete Gauss | Rows+Columns | High | O(n³) | Maximum stability |
| Gauss-Jordan | Complete | High | O(n³) | Final identity matrix |
| LU Factorization | None | Medium | O(n³) | Efficient for multiple RHS |

## 📁 Project Structure

```
computational-numerical-analysis/
├── triangularsystem.c      # Triangular system
├── simple-gauss.c          # Simple Gauss
├── parcial-gauss.c         # Partial Gauss
├── complete-gauss.c        # Complete Gauss
├── jordan-gauss.c          # Gauss-Jordan
├── lu-factorization.c      # LU Factorization
├── README.md               # This file
└── LICENSE                 # MIT License
```

## 🎯 Educational Objectives

This project demonstrates:
- Implementation of fundamental linear algebra algorithms
- Pivoting techniques for numerical stability
- Matrix factorization methods (LU decomposition)
- Dynamic memory management in C
- Different approaches to the same problem

## ⚠️ Limitations

- Single precision implementation (float)
- No zero determinant verification
- Command-line interface only
- No robust input error handling
- LU factorization without pivoting (may be unstable)

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest improvements
- Add new methods (Cholesky, QR, etc.)
- Improve documentation

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Renan Costa**

---

### 📝 Technical Notes

- The `-lm` flag is required for methods using `fabs()` from math library
- All methods use linear indexing for 2D matrices
- The `getOffset(i, j, n)` function converts (i,j) coordinates to linear index
- Dynamic memory allocation for support of any system order
- LU factorization uses Doolittle's method (L has 1's on diagonal)