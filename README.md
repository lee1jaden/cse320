# Important Contents

- Author:         Jaden Lee
- Partner:        -none-
- Start Date:     30-May-2024
- Course:         CSE 320, State University of New York at Korea, Department of Computer Science
- Professor:      Yoon Seok Yang
- Submit Date:    30-May-2024
- Project:        Assignment 10 - Mastering Advanced C Programing - Shared Library and Dynamic Linking
- Copyright:      Jaden Lee and SUNY Korea - This work may not be copied for use in Academic Coursework or elsewhere.

# Overview of Functionality

This program satisfies the requirements laid forth in the Assignment 10 instructions document linked here: 
    https://drive.google.com/file/d/1XWk5Icf15TaeQRMi4MdJwwh9U2DzGd2H/view

This repository is a program to implement matrix multiplication using shared libraries and dynamic linking functions. Given with the assignment is reference code without dynamic linking functions in nodl.c and compile commands for everything in the Makefile. My code loads and links the shared library within the application.

# Compilation and Execution Instructions

A Makefile is included in the repository to ease compilation. 

1. If the matrix dimensions need to modified, adjust the row and column length macros in the matmul.h file.
2. To generate the shared library, run the following command: make lib
3. To generate an executable without dynamic linking, run the following command: make nodl
4. To generate an executable with dynamic linking, run the following command: make dl
5. Execute the desired binary file with: ./dl or ./nodl
6. To recompile the entire repository, run the following command before re-compiling: make clean

# Assumptions
//todo

# Matrix Format
All matrices are represented as a single line of space-delimited integers in text files. They will be read into the program as matrices in a row-first order in the dimensions listed in the 'matmul.h' macro definitions. Edit that file to change the expected matrix dimensions.