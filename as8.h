/// File: as8.h
/// Assignment 8 - Mastering Advanced C Programing Concepts - Semaphores 2
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 13, 2024
/// Description: This program declares the sleeping barber problem in C.

#ifndef AS8_H
#define AS8_H

#define NUM_CHAIRS 5

/// @brief Thread function for a barber in the sleeping barber problem. If no customers are waiting, they will fall asleep
///     in the chair until a customer arrives to wake them. When completed with a haircut, they will check the waiting room 
///     for waiting customers.
/// @param arg NULL (void* argument needed for thread function)
/// @return NULL
void* barber(void* arg);

/// @brief Thread function for a customer in the sleeping barber problem. Wakes the barber if they are asleep. If they arrive
///     while the barber is working, they will sit in an available empty chair until they get their haircut. Otherwise when all
///     chairs are occupied, they leave.
/// @param arg NULL (void* argument needed for thread function)
/// @return NULL
void* customer(void* arg);

/// @brief Runs the sleeping barber problem as a threaded program with barbers and customers.
/// @return 0 if successful, nonzero otherwise
int main();

#endif