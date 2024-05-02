/// File: as7_pc.c
/// Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 26, 2024
/// Description: This program implements the producer-consumer problem using semaphores in C.

#include "as7_pc.h"
#include "wrappers.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

void sbuf_init(sbuf_t* sp, int n) {
    sp->buf = (int*) calloc(n, sizeof(int));
    sp->capacity = n;
    sp->head = sp->tail = 0;
    SEM_init(&sp->mutex, 0, 1);
    SEM_init(&sp->slots, 0, n);
    SEM_init(&sp->items, 0, 0);
}

void sbuf_deinit(sbuf_t *sp) {
    free(sp->buf);
    SEM_destroy(&sp->mutex);
    SEM_destroy(&sp->slots); 
    SEM_destroy(&sp->items); 
}

int sbuf_size(sbuf_t *sp) {
    SEM_wait(&sp->mutex); // access buffer after acquiring the lock
    int n = (sp->head + sp->capacity - sp->tail) % sp->capacity;
    SEM_post(&sp->mutex); // release the lock
    return n;
}

void sbuf_insert(sbuf_t *sp, int item) {
    SEM_wait(&sp->slots); // wait while the buffer is full
    SEM_wait(&sp->mutex); // access buffer after acquiring the lock
    sp->head = (sp->head + 1) % sp->capacity;
    sp->buf[sp->head] = item;
    SEM_post(&sp->mutex); // release the lock
    SEM_post(&sp->items); // wake up consumer if it is suspended
}

int sbuf_remove(sbuf_t *sp) {
    SEM_wait(&sp->items); // wait while the buffer is empty
    SEM_wait(&sp->mutex); // access buffer after acquiring the lock
    sp->tail= (sp->tail + 1) % sp->capacity;
    int item = sp->buf[sp->tail];
    SEM_post(&sp->mutex); // release the lock
    SEM_post(&sp->slots); // wake up producer if it is suspended
    return item;
}

void* producer(void* vargp) {
    sbuf_t *sp = (sbuf_t*)vargp;
    int i, j;
    for(i = 0; i < producer_num_iterations; i++) { 
        long s = 0;
        for(j = 0; j < num_items_produced; j++) 
            s += j, sbuf_insert(sp, j);
	    printf("Producer #%d: Sum of inserted numbers = %ld | Current Buffer Size = %d\n", i+1, s, sbuf_size(sp)); 
    }
    pthread_exit(NULL);
}

void* consumer(void* vargp) {
    sbuf_t *sp = (sbuf_t*)vargp;
    int i, j;
    for(i = 0; i < consumer_num_iterations; i++) {  
        long s = 0;
        for(j = 0; j < num_items_consumed; j++)  
            s += sbuf_remove(sp);
        printf("Consumer #%d: Sum of removed numbers = %ld | Current Buffer Size = %d\n", i+1, s, sbuf_size(sp)); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid_p, tid_c;
    sbuf_t sb;
    sbuf_init(&sb, buffer_size);

    printf("Each producer will insert %d numbers.\n", num_items_produced);
    printf("Each consumer will remove %d numbers.\n", num_items_consumed);
    pthread_create(&tid_p, NULL, producer, &sb);
    pthread_create(&tid_c, NULL, consumer, &sb);

    pthread_join(tid_p, NULL);
    pthread_join(tid_c, NULL);

    sbuf_deinit(&sb);
    return 0;
}
