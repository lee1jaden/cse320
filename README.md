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

This program was completed to practice implementing semaphores in a multithreaded program. Part 1 investigated the 
producer-consumer example and Part 2 investigated the second version of the reader-writer problem.

Part 1:
The first program is a producer-consumer example. Within that, the printing code was corrected to monitor the behavior 
of producers and consumers in the program. There is a discussion below of whether the semaphores work correctly or not.

Part 2:
The second problem is a readers-writers example. There is a collection of concurrent threads that access shared data. 
The reader threads only read the data and write threads only modify the data. Once a writer is ready to write, it performs 
its operation as soon as possible and a reader that arrives after a write must wait, even if the writer is already waiting.

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

# Assumptions
- No two writers can modify the variable at the same time. They may not make their edits in the order they come in, but the shared data should be protected.