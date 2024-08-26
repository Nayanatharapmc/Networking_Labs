// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    free(inputsignal);
    
	return 0;
}

void run(asignal * inputsignal) 
{
    int interval,encoderbits;  //To store user input

    /*Getting user inputs*/
    scanf("%f %f %f %d %d %d",&inputsignal->A,&inputsignal->omega,&inputsignal->sigma,&inputsignal->duration,&interval,&encoderbits);
    int levels = pow(2,encoderbits);  //No. of quantization levels
    int boundaries = (inputsignal->duration / interval)+2;  //No. of sample points + 1(plus one for sentinel)
    
    /*Function calls start here*/
    float * samples = (float *) malloc(boundaries*sizeof(float));
    sampler(samples, interval,*inputsignal);  

    int * pcmpulses = (int *) malloc(boundaries*sizeof(int));
    quantizer(samples,pcmpulses,levels,inputsignal->A);

    int * dsignal = (int *) malloc(boundaries*encoderbits*sizeof(int));
    encoder(pcmpulses,dsignal,encoderbits);

    free(samples);
    free(pcmpulses);
    free(dsignal);
}