/// File: matmul.h
/// Assignment 10 - Mastering Advanced C Programing - Shared Library and Dynamic Linking
/// Author: Yoon Seok Yang
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 23, 2024
/// Description: This program is a header file for matrix multiplication and handing dynamic link library function errors.

#ifndef __MATMUL__
#define __MATMUL__

#define ROWS_A 2
#define COLS_A 3
#define ROWS_B 3
#define COLS_B 2

/// @brief Prints an error message if the given expression returns NULL
/// @param p expression with possible NULL return representing an error
#define CHECKNULL_EXIT(p)                   \
    if((p) == NULL) {                       \
        fprintf(stderr,                     \
            "%s in file %s @ line %d\n",    \
            dlerror(), __FILE__, __LINE__); \
        exit(1);                            \
    }

/// @brief Multiplies matrices A and B and fills the product into C.
/// @param A first operand matrix
/// @param B second operand matrix
/// @param C product matrix
void matmul(int **A, int **B, int **C);

#endif
