#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "jumpingBozons.h"
#include "numberGen.h"

int main(int argc, char** argv){

    double args_notprovided[3]; //M, 

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