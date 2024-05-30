/*
* File: dl.c
* Owner: Yoonseok Yang
* Date: 05.23.2024
* Description: Implement of matrix multiplication with dynamic linking functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "matmul.h"

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


    // --------------------------------------------------
    // Your implementation using dl functions
    
    // Load the shared library using dlopen


    // Get the symbol for matmul using dlsym
    

    // Call the matrix multiplication function using the function symbol


    // close the shared library


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
