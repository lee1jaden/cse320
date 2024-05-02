/// File: as7_rw.c
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program implements the second readers-writers problem using semaphores in C.

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
void rwlock_init(rwlock *lock) {
    sem_init(&lock->mutex, 0, 1);
    sem_init(&lock->rlock, 0, 1);
    lock->writecount = 0;
}

/// @brief Destroys the semaphores of a rwlock object
/// @param lock lock to be destructed
void rwlock_deinit(rwlock *lock) {
    sem_destroy(&lock->mutex);
    sem_destroy(&lock->rlock);
}

/// @brief Acquires the lock for a reader to access data once no writes are waiting
/// @param lock rwlock to be acquired
void acquire_reader_lock(rwlock *lock) {
    sem_wait(&lock->rlock); // waits for reader lock to be released
}

/// @brief Releases the lock from a writer for other readers and writers to access
/// @param lock rwlock to be released
void release_reader_lock(rwlock *lock) {
    sem_post(&lock->rlock); // releases the reader lock
}

/// @brief Acquires the lock for a writer as soon as possible but only allows one writer at a time.
/// @param lock rwlock to be acquired
void acquire_writer_lock(rwlock *lock) {
    lock->writecount++;
    if(lock->writecount == 1) // if this is the first writer
        sem_wait(&lock->rlock); // wait for a reader to finish or block readers
    sem_wait(&lock->mutex); // waits for lock on data
}

/// @brief Releases the lock from a writer for other readers and writers to access
/// @param lock rwlock to be released
void release_writer_lock(rwlock *lock) {
    sem_post(&lock->mutex);
    lock->writecount--;
    if(lock->writecount == 0)   //if this is the last reader
        sem_post(&lock->rlock); //unblock any waiting writers
}

/// @brief This thread function reads num_items_read from the object given.
/// @param vargp object to read integer from
/// @return NULL
void* reader(void *vargp) {
    object* pobj = (object*)vargp;
    for(int i = 0; i < num_items_read; i++) {
        acquire_reader_lock(&pobj->lock);
        int data = pobj->data;
        int copy = pobj->copy;
        printf("Read #%d: Data = %d | Copy of Data = %d\n", i+1, data, copy); // Moved this inside the lock for more accurate printing order
        release_reader_lock(&pobj->lock);
    }
}

/// @brief This thread function writes num_items_written into the given object. 
/// @param vargp object to write integer to
/// @return NULL
void* writer(void *vargp) {
    object* pobj = (object*)vargp;
    for(int i = 0; i < num_items_written; i++) {
        acquire_writer_lock(&pobj->lock);
        int data = pobj->data = i;
        int copy = pobj->copy = pobj->data;        
        printf("Write #%d: Data = %d | Copy of Data = %d\n", i+1, data, copy); // Moved this inside the lock for more accurate printing order
        release_writer_lock(&pobj->lock);
    }
}

/// @brief Implements the reader-writer problem with separate threads that read and write data.
/// @return 0 if successful, nonzero otherwise
int main() {
    pthread_t tid[num_reader_threads + num_writer_threads];
    object obj;
    obj.data = obj.copy = 0;
    rwlock_init(&obj.lock);

    int i;
    for (i = 0; i < num_writer_threads; i++) {
        pthread_create(tid+i, 0, writer, &obj);
    }
    for (i = i; i < num_reader_threads + num_writer_threads; i++) {
        pthread_create(tid+i, 0, reader, &obj);
    }
    for (i = 0; i < num_reader_threads + num_writer_threads; i++) {
        pthread_join(tid[i], NULL);
    }

    rwlock_deinit(&obj.lock);
    return 0;
}
