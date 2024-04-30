/// File: as7_pc.c
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program implements the producer-consumer problem using semaphores in C.

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

const int producer_num_iterations = 2;
const int num_items_produced = 100;
const int consumer_num_iterations = 3;
const int num_items_consumed = 10;
const int buffer_size = 15000;

/// @brief The sbuf_t data structure encapsulates a buffer of integers. Items can be inserted at the head and
///     removed from the tail. Semaphores protect the shared data and prevent data corruption.
typedef struct {
    int *buf;
    int capacity, head, tail;
    sem_t mutex; // protects buffer while inserting and removing
    sem_t slots; // prevents adding to full buffer when slots = 0
    sem_t items; // 
} sbuf_t;

/// @brief Initializes a sbuf_t object with semaphores, default values, and allocated buffer memory.
/// @param sp uninitialized sbuf_t object
/// @param n number of slots to allocate in the buffer
void sbuf_init(sbuf_t* sp, int n) {
    sp->buf = (int*) calloc(n, sizeof(int));
    sp->capacity = n;
    sp->head = sp->tail = 0;
    sem_init(&sp->mutex, 0, 1);
    sem_init(&sp->slots, 0, n);
    sem_init(&sp->items, 0, 0);
}

/// @brief Deinitializes a sbuf_t object by deallocating buffer memory and destroying semaphores.
/// @param sp sbuf_t object to be destroyed
void sbuf_deinit(sbuf_t *sp) {
    free(sp->buf);
    sem_destroy(&sp->mutex);
    sem_destroy(&sp->slots); 
    sem_destroy(&sp->items); 
}

/// @brief Evaluates the number of slots currently filled. 
/// @param sp sbuf_t object
/// @return number of filled slots in buffer
int sbuf_size(sbuf_t *sp) {
    sem_wait(&sp->mutex); // access buffer after acquiring the lock
    int n = (sp->head + sp->capacity - sp->tail) % sp->capacity;
    sem_post(&sp->mutex);
    return n;
}

/// @brief Inserts a given integer into the buffer array and increments the head index where produced items are written.
/// @param sp sbuf_t object to insert into
/// @param item integer to insert
void sbuf_insert(sbuf_t *sp, int item) {
    sem_wait(&sp->slots); // wait while the buffer is full
    sem_wait(&sp->mutex); // access buffer after acquiring the lock
    sp->head = (sp->head + 1) % sp->capacity;
    sp->buf[sp->head] = item;
    sem_post(&sp->mutex);
    sem_post(&sp->items); // wake up consumer if it is suspended
}

/// @brief Removes an integer from the buffer array and increments the tail index where consumed items are read.
/// @param sp sbuf_t object to remove from
/// @return integer being consumed
int sbuf_remove(sbuf_t *sp) {
    sem_wait(&sp->items); // wait while the buffer is empty
    sem_wait(&sp->mutex); // access buffer after acquiring the lock
    sp->tail= (sp->tail + 1) % sp->capacity;
    int item = sp->buf[sp->tail];
    sem_post(&sp->mutex);
    sem_post(&sp->slots); // wake up producer if it is suspended
    return item;
}

/// @brief Twice inserts numbers 0 to 99 into the head of a buffer and prints their sum. 
/// @param vargp sbuf_t object to insert items into
/// @return NULL
void* producer(void* vargp) {
    sbuf_t *sp = (sbuf_t*)vargp;
    int i, j;
    for(i = 0; i < producer_num_iterations; i++) { //-----------------------------------------------------------
        long s = 0;
        for(j = 0; j < num_items_produced; j++)  //-----------------------------------------------------------
            s += j, sbuf_insert(sp, j);
	    printf("producer: sum: %ld, size: %d\n", s, sbuf_size(sp));  //-----------------------------------------------------------
    }
    pthread_exit(NULL);
}

/// @brief Thrice removes 10 numbers from the tail of the buffer and prints their sum.
/// @param vargp sbuf_t object to consume items from
/// @return NULL
void* consumer(void* vargp) {
    sbuf_t *sp = (sbuf_t*)vargp;
    int i, j;
    for(i = 0; i < consumer_num_iterations; i++) {  //-----------------------------------------------------------
        long s = 0;
        for(j = 0; j < num_items_consumed; j++)  //-----------------------------------------------------------
            s += sbuf_remove(sp);
        printf("consumer: sum: %ld, size: %d\n", s, sbuf_size(sp));  //-----------------------------------------------------------
    }
    pthread_exit(NULL);
}

/// @brief Implements the producer-consumer problem with two separate threads inserting and removing from a shared buffer.
/// @return 0 if successful, nonzero otherwise
int main() {
    pthread_t tid_p, tid_c;
    sbuf_t sb;
    sbuf_init(&sb, buffer_size);

    pthread_create(&tid_p, NULL, producer, &sb);
    pthread_create(&tid_c, NULL, consumer, &sb);

    pthread_join(tid_p, NULL);
    pthread_join(tid_c, NULL);

    sbuf_deinit(&sb);
    return 0;
}
