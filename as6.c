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

const int max_string_length = 100;

void* word_detect_join(void *vargp);
void* word_detect_detach(void *vargp);
void printFrequency(char *word, int frequency);
void printElapsedTime(char *threadName, clock_t start, clock_t end);

clock_t join_start_time;
clock_t join_end_time;
clock_t detach_start_time;
clock_t detach_end_time;

int main() {
    pthread_t tid = pthread_self();
    printf("Main Thread ID: %u\n", (unsigned int)tid);
    char text_string[max_string_length + 2];
    char target_word[max_string_length + 2];

    while(1) {
        // Prompt user to enter text. Check if the string is too long or contains 'quit'.
        printf("Enter some text or quit: ");
        fgets(text_string, max_string_length + 2, stdin);
        if (strlen(text_string) > max_string_length && text_string[strlen(text_string) - 1] != '\n') {
            printf("Error: Text string was longer than 100 characters long. Now exiting.\n");
            exit(EXIT_FAILURE);
        }
        text_string[strlen(text_string) - 1] = 0;
        if(strcmp(text_string, "quit") == 0)
            break;

        // printf("String '%s' is length %d\n", text_string, (int)strlen(text_string)); //DEBUG

        // Prompt user to enter the word to search for. Check if the string is too long or has multiple words.
        printf("Enter a word you'd like to detect: ");
        fgets(target_word, max_string_length + 2, stdin);
        if (strlen(target_word) > max_string_length && target_word[strlen(target_word) - 1] != '\n') {
            printf("Error: Word was longer than 100 characters long. Now exiting.\n");
            exit(EXIT_FAILURE);
        }
        target_word[strlen(target_word) - 1] = 0;
        // printf("String '%s' is length %d\n", target_word, (int)strlen(target_word)); //DEBUG
        if (strchr(target_word, ' ') != NULL) {
            printf("Error: Submitted more than one word. Now exiting.\n");
            exit(EXIT_FAILURE);
        }

        // Set up array of arguments to pass to thread functions.
        char *args[2] = {text_string, target_word};

        // Create a peer thread for word_detect_join, detecting a word in the str buffer using pthread_join
        pthread_t join_tid;
        void* frequencyPtr;
        join_start_time = clock();
        if (pthread_create(&join_tid, NULL, &word_detect_join, args) != 0) {
            printf("Error: Join thread creation failed. Now exiting.\n");
            exit(EXIT_FAILURE);
        }
        if (pthread_join(join_tid, &frequencyPtr) != 0) {
            printf("Error: Join thread reaping failed. Now exiting.\n");
            exit(EXIT_FAILURE);
        }
        join_end_time = clock();
        printFrequency(target_word, *(int*)frequencyPtr);
        printElapsedTime("joined thread", join_start_time, join_end_time);
        free(frequencyPtr);


        // TODO: Create a peer thread for word_detect_detach, detecting a word in the str buffer using pthread_detach
        // ...
    }
    // TODO: Free the str buffer if you dynamically allocate the string memory

    return 0;
}

/// @brief 
/// @param vargp - text string to search through.
/// @return NULL
void* word_detect_join(void *vargp) {
    char **args = (char**)vargp;
    char *sentence = args[0];
    char *search_word = args[1];
    // printf("Trying to detect '%s' from '%s'?\n", word, sentence); //DEBUG

    int *frequencyPtr = malloc(sizeof(int));
    *frequencyPtr = 0;
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        if (strcmp(token, search_word) == 0)
            (*frequencyPtr)++;
        token = strtok(NULL, " ");
    }


    pthread_exit(frequencyPtr);

    // TODO: Implement a peer thread using pthread_join to detect a word in the argument passed
    // TODO: Print the detected word and frequency if there are multiple detections
    // TODO: Calculate the elapsed execution time in the thread execution using join_start_time and join_end_time 
    // i.e., join_start_time = clock(); <... your thread function>; join_end_time = clock(); 
    //float join_execution_time = join_end_time - join_start_time;
    return NULL;
}

void* word_detect_detach(void *vargp) {
    // TODO: Implement a peer thread using pthread_detach to detect a word in the argument passed
    // TODO: Print the detected word and frequency if there are multiple detections
    // TODO: Calculate the elapsed execution time in the thread execution using detach_start_time and detach_end_time 
    return NULL;
}

void printFrequency(char *word, int frequency) {
    printf("'%s' was detected %d %s.\n", word, frequency, frequency == 1 ? "time" : "times");
}

void printElapsedTime(char *threadName, clock_t start, clock_t end) {
    double secondsElapsed = (double)(join_end_time - join_start_time) / CLOCKS_PER_SEC;
    printf("The %s took %.6f seconds to complete.\n", threadName, secondsElapsed);
}