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

sem_t customer_sem; // Indicates how many customers are waiting for a haircut.
sem_t waiting_room_mutex; // Controls access to seats in waiting room so only one thread accesses it at a time.
sem_t barber_room_mutex; // Controls access to the seat in the barber room so only one customer can be inside at a time.
sem_t barber_start_sem; // Controls access to the barber's chair so only one waiting customer can sit down.
sem_t barber_done_sem; // Alerts the customer when the haircut is complete.
sem_t customer_left_sem; 
int num_customers_waiting = 0; 
int haircut_in_progress = 0;

void* barber(void* arg) {
    while (1) {
        // Check waiting room for customers and fall asleep if none are waiting
        SEM_wait(&waiting_room_mutex); 
        if (num_customers_waiting == 0) {
            printf("Barber     >>> No customers present. Falling asleep in my chair.\n");
        }
        SEM_post(&waiting_room_mutex);

        // Wait until a customer arrives
        SEM_wait(&customer_sem);

        // Accept a customer into the barber shop
        SEM_wait(&waiting_room_mutex);
        if (num_customers_waiting == 0) {
            // Customer found barber asleep
            printf("Barber     >>> New customer entered and woke me up.\n");
        }
        else {
            // Select a new customer from the waiting room
            num_customers_waiting--; 
            printf("Barber     >>> New customer has entered. The number of customers remaining is %d.\n", num_customers_waiting);
        }
        SEM_post(&waiting_room_mutex); // release mutex for waiting room

        // Signal that the haircut has begun
        haircut_in_progress = 1;
        SEM_post(&barber_start_sem);
        // Simulate haircut
        sleep(HAIRCUT_TIME);
        // Signal that the haircut has ended
        SEM_post(&barber_done_sem);
        // Wait for the customer to leave
        SEM_wait(&customer_left_sem);
    }
}

void* customer(void* arg) {
    static int customer_count = 0;
    int id = ++customer_count;

    SEM_wait(&waiting_room_mutex);
    if (num_customers_waiting < NUM_CHAIRS) {
        num_customers_waiting++;
        if (num_customers_waiting == 1 && !haircut_in_progress) { // must account that barber is not working
            // Wake the barber if they are asleep.
            printf("Customer %d >>> Barber is asleep. Waking them up. \n", id);
        }
        else {
            // Enter the waiting room if barber is working.
            printf("Customer %d >>> Now that I arrived, the number of customers waiting is %d.\n", id, num_customers_waiting);
        }
        SEM_post(&waiting_room_mutex);
        SEM_post(&customer_sem); // increment amount of customers waiting

        // One customer enters the barber shop
        SEM_wait(&barber_room_mutex);   
        // Acknowledge that haircut has begun
        SEM_wait(&barber_start_sem);
        printf("Customer %d >>> Haircut has begun.\n", id);
        // Acknowledge that the haircut is done
        SEM_wait(&barber_done_sem);
        printf("Customer %d >>> Haircut is complete. Now leaving.\n", id);
        // Customer leaves the barber shop
        SEM_post(&customer_left_sem);
        SEM_post(&barber_room_mutex);
        haircut_in_progress = 0;
    } 
    else {
        printf("Customer %d >>> No seats are available. Now leaving.\n", id);
        SEM_post(&waiting_room_mutex); // release mutex for waiting room
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t barber_thread, customer_threads[NUM_CUSTOMERS];

    SEM_init(&barber_room_mutex, 0, 1);
    SEM_init(&customer_sem, 0, 0);
    SEM_init(&waiting_room_mutex, 0, 1);
    SEM_init(&barber_start_sem, 0, 0);
    SEM_init(&barber_done_sem, 0, 0);
    SEM_init(&customer_left_sem, 0, 0);

    pthread_create(&barber_thread, NULL, barber, NULL);
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        int id = i + 1;
        // Sleep to simulate time between customer arrivals
        sleep(CUSTOMER_INTERVAL);
        pthread_create(&customer_threads[i], NULL, customer, NULL);
    }

    pthread_join(barber_thread, NULL);
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    SEM_destroy(&barber_room_mutex);
    SEM_destroy(&customer_sem);
    SEM_destroy(&waiting_room_mutex);
    SEM_destroy(&barber_start_sem);
    SEM_destroy(&barber_done_sem);
    SEM_destroy(&customer_left_sem);

    return 0;
}

