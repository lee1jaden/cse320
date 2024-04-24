# Important Contents

Author:         Jaden Lee
Partner:        -none-
Start Date:     21-Apr-2024
Course:         CSE 320, State University of New York at Korea, Department of Computer Science
Professor:      Yoon Seok Yang
Submit Date:    25-Apr-2024
Project:        Assignment 6 - Mastering Advanced C Programing Concepts - Basic Pthread Functions
Copyright:      Jaden Lee and SUNY Korea - This work may not be copied for use in Academic Coursework or elsewhere.

# Overview of Functionality

This program satisfies the requirements laid forth in the Assignment 6 instructions document linked here: 
    https://drive.google.com/file/d/1YujyQYkKsr6pbByw9DyPuMfR5Ad7iuLo/view

The program is an implementation of a word detection program using pthread functions. It prompts users to enter a
text string up to 100 characters and a word to search for in that string. The program will determine how often the 
string occurs first with a join thread and then with a detached thread. Each thread will output its execution time. 
This process will be iterated until the user quits the program by entering 'quit'.

# Compilation and Execution Instructions

A Makefile is included in the repository. Run the following command to compile:
    make as6
Then execute the binary file with:
    ./as6
If you desire to recompile the entire repository, first run this before compiling again:
    make clean

# Assumptions

- The execution time for the joined thread should not include the time spent returning control to the main function. The extra lines of code required would alter the results and make the joined and detached threads incomparable. Calculating the execution time of the detached thread would be impossible from the main method because it is non-blocking.
- The order of successive iterations should always be preserved. This is why there is a 2 second sleep period after beginning the detached thread. The thread should be able to finish in this time, but the non-blocking characteristic of it should be acknowledged.
- Formerly global variables could be moved to a smaller scope and passed as parameters. 