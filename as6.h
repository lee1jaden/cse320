/// File: as6.h
/// Assignment 6 - Mastering Advanced C Programing Concepts - Basic Pthread Functions
/// Author: Jaden Lee
/// Course: CSE 320
/// Professor: Yoon Seok Yang
/// Date: April 21, 2024
/// Description: This program is an implementation of a word detection program using pthread functions in C.
///     It compares the speed of blocking (join) and non-blocking (detached) threads.

#ifndef AS6_H
#define AS6_H

#include <time.h>

/// @brief Repeatedly prompts the user to enter a line of text and a word to detect from it. Prints how often the
///     target word appears and prints the running times of various thread executions for each iteration.
/// @return 0 if successful, nonzero otherwise
int main();

/// @brief Prints the detected word and frequency if there are multiple detections, then calculates the elapsed 
///     execution time of the joined thread execution.
/// @param vargp array with two elements: (1) string of text to search through, (2) word to search for
/// @return pointer to frequency count (memory must be freed)
void* word_detect_join(void *vargp);

/// @brief Prints the detected word and frequency if there are multiple detections, then calculates the elapsed 
///     execution time of the detached thread execution.
/// @param vargp array with two elements: (1) string of text to search through, (2) word to search for
/// @return NULL
void* word_detect_detach(void *vargp);

/// @brief Prints the frequency of a given word based on the parameters.
/// @param word word that was attempted to be detected
/// @param frequency number of times that word occurred in the string
void printFrequency(char *word, int frequency);

/// @brief Prints how long a given thread took to run given the start and end times in clocks.
/// @param threadName string to identify the thread
/// @param start start time of execution
/// @param end end time of execution
void printElapsedTime(char *threadName, clock_t start, clock_t end);

#endif