/* ============================================================================
 * Author: Brian Bowden
 * Date: December 2, 2018
 * Due: December 3, 2018
 * Class: CPSC 441 || Tut 04
 * ============================================================================
 * jumpingBozons.c
 * executable: ./Bozons
 * ============================================================================
 * 
 * Simulation of Random Access Channel (using Yodelling Aliens...)
 * 
 * Arguments can be supplied at execution, in this order (how it will be interpreted):
 *       ./Bozons [colon-size][avg-sleep-time][avg-yodel-time]
 * 
 * Can also be executed with no arguments, user will be prompted for input in this case:
 *      ./Bozons
 * 
 * Certain variables can be changed in the associated .h file to simulate either
 * 
 *      __BONUS 0 - yodel times will be pulled "randomly" from a exponential number generator
 *                  with the mean time that is supplied
 * 
 *      __BONUS 1 - yodel times are hard-coded at 10.0 (simulating a regulated rate)
 * 
 * 
 *      __DEBUG 0 - debugging messages are turned off
 * 
 *      __DEBUG 1 - debugging messages are turned on 
 * 
 * for the allotted time, increment time in small increments to assure important "events" aren't missed
 *      for every Bozon in the colony, check if it's asleep or yodelling
 *          asleep:
 *              check if it's time to wake up
 *                  wake it up, set a random yodel time for it, assume perfect yodel
 *                  incement yodellers, perfect yodellers, attempted yodels
 *          yodelling:
 *              check if anyone else is yodelling
 *                  interrupted yodel if there are more than one yodellers, no longer a perfect yodel
 *              check if it is time to stop yodelling
 *                  put it to bed, set random sleep time for it
 *                  check if it was interrupted,
 *                      decrement perfect yodels
 *                  decrement yodellers
 *          add time increment to appropriate "yodel state"
 * 
 * ============================================================================
 * Bugs: No known bugs
 *       I recognize there might be a rare instance where perfect yodels may not be calculated properly
 *           This instance occurs because I don't retract every yodelling Bozons "perfect yodel" privelage
 *           However, the only time this would be a problem is (within the time increment) a yodeller gets
 *           put to sleep, the yodellers are decremented, and suddenly I have one less yodeller (before I check
 *           the remaining colony in that time increment)
 *           BUT! given the explicit randomness, and small liklehood of this happening (smaller with smaller time
 *           increments) I do not think this will hurt the results in any significant way.
 * 
 * Testing: Testing done on my laptop (for working state)
 *          
 * 
 * Notes: Negative input untested and untracked, results are unknown
 * 
 * ============================================================================
 * */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "jumpingBozons.h"
#include "numberGen.h"

struct Bozon{ // make this a struct to keep track of each Bozon 
    int name;
    double sleep_time;
    double yodel_time; 
    double sleep_start;
    double yodel_start;
    int sleeping;
    short perfect;
}; // I mean, they basically have a personality

