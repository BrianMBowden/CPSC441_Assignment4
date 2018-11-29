Brian Bowden || 10060818
CPSC441 || Assignment 4

================
-----README-----
================

Jumping Bozons

Compilation: (makefile provided)
    make (compile)
    make clean (remove all compiled files)
    make run (compile and run program)

Execution: (2 methods)
    //method 1
    ./Bozons [colony-size][avg-sleep-time][avg-yodel-time]

    //method 2
    ./Bozons
        -- note, this method will prompt the user to enter the data, method one is just command line args 

NOTE:
    This assignment contains a way to incorporate the BONUS and DEBUGGING into it, for standard output:
        make __BONUS 0 in the jumpingBozons.h file
        make __DEBUG 0 in the jumpingBozons.h file
        otherwise set these values to 1

    This assignment will also create a new file upon execution, this file is formatted to be incorporated into
    Microsoft Excel or some graphing software. It is for ease of use. 
    (separate files will be created for standard vs BONUS execution)
    This file will either be called "report.txt" or "bonus.txt"

TESTING:
    experiment with colony size, sleep time and yodel time. Values should present a clear trend. Try testing with 
    varied colony size and static sleep and yodel time. ie vary one value and keep the others the same. 
    All this testing is tracked (although I deleted my results often) through the generated text files, and 
    every proceeding test is appended to the existing file.
    Once I was satisfied, I imported the test files into Microsoft Excel, and graphed them. You can refresh the 
    Excel file to bring in any new data.

    All testing was done on my laptop.

REPO:
    https://github.com/BrianMBowden/CPSC441_Assignment4

