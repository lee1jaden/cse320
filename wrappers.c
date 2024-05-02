/// File: wrappers.c
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program implements the wrapper class for handling errors with semaphores.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void SEM_init(sem_t *semaphore, int pshared, int value) {
    if (sem_init(semaphore, pshared, value) != 0) {
        printf("Error occurred while initializing semaphore.");
        exit(0);
    }
}

void SEM_destroy(sem_t *semaphore) {
    if (sem_destroy(semaphore) != 0) {
        printf("Error occurred while destroying semaphore.");
        exit(0);
    }
}

void SEM_wait(sem_t *semaphore) {
    if (sem_wait(semaphore) != 0) {
        printf("Error occurred while decrementing semaphore.");
        exit(0);
    }
}

void SEM_post(sem_t *semaphore) {
    if (sem_post(semaphore) != 0) {
        printf("Error occurred while incrementing semaphore.");
        exit(0);
    }
}