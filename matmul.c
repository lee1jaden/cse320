/*
* File: matmul.c
* Owner: Yoonseok Yang
* Date: 05.23.2024
* Description: Function of matrix multiplication for neural network in C
*/

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
