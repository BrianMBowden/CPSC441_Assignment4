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
    short perfect;
};

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

    /* File stuff for populating Excel spreadsheet */
#if __BONUS
    fp = fopen("./bonus.txt", "a");
#else
    fp = fopen("./report.txt", "a");
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
        colony[i].name = i;
        colony[i].sleep_time = Exponential(args_notprovided[1]);
#if __BONUS
        colony[i].yodel_time = 10.0;
#else
        colony[i].yodel_time = Exponential(args_notprovided[2]);
#endif
        colony[i].sleep_start = START;
        colony[i].sleeping = 1;
#if __DEBUG
        printf("Bozon ID: %d || Sleeps for: %lf || Yodels for: %lf\n", colony[i].name, colony[i].sleep_time, colony[i].yodel_time);
#endif
    }

    for (;start < MAX_TIME; (start += TIME_INC)){
        //printf("the time is: %lf\n", start);
        for (i = 0; i < colony_size; i++){
            if (colony[i].sleeping){
                if ((colony[i].sleep_start + colony[i].sleep_time) <= start){
                    //wake it up, start yodelling
                    colony[i].sleeping = 0;
                    colony[i].yodel_start = start;
#if __BONUS
                    colony[i].yodel_time = 10.0;
#else
                    colony[i].yodel_time = Exponential(args_notprovided[2]);
#endif
                    colony[i].perfect = 1;
                    yodelling++;
                    attempted_yodels++;
                    perfect_yodels++;
                }
            }
            else{
                // must be yodelling
                if (yodelling > 1){
                    colony[i].perfect = 0;
                }
                if ((colony[i].yodel_start + colony[i].yodel_time) <= start){
                    //done yodelling, go to bed, update time
                    colony[i].sleeping = 1;
                    colony[i].sleep_start = start;
                    colony[i].sleep_time = Exponential(args_notprovided[1]);
                    if (!colony[i].perfect){
                        perfect_yodels--;
                    }  
                    colony[i].perfect = 0;
                    yodelling--;
                }
            }
        }

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

    printf("Time elapsed:     %lf\n", start);
    printf("Time silent:      %lf || (%lf%%)\n", time_silent, 100.0*time_silent/start);
    printf("Time harmonious:  %lf || (%lf%%)\n", time_harmonious, 100.0*time_harmonious/start);
    printf("Time screechy:    %lf || (%lf%%)\n", time_screechy, 100.0*time_screechy/start);
    printf("Attempted yodels: %d\n", attempted_yodels);
    printf("Perfect yodels:   %d\n", perfect_yodels);

    //printf("Time spent silent: %lf\nTime spent harmonious: %lf\nTime spent screechy: %lf\nTotal time elapsed: %lf\n", time_silent, time_harmonious, time_screechy, start);
    /* Write data to file */
    //            M   S   Y S_t H_t C_t
    //fprintf(fp, "%d|%lf|%lf|%lf|%lf|%lf\n", colony_size, args_notprovided[1], args_notprovided[2], 100.0*time_silent/start, 100*time_harmonious/start, 100*time_screechy/start);    

    fprintf(fp, "%d|%lf|%lf|", colony_size, args_notprovided[1], args_notprovided[2]);
    fprintf(fp, "%lf|%lf|%lf|", 100.0*time_silent/start, 100*time_harmonious/start, 100*time_screechy/start);
    fprintf(fp, "%d|%d\n", attempted_yodels, perfect_yodels);

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