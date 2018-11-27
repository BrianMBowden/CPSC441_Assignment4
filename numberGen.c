#include <time.h>
#include <stdlib.h>
#include <math.h>

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