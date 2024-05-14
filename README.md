# Important Contents

- Author:         Jaden Lee
- Partner:        -none-
- Start Date:     13-May-2024
- Course:         CSE 320, State University of New York at Korea, Department of Computer Science
- Professor:      Yoon Seok Yang
- Submit Date:    14-May-2024
- Project:        Assignment 8 - Mastering Advanced C Programing Concepts - Semaphores 2
- Copyright:      Jaden Lee and SUNY Korea - This work may not be copied for use in Academic Coursework or elsewhere.

# Overview of Functionality

This program satisfies the requirements laid forth in the Assignment 8 instructions document linked here: 
    https://drive.google.com/file/d/1YJUCUvYK9IiG4YjkhcYFWgecUoiTKc93/view

The main goal of the program is to solve the sleeping barber problem using semaphores. The problem is a well-known challenge highlighting the complexities of inter-process communication, synchronization, and potential redundancy of semaphores. 

The scenario involves a hypothetical barbershop with one barber, a single barber chair, and a waiting room containing n chairs (where n may be 0) for waiting customers. If no customers are present, the barber falls asleep in the chair. A customer must wake the barber if they find him asleep. If a customer arrives while the barber is working, the customer leaves if all chairs are occupied; otherwise, they sit in an empty chair if available. When the barber completes a haircut, they check the waiting room for any waiting customers and fall asleep if none are found.

# Compilation and Execution Instructions

A Makefile is included in the repository to ease compilation. 

1. To compile the producer-consumer program, run the following command: make as8
2. Then execute the binary file with: ./as8 (Note: the barber will continue sleeping indefinitely once the customers leave. Exit the program with Ctrl-C)
3. To recompile the entire repository, first run the following command before compiling: make clean

# Assumptions
- In testing, no starvation has occurred. Therefore, no queue is needed at the present moment to ensure no customers are left waiting.