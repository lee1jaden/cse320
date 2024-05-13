/// File: as8.c
/// Assignment 8 - Mastering Advanced C Programing Concepts - Semaphores 2
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: May 13, 2024
/// Description: This program implements the sleeping barber problem in C.

#include "as8.h"
#include "wrappers.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t barber_sem, customer_sem, access_seats_sem, haircut_sem, barber_done_sem;
int num_waiting = 0;

void* barber(void* arg) {
    while (1) {
        SEM_wait(&customer_sem);
        SEM_wait(&access_seats_sem);

        if (num_waiting > 0) {
            num_waiting--;
            printf("Barber: Cutting hair. Customers waiting: %d\n", num_waiting);

            SEM_post(&access_seats_sem);
            SEM_post(&haircut_sem);

            // Simulate haircut
            sleep(1);

            SEM_post(&barber_done_sem);
        } else {
            // If no customers are waiting, release the access_seats_sem
            SEM_post(&access_seats_sem);
        }
    }
}

void* customer(void* arg) {
    SEM_wait(&access_seats_sem);

    if (num_waiting < NUM_CHAIRS) {
        num_waiting++;
        printf("Customer: Arrived. Customers waiting: %d\n", num_waiting);

        SEM_post(&access_seats_sem);
        SEM_post(&customer_sem);

        SEM_wait(&haircut_sem);
        printf("Customer: Got a haircut.\n");

        // Acknowledge that the haircut is done
        SEM_wait(&barber_done_sem);
    } else {
        printf("Customer: No seats available. Leaving.\n");
        SEM_post(&access_seats_sem);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t barber_thread, customer_threads[10];

    SEM_init(&barber_sem, 0, 0);
    SEM_init(&customer_sem, 0, 0);
    SEM_init(&access_seats_sem, 0, 1);
    SEM_init(&haircut_sem, 0, 0);
    SEM_init(&barber_done_sem, 0, 0);

    pthread_create(&barber_thread, NULL, barber, NULL);

    for (int i = 0; i < 10; ++i) {
        pthread_create(&customer_threads[i], NULL, customer, NULL);
        // Sleep to simulate time between customer arrivals
        sleep(1);
    }

    pthread_join(barber_thread, NULL);

    for (int i = 0; i < 10; ++i) {
        pthread_join(customer_threads[i], NULL);
    }

    SEM_destroy(&barber_sem);
    SEM_destroy(&customer_sem);
    SEM_destroy(&access_seats_sem);
    SEM_destroy(&haircut_sem);
    SEM_destroy(&barber_done_sem);

    return 0;
}

