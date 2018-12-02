/* ============================================================================
 * Author: Brian Bowden
 * Date: December 2, 2018
 * Due: December 3, 2018
 * Class: CPSC 441 || Tut 04
 * ============================================================================
 * numberGen.c
 * ============================================================================
 * Library for computing "random" exponential numbers
 * 
 * ============================================================================
 * Bugs: No known bugs
 * 
 * Testing: Testing done on my laptop (for working state)
 *          
 * Notes: user can use the seeded random number via a change in the associated .h file
 *        Most of this was provided through the University of Calgary Computer Science
 *        Department: CPSC 441 - Computer Networks class for use during an assignment
 * 
 * ============================================================================
 * */
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "numberGen.h"

double uniform01(){

    double randnum;

    randnum = (double) 1.0 * random();
    randnum /= (1.0 * MAX_INT);
    return (randnum);
}

double seedUniform01(){

    double randnum;
    srandom(time(NULL));
    randnum = (double) 1.0 * random();
    randnum /= (1.0 * MAX_INT);
    return randnum;
}

double Exponential(double mu){
    
    double randnum;
    double answer;

#if __SEED
    randnum = seedUniform01();
#else 
    randnum = uniform01();
#endif

    answer = -(mu) * log(randnum);
    return answer;
}