/// File: matmul.c
/// Assignment 10 - Mastering Advanced C Programing - Shared Library and Dynamic Linking
/// Author: Yoon Seok Yang
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 23, 2024
/// Description: This program implements a function of matrix multiplication for neural networks in C

#include <stdio.h>
#include <stdlib.h>
#include "matmul.h"

void matmul(int **A, int **B, int **C) {
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            C[i][j] = 0;// Initialize the result matrix element to 0
            for (int k = 0; k < COLS_A; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Perform matrix multiplication
            }
        }
    }
}
