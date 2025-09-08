# Computational Numerical Analysis

This repository contains C implementations of various numerical methods for solving linear systems, developed as part of Computational Numerical Analysis studies.

## 📚 Implemented Methods

### Direct Methods

#### 1. Triangular System
- **File**: [`triangularsystem.c`](triangularsystem.c)
- **Description**: Solves upper triangular systems using back substitution
- **Compilation**: `gcc -o triangularsystem triangularsystem.c`

#### 2. Simple Gaussian Elimination
- **File**: [`simple-gauss.c`](simple-gauss.c)
- **Description**: Basic Gauss method without pivoting
- **Compilation**: `gcc -o simple-gauss simple-gauss.c`

#### 3. Gaussian Elimination with Partial Pivoting
- **File**: [`parcial-gauss.c`](parcial-gauss.c)
- **Description**: Gauss with partial pivoting (row swapping)
- **Compilation**: `gcc -o parcial-gauss parcial-gauss.c -lm`

#### 4. Gaussian Elimination with Complete Pivoting
- **File**: [`complete-gauss.c`](complete-gauss.c)
- **Description**: Gauss with complete pivoting (row and column swapping)
- **Compilation**: `gcc -o complete-gauss complete-gauss.c -lm`

#### 5. Gauss-Jordan Method
- **File**: [`jordan-gauss.c`](jordan-gauss.c)
- **Description**: Complete elimination producing identity matrix
- **Compilation**: `gcc -o jordan-gauss jordan-gauss.c -lm`

#### 6. LU Factorization
- **File**: [`lu-factorization.c`](lu-factorization.c)
- **Description**: Decomposes matrix A into lower (L) and upper (U) triangular matrices
- **Compilation**: `gcc -o lu-factorization lu-factorization.c`

### Iterative Methods

#### 7. Jacobi Method
- **File**: [`jacobi-gauss.c`](jacobi-gauss.c)
- **Description**: Iterative method using simultaneous updates from previous iteration
- **Compilation**: `gcc -o jacobi-gauss jacobi-gauss.c -lm`

#### 8. Gauss-Seidel Method
- **File**: [`seidel-gauss.c`](seidel-gauss.c)
- **Description**: Iterative method using updated values immediately as calculated
- **Compilation**: `gcc -o seidel-gauss seidel-gauss.c -lm`

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

#### Direct Methods
All direct methods follow the same input format:

1. **System order**: integer n
2. **Coefficient matrix**: n×n numbers in matrix format
3. **Independent terms**: n numbers (vector b)

#### Iterative Methods
Iterative methods require additional parameters:

1. **System order**: integer n
2. **Coefficient matrix**: n×n numbers in matrix format
3. **Independent terms**: n numbers (vector b)
4. **Tolerance**: convergence criterion (e.g., 0.001)
5. **Maximum iterations**: maximum number of iterations (e.g., 100)

**Example for 2×2 system:**
```
System order: 2
Coefficient matrix:
2 3
1 4
Independent terms:
7
6
Enter tolerance (e.g., 0.001): 0.001
Enter maximum iterations (e.g., 100): 50
```

## 📊 Usage Example

### Example system:
```
2x + 3y = 7
1x + 4y = 6
```

### Direct Methods Input:
```
2
2 3
1 4
7
6
```

### Iterative Methods Input:
```
2
2 3
1 4
7
6
0.001
50
```

### Expected output (Iterative Methods):
```
Warning: Matrix is not diagonally dominant. Convergence is not guaranteed.

Jacobi Method Iterations:
Iteration	x1		x2		Error
1		3.500000	1.500000	3.500000
2		1.750000	1.125000	1.750000
3		2.062500	0.937500	0.312500
...
Converged after 15 iterations with tolerance 0.001000

Final solution:
x1 = 2.000000
x2 = 1.000000
```

## 🔧 Method Characteristics

| Method | Type | Pivoting | Stability | Complexity | Convergence |
|--------|------|----------|-----------|------------|-------------|
| Triangular | Direct | N/A | High | O(n²) | Guaranteed |
| Simple Gauss | Direct | None | Low | O(n³) | May fail |
| Partial Gauss | Direct | Rows | Medium | O(n³) | Guaranteed |
| Complete Gauss | Direct | Rows+Columns | High | O(n³) | Guaranteed |
| Gauss-Jordan | Direct | Complete | High | O(n³) | Guaranteed |
| LU Factorization | Direct | None | Medium | O(n³) | May fail |
| Jacobi | Iterative | N/A | Medium | O(n²·k) | Conditional |
| Gauss-Seidel | Iterative | N/A | Medium | O(n²·k) | Conditional |

*k = number of iterations required*

## 📁 Project Structure

```
computational-numerical-analysis/
├── triangularsystem.c      # Triangular system
├── simple-gauss.c          # Simple Gauss
├── parcial-gauss.c         # Partial Gauss
├── complete-gauss.c        # Complete Gauss
├── jordan-gauss.c          # Gauss-Jordan
├── lu-factorization.c      # LU Factorization
├── jacobi-gauss.c          # Jacobi Method
├── seidel-gauss.c          # Gauss-Seidel Method
├── README.md               # This file
└── LICENSE                 # MIT License
```

## 🎯 Educational Objectives

This project demonstrates:
- Implementation of fundamental linear algebra algorithms
- Comparison between direct and iterative methods
- Pivoting techniques for numerical stability
- Matrix factorization methods (LU decomposition)
- Iterative convergence criteria and error analysis
- Diagonal dominance importance for iterative methods
- Dynamic memory management in C
- Different approaches to the same problem

## 🔄 Iterative Methods Notes

### Convergence Requirements
- **Diagonal Dominance**: For guaranteed convergence, the matrix should be diagonally dominant:
  ```
  |a[i][i]| > Σ|a[i][j]| for all i ≠ j
  ```
- **Tolerance**: Controls precision of the solution
- **Maximum Iterations**: Prevents infinite loops

### Method Comparison
- **Jacobi**: Uses all values from previous iteration simultaneously
- **Gauss-Seidel**: Uses updated values immediately, typically converges faster

### When to Use Iterative Methods
- Large sparse systems
- When direct methods are computationally expensive
- Systems with special structure
- When approximate solutions are acceptable

## ⚠️ Limitations

- Single precision implementation (float)
- No zero determinant verification for direct methods
- Iterative methods may not converge for non-diagonally dominant matrices
- Command-line interface only
- No robust input error handling
- LU factorization without pivoting (may be unstable)

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest improvements
- Add new methods (SOR, Cholesky, QR, etc.)
- Improve documentation
- Add double precision versions

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
- Iterative methods check diagonal dominance and warn if not satisfied
- Error calculation uses maximum absolute difference between iterations