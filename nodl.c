/// File: nodl.c
/// Assignment 10 - Mastering Advanced C Programing - Shared Library and Dynamic Linking
/// Author: Yoon Seok Yang
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 23, 2024
/// Description: This program is an implementation of matrix multiplication without dynamic linking functions for reference.

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "matmul.h"

/// @brief Conducts matrix multiplication of the matrices in 'matA.txt' and 'matB.txt' and outputs it to 'matOut.txt'
/// @return 0 if successful, nonzero otherwise
int main() {
    FILE *inMatA;
    FILE *inMatB;
    FILE *outFile;
    int **matA;
    int **matB;
    int **matOut;

    // Allocate memory for matA, matB, and matOut
    matA = (int **)malloc(ROWS_A * sizeof(int *));
    matB = (int **)malloc(ROWS_B * sizeof(int *));
    matOut = (int **)malloc(ROWS_A * sizeof(int *));

    for(int i = 0; i < ROWS_A; i++){
        matA[i] = (int *)malloc(COLS_A * sizeof(int));
        matOut[i] = (int *)malloc(COLS_B * sizeof(int));
    }
    for(int i = 0; i < ROWS_B; i++){
        matB[i] = (int *)malloc(COLS_B * sizeof(int));
    }

    // Open the file for reading and load integers to matA and matB
    inMatA = fopen("matA.txt", "rt");
    inMatB = fopen("matB.txt", "rt");
    for(int i = 0; i < ROWS_A; i++){
        for(int j = 0; j < COLS_A; j++){
            fscanf(inMatA, "%d", &matA[i][j]);
        }
    }

    for(int i = 0; i < ROWS_B; i++){
        for(int j = 0; j < COLS_B; j++){
            fscanf(inMatB, "%d", &matB[i][j]);
        }
    }

    // Multiply matrices matA and matB
    matmul(matA, matB, matOut);

    // Write the result of the matrix multiplication
    outFile = fopen("matOut.txt", "wt");
    for(int i = 0; i < ROWS_A; i++){
        for(int j = 0; j < COLS_B; j++){
            fprintf(outFile, "%d\n", matOut[i][j]);
        }
    }

    // Free the dynamically allocated memories
    for(int i = 0; i < ROWS_A; i++){
        free(matA[i]);
        free(matOut[i]);
    }
    for(int i = 0; i < ROWS_B; i++){
        free(matB[i]);
    }
    free(matA);
    free(matB);
    free(matOut);

    // Close the file
    fclose(inMatA);
    fclose(inMatB);
    fclose(outFile);

    return 0;
}
