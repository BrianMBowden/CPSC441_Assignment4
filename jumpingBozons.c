#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "jumpingBozons.h"
#include "numberGen.h"

struct Bozon{
    int name;
    double sleep_time;
    double yodel_time; 
    double sleep_start;
    double yodel_start;
    int sleeping;
};

int main(int argc, char** argv){

    double args_notprovided[3]; //M, S, Y
    int colony_size;

    /* Exponential Variables */
    double random_yodel;
    double random_sleep;

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
    int sleeping = 0;

    /* Start Up */
    if (argc == 1){
        welcomePrompt(args_notprovided);
    }
    else if (argc == 4){
        args_notprovided[0] = atof(argv[1]);
        args_notprovided[1] = atof(argv[2]);
        args_notprovided[2] = atof(argv[3]);
    }
    else{
        printf("Usage: arguments provided not zero or three\n");
        return 0;
    }

#if __DEBUG
    printf("M= %lf \tS= %lf \tY= %lf \n",args_notprovided[0], args_notprovided[1], args_notprovided[2]);
#endif

    colony_size = (int)args_notprovided[0];
 //   random_sleep = Exponential(args_notprovided[1]);
 //   random_yodel = Exponential(args_notprovided[2]);

#if __DEBUG
    //printf("M= %d \tS_mu= %lf \tY_mu = %lf \n", colony_size, random_sleep, random_yodel);
#endif

    colony = (struct Bozon*)malloc(colony_size * sizeof(struct Bozon));

    /* Initialize Colony */ 
    for (i = 0; i < colony_size; i++){
        colony[i].name = i;
        colony[i].sleep_time = Exponential(args_notprovided[1]);
        colony[i].yodel_time = Exponential(args_notprovided[2]);
        colony[i].sleep_start = START;
//        colony[i].yodel_start = colony[i].sleep_time;
        colony[i].sleeping = 1;
        printf("Bozon ID: %d || Sleeps for: %lf || Yodels for: %lf\n", colony[i].name, colony[i].sleep_time, colony[i].yodel_time);
    }

    for (;start < MAX_TIME; (start += TIME_INC)){
        //printf("the time is: %lf\n", start);
        for (i = 0; i < colony_size; i++){
            if (colony[i].sleeping){
                if (colony[i].sleep_start + colony[i].sleep_time <= start){
                    //wake it up, start yodelling
                    colony[i].sleeping = 0;
                    colony[i].yodel_start = start;
                    yodelling++;
                }
                //printf("Bozon %d is sleeping\n", colony[i].name);
            }
            else{
                // must be yodelling
                if ((colony[i].yodel_start + colony[i].yodel_time) <= start){
                //done yodelling, go to bed, update time
                    colony[i].sleeping = 1;
                    colony[i].sleep_start = start;
                    yodelling--;
                }
                //printf("Bozon %d is yodelling\n", colony[i].name);
            } 
        }
        if (yodelling == 0){
            time_silent += start;
        }
        else if (yodelling == 1){
            time_harmonious += start;
        }
        else{
            time_screechy += start;
        }
    }

    printf("Time spent silent: %lf\nTime spent harmonious: %lf\nTime spent screechy: %lf\n", time_silent/start, time_harmonious/start, time_screechy/start);
    

    return 0;
}

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