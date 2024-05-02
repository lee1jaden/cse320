/// File: wrappers.h
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program declares the wrapper class for handling errors with semaphores.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/// @brief Wrapper method for sem_init that handles error results.
/// @param semaphore semaphore to be initialized
/// @param pshared = 0
/// @param value initial value
void SEM_init(sem_t *semaphore, int pshared, int value);

/// @brief Wrapper method for sem_destroy that handles error results
/// @param semaphore semaphore to be destroyed
void SEM_destroy(sem_t *semaphore);

/// @brief Wrapper method for sem_wait that handles error results
/// @param semaphore semaphore to be decremented
void SEM_wait(sem_t *semaphore);

/// @brief Wrapper method for sem_post that handles error results
/// @param semaphore semaphore to be incremented
void SEM_post(sem_t *semaphore);