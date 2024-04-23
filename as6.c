/// File: as6.c
/// Assignment 6 - Mastering Advanced C Programing Concepts - Basic Pthread Functions
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 21, 2024
/// Description: This program is an implementation of a word detection program using pthread functions in C.
///     It compares the speed of blocking (join) and non-blocking (detached) threads.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void* word_detect_join(void *vargp);
void* word_detect_detach(void *vargp);

clock_t join_start_time;
clock_t join_end_time;
clock_t detach_start_time;
clock_t detach_end_time;

int main() {
    pthread_t tid = pthread_self();
    printf("main: %u\n", (unsigned int)tid);
    void *ret;

    while(1) {
        char str[100];
        pthread_t tid;
        scanf("%99s", str);
        if(strcmp(str, "quit") == 0)
            break;

        // TODO: Create a peer thread for word_detect_join, detecting a word in the str buffer using pthread_join
        pthread_t joinThread;
        pthread_create(&joinThread, NULL, &word_detect_join, str);
        pthread_join(joinThread, &ret);
        float runtime = *((float*)ret);
        printf("Join thread ran for %.6f seconds.\n", runtime);

        // TODO: Create a peer thread for word_detect_detach, detecting a word in the str buffer using pthread_detach
        // ...
    }
    // TODO: Free the str buffer if you dynamically allocate the string memory
    free(ret);
    return 0;
}

void* word_detect_join(void *vargp) {
    // TODO: Implement a peer thread using pthread_join to detect a word in the argument passed
    // TODO: Print the detected word and frequency if there are multiple detections
    // TODO: Calculate the elapsed execution time in the thread execution using join_start_time and join_end_time 
    // i.e., join_start_time = clock(); <... your thread function>; join_end_time = clock(); 
    float join_execution_time = .5; //join_end_time - join_start_time;
    
    pthread_exit(&join_execution_time);
    return NULL;
}

void* word_detect_detach(void *vargp) {
    // TODO: Implement a peer thread using pthread_detach to detect a word in the argument passed
    // TODO: Print the detected word and frequency if there are multiple detections
    // TODO: Calculate the elapsed execution time in the thread execution using detach_start_time and detach_end_time 
    return NULL;
}

