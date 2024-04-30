# Important Contents

- Author:         Jaden Lee
- Partner:        -none-
- Start Date:     26-Apr-2024
- Course:         CSE 320, State University of New York at Korea, Department of Computer Science
- Professor:      Yoon Seok Yang
- Submit Date:    02-May-2024
- Project:        Assignment 7 - Mastering Advanced C Programing Concepts - Semaphores
- Copyright:      Jaden Lee and SUNY Korea - This work may not be copied for use in Academic Coursework or elsewhere.

# Overview of Functionality

This program satisfies the requirements laid forth in the Assignment 7 instructions document linked here: 
    https://drive.google.com/file/d/1jpiVjaX6MhK2VD9ZSvKuPv3cWqp4f8Do/view

This program was completed to practice implementing semaphores in a multithreaded program. The first program
is a producer-consumer example. Within that, the printing code was corrected to monitor the behavior of producers 
and consumers in the program. There is a discussion below of whether the semaphores work correctly or not.

# Compilation and Execution Instructions

A Makefile is included in the repository to ease compilation. 

1. To compile the producer-consumer program, run the following command: 
    make as7_pc
2. Then execute the binary file with: 
    ./as7_pc
3. To compile the reader-writer program, run the following command: 
    make as7_rw
4. Then execute the binary file with: 
    ./as7_rw

To recompile the entire repository, first run the following command before compiling: 
    make clean

# Producer-Consumer Example Semaphore Analysis

Upon inspecting results of the printed code, it appears the semaphores work properly. Orderings of the producer and consumer result print statements vary on each execution, but that is due to unpredictable thread ordering in each execution by the operating system. Similarly, the outputed buffer sizes can vary because the point at which the consumers acquire the lock from a producer varies on each execution. As long as the sums are correct, then the semaphores should be working properly. That indicates that the shared data remains uncorrupted, no data is overwritten or skipped, and the code is free of synchronization errors.

# Assumptions
- 