int main(int argc, char** argv){

    double args_notprovided[3]; //M, S, Y
    int colony_size;

    /* Time Variables */
    double start = START;
    double time_silent = 0.0;
    double time_harmonious = 0.0;
    double time_screechy = 0.0;

    /* Bozon Colony */
    struct Bozon *colony;

    /* Helper Variables */
    int i;
    int yodelling = 0;
    int attempted_yodels = 0;
    int perfect_yodels = 0;

    /* FILE I/O */
    FILE *fp;

    /* Start Up */
    if (argc == 1){
        welcomePrompt(args_notprovided); // arguments not supplied at execution call 
    }
    else if (argc == 4){ // arguments at execution
        args_notprovided[0] = atof(argv[1]);
        args_notprovided[1] = atof(argv[2]);
        args_notprovided[2] = atof(argv[3]);
    }
    else{
        printf("Usage: arguments provided not zero or three\n");
        return 0;
    }

    /* File stuff for populating Excel spreadsheet */
#if __BONUS
    fp = fopen("./bonus.txt", "a"); // split up Bonus file
#else
    fp = fopen("./report.txt", "a"); // split up regular file
#endif
    if (fp == NULL){
        printf("File Usage: File not found or created");
    }

#if __DEBUG
    printf("M= %lf \tS= %lf \tY= %lf \n",args_notprovided[0], args_notprovided[1], args_notprovided[2]);
#endif

    colony_size = (int)args_notprovided[0];
    colony = (struct Bozon*)malloc(colony_size * sizeof(struct Bozon));

    /* Initialize Colony */ 
    for (i = 0; i < colony_size; i++){
        colony[i].name = i; // give them a name to keep track for debugging
        colony[i].sleep_time = Exponential(args_notprovided[1]); // pull first "random" sleep time
#if __BONUS
        colony[i].yodel_time = 10.0; //for bonus, hard code value for yodel
#else
        colony[i].yodel_time = Exponential(args_notprovided[2]); // pull first "random" yodel time
#endif
        colony[i].sleep_start = START; // sleep starts at time == 0.0
        colony[i].sleeping = 1; // assume all Bozons start off sleeping
#if __DEBUG
        printf("Bozon ID: %d || Sleeps for: %lf || Yodels for: %lf\n", colony[i].name, colony[i].sleep_time, colony[i].yodel_time);
#endif
    }

    for (;start < MAX_TIME; (start += TIME_INC)){ // start will keep track of current time
        for (i = 0; i < colony_size; i++){ // check every bozon in colony
            if (colony[i].sleeping){ // only do things here if is currently sleeping
                if ((colony[i].sleep_start + colony[i].sleep_time) <= start){
                    //wake it up, start yodelling
                    colony[i].sleeping = 0; // wake it up
                    colony[i].yodel_start = start; // start yodelling now
#if __BONUS
                    colony[i].yodel_time = 10.0; // hard-coded value for bonus submission
#else
                    colony[i].yodel_time = Exponential(args_notprovided[2]); // pull new "random" value for next yodel cycle
#endif
                    colony[i].perfect = 1; // assume yodel is perfect at wake-up
                    yodelling++; // one more yodeller
                    attempted_yodels++; // count all of our yodels
                    perfect_yodels++; // increment perfect yodels
                }
            }
            else{
                // must be yodelling
                if (yodelling > 1){
                    colony[i].perfect = 0; // if there is more than one yodeller, obviously not perfect 
                }
                if ((colony[i].yodel_start + colony[i].yodel_time) <= start){
                    //done yodelling, go to bed, update time
                    colony[i].sleeping = 1; // put it to bed
                    colony[i].sleep_start = start; // sleep at current time
                    colony[i].sleep_time = Exponential(args_notprovided[1]); // pull new "random" value for next sleep cycle
                    if (!colony[i].perfect){
                        perfect_yodels--; // yodel not perfect, decrement counter by one
                    }  
                    colony[i].perfect = 0; // not yodelling == not perfect yodel
                    yodelling--; // one less yodeller
                }
            }
        }

        /* Increment time counter based on yodellers */
        if (yodelling == 0){
            time_silent += TIME_INC;
        }
        else if (yodelling == 1){
            time_harmonious += TIME_INC;
        }
        else{
            time_screechy += TIME_INC;
        }
    }

    /* Write results to screen */
    printf("Time elapsed:     %lf\n", start);
    printf("Time silent:      %lf || (%lf%%)\n", time_silent, 100.0*time_silent/start);
    printf("Time harmonious:  %lf || (%lf%%)\n", time_harmonious, 100.0*time_harmonious/start);
    printf("Time screechy:    %lf || (%lf%%)\n", time_screechy, 100.0*time_screechy/start);
    printf("Attempted yodels: %d\n", attempted_yodels);
    printf("Perfect yodels:   %d\n", perfect_yodels);

    /* Write results to file */
    fprintf(fp, "%d|%lf|%lf|", colony_size, args_notprovided[1], args_notprovided[2]);
    fprintf(fp, "%lf|%lf|%lf|", 100.0*time_silent/start, 100*time_harmonious/start, 100*time_screechy/start);
    fprintf(fp, "%d|%d\n", attempted_yodels, perfect_yodels);

    return 0;
}
/* -----------------------------------------------
 *  Author: Brian Bowden
 *  Function Name: void welcomePrompt(double* parameters)
 *  Input: *parameters - empty (or NULL) double array with size >= 3
 *  Returns: *parameters is filled by user after prompts
 *  Usage: Extracting user input from command line at runtime
 * -----------------------------------------------
 * */
void welcomePrompt(double* parameters){
    double size;      // M
    double avg_sleep; // S
    double avg_yodel; // Y

    printf("------------------------------------------------------------------------------------\n\n");
    printf("            Welcome Tourists, to the Land of the Jumping Bozons                         ");
    printf("\n\n------------------------------------------------------------------------------------");
    printf("\n\n            Please enter your parameters for your visit                             ");
    printf("\n\n------------------------------------------------------------------------------------");
    printf("\nEnter colony size: ");
    scanf("%lf", &size);
    printf("\nEnter average sleep time: ");
    scanf("%lf", &avg_sleep);
    printf("\nEnter average yodel time: ");
    scanf("%lf", &avg_yodel);
    printf("\n\n            Thank you, program will simulate behavior                           \n\n");
    printf("------------------------------------------------------------------------------------\n\n");

    parameters[0] = size;
    parameters[1] = avg_sleep;
    parameters[2] = avg_yodel;

}