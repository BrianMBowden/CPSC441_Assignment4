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
};

int main(int argc, char** argv){

    double args_notprovided[3]; //M, S, Y
    int colony_size;

    /* Exponential Variables */
    double random_yodel;
    double random_sleep;

    /* Time Variables */
    double start = START;

    /* Bozon Colony */
    struct Bozon *colony;

    /* Helper Variables */
    int i;

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
        colony[i].yodel_start = colony[i].sleep_time;
        printf("Bozon ID: %d || Sleeps for: %lf || Yodels for: %lf\n", colony[i].name, colony[i].sleep_time, colony[i].yodel_time);
    }

    for (;start < MAX_TIME; (start += TIME_INC)){
        for (i = 0; i < colony_size; i++){
            
        }
    }

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