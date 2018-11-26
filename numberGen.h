#ifndef NUMBERGEN_H
#define NUMBERGEN_H

#define MAX_INT 0x7FFFFFFF /* Maximum positive integer 2^31 - 1 */
#define __SEED 0

double uniform01();
double seedUniform01();
double Exponential(double mu);

#endif