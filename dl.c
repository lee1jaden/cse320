/// File: dl.c
/// Assignment 10 - Mastering Advanced C Programing - Shared Library and Dynamic Linking
/// Author: Yoon Seok Yang and Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 23, 2024
/// Description: This program implements matrix multiplication with dynamic linking functions.

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "matmul.h"

/// @brief Conducts matrix multiplication of the matrices in 'matA.txt' and 'matB.txt' and outputs it to 'matOut.txt'
///     This program uses dynamic linking functions.
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

    // Open the file for reading and load integers to matA and matB. Exit gracefully if the files do not exist.
    inMatA = fopen("matA.txt", "rt");
    if (inMatA == NULL) {
        printf("Error: Couldn't located 'matA.txt'.\n");
        exit(EXIT_FAILURE);
    }
    inMatB = fopen("matB.txt", "rt");
    if (inMatB == NULL) {
        printf("Error: Couldn't located 'matB.txt'.\n");
        exit(EXIT_FAILURE);
    }
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


    // Your implementation using dl functions. Using the macro will output an error message if dynamically linking fails.
    // --------------------------------------------------

    // Load the shared library using dlopen
    void *handle;
    CHECKNULL_EXIT(handle = dlopen("./matmul.so", RTLD_LAZY | RTLD_GLOBAL));

    // Get the symbol for matmul using dlsym
    void (*_matmul)(int **A, int **B, int **C);
    CHECKNULL_EXIT(_matmul = dlsym(handle, "matmul"));

    // Call the matrix multiplication function using the function symbol
    _matmul(matA, matB, matOut);

    // close the shared library
    dlclose(handle);

    // --------------------------------------------------


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
