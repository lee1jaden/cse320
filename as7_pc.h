/// File: as7_pc.h
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program declares the producer-consumer problem using semaphores in C.

#include "wrappers.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

const int producer_num_iterations = 2;
const int num_items_produced = 100;
const int consumer_num_iterations = 20;
const int num_items_consumed = 10;
const int buffer_size = 120;

/// @brief The sbuf_t data structure encapsulates a buffer of integers. Items can be inserted at the head and
///     removed from the tail. Semaphores protect the shared data and prevent data corruption.
typedef struct {
    int *buf;
    int capacity, head, tail;
    sem_t mutex; // binary semaphore - protects buffer while inserting and removing
    sem_t slots; // counting semaphore - prevents adding to full buffer when slots = 0
    sem_t items; // counting semaphore - prevents consuming from empty buffer when items = 0
} sbuf_t;

/// @brief Initializes a sbuf_t object with semaphores, default values, and allocated buffer memory.
/// @param sp uninitialized sbuf_t object
/// @param n number of slots to allocate in the buffer
void sbuf_init(sbuf_t* sp, int n);

/// @brief Deinitializes a sbuf_t object by deallocating buffer memory and destroying semaphores.
/// @param sp sbuf_t object to be destroyed
void sbuf_deinit(sbuf_t *sp);

/// @brief Evaluates the number of slots currently filled. 
/// @param sp sbuf_t object
/// @return number of filled slots in buffer
int sbuf_size(sbuf_t *sp);

/// @brief Inserts a given integer into the buffer array and increments the head index where produced items are written.
/// @param sp sbuf_t object to insert into
/// @param item integer to insert
void sbuf_insert(sbuf_t *sp, int item);

/// @brief Removes an integer from the buffer array and increments the tail index where consumed items are read.
/// @param sp sbuf_t object to remove from
/// @return integer being consumed
int sbuf_remove(sbuf_t *sp);

/// @brief Inserts the numbers 0 to num_items_produced in producer_num_iterations times into the head of a buffer and prints their sum. 
/// @param vargp sbuf_t object to insert items into
/// @return NULL
void* producer(void* vargp);

/// @brief Removes num_items_consumed numbers a total of consumer_num_iterations times from the tail of the buffer and prints their sum.
/// @param vargp sbuf_t object to consume items from
/// @return NULL
void* consumer(void* vargp);

/// @brief Implements the producer-consumer problem with two separate threads inserting and removing from a shared buffer.
/// @return 0 if successful, nonzero otherwise
int main();
