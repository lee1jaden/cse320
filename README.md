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


# Assumptions
- 