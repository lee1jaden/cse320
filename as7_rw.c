/// File: as7_rw.c
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program implements the second readers-writers problem using semaphores in C.

#include "as7_rw.h"
#include "wrappers.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

void rwlock_init(rwlock *lock) {
    sem_init(&lock->mutex, 0, 1);
    sem_init(&lock->rlock, 0, 1);
    lock->writecount = 0;
}

void rwlock_deinit(rwlock *lock) {
    sem_destroy(&lock->mutex);
    sem_destroy(&lock->rlock);
}

void acquire_reader_lock(rwlock *lock) {
    sem_wait(&lock->rlock); // waits for reader lock to be released
}

void release_reader_lock(rwlock *lock) {
    sem_post(&lock->rlock); // releases the reader lock
}

void acquire_writer_lock(rwlock *lock) {
    lock->writecount++;
    if(lock->writecount == 1) // if this is the first writer
        sem_wait(&lock->rlock); // wait for a reader to finish or block readers
    sem_wait(&lock->mutex); // waits for lock on data
}

void release_writer_lock(rwlock *lock) {
    sem_post(&lock->mutex);
    lock->writecount--;
    if(lock->writecount == 0)   //if this is the last reader
        sem_post(&lock->rlock); //unblock any waiting writers
}

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
