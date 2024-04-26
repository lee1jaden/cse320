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

typedef struct {
    sem_t mutex;
    sem_t wlock;
    int readcount;
} rwlock;

typedef struct {
    int data;
    int copy;
    rwlock lock;
} object;

void rwlock_init(rwlock *lock) {
    sem_init(&lock->mutex, 0, 1);
    sem_init(&lock->wlock, 0, 1);
    lock->readcount = 0;
}

void rwlock_deinit(rwlock *lock) {
    sem_destroy(&lock->mutex);
    sem_destroy(&lock->wlock);
}

void acquire_reader_lock(rwlock *lock) {
    sem_wait(&lock->mutex);
    lock->readcount++;
    if(lock->readcount == 1) //if this is the first reader
        sem_wait(&lock->wlock);//wait for a writer to finish or block writers
    sem_post(&lock->mutex);
}

void release_reader_lock(rwlock *lock) {
    sem_wait(&lock->mutex);
    lock->readcount--;
    if(lock->readcount == 0)   //if this is the last reader
        sem_post(&lock->wlock);//unblock any waiting writers
    sem_post(&lock->mutex);
}

void acquire_writer_lock(rwlock *lock) {
    sem_wait(&lock->wlock);
}

void release_writer_lock(rwlock *lock) {
    sem_post(&lock->wlock);
}

void* reader(void *vargp) {
    object* pobj = (object*)vargp;
    int i;
    for(i = 0; i < 100; i++) {
        acquire_reader_lock(&pobj->lock);
        int data = pobj->data;
        int copy = pobj->copy;
        release_reader_lock(&pobj->lock);
        printf("R_%d: data: %d, copy: %d\n", i, data, copy);
    }
}

void* writer(void *vargp) {
    object* pobj = (object*)vargp;
    int i;
    for(i = 0; i < 100; i++) {
        acquire_writer_lock(&pobj->lock);
        int data = pobj->data = i % 10;
        int copy = pobj->copy = pobj->data;
        release_writer_lock(&pobj->lock);
        printf("W_%d: data: %d, copy: %d\n", i, data, copy);
    }
}

int main() {
    pthread_t tid[3];
    object obj;
    obj.data = obj.copy = 0;
    rwlock_init(&obj.lock);

    pthread_create(tid+0, 0, reader, &obj);
    pthread_create(tid+1, 0, reader, &obj);
    pthread_create(tid+2, 0, writer, &obj);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    rwlock_deinit(&obj.lock);
}
