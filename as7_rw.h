/// File: as7_rw.h
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program declares the second readers-writers problem using semaphores in C.

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

const int num_reader_threads = 6;
const int num_items_read = 5;
const int num_writer_threads = 3;
const int num_items_written = 10;

/// @brief This lock controls access to object struct to prevent synchronization errors and favor writers.
typedef struct {
    sem_t mutex;
    sem_t rlock; //
    int writecount;
} rwlock;

/// @brief Represents an object that can be written to and read from. Contains a lock struct to protect the data.
typedef struct {
    int data;
    int copy;
    rwlock lock;
} object;

/// @brief Initializes the semaphores and writer counter for a rwlock object
/// @param lock lock to be initialized
void rwlock_init(rwlock *lock);

/// @brief Destroys the semaphores of a rwlock object
/// @param lock lock to be destructed
void rwlock_deinit(rwlock *lock);

/// @brief Acquires the lock for a reader to access data once no writes are waiting
/// @param lock rwlock to be acquired
void acquire_reader_lock(rwlock *lock);

/// @brief Releases the lock from a writer for other readers and writers to access
/// @param lock rwlock to be released
void release_reader_lock(rwlock *lock);

/// @brief Acquires the lock for a writer as soon as possible but only allows one writer at a time.
/// @param lock rwlock to be acquired
void acquire_writer_lock(rwlock *lock);

/// @brief Releases the lock from a writer for other readers and writers to access
/// @param lock rwlock to be released
void release_writer_lock(rwlock *lock);

/// @brief This thread function reads num_items_read from the object given.
/// @param vargp object to read integer from
/// @return NULL
void* reader(void *vargp);

/// @brief This thread function writes num_items_written into the given object. 
/// @param vargp object to write integer to
/// @return NULL
void* writer(void *vargp);

/// @brief Implements the reader-writer problem with separate threads that read and write data.
/// @return 0 if successful, nonzero otherwise
int main();
