// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <string.h>
#include <math.h>

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
int decimal_to_binary(int num){
	/*This function will convert a given decimal number to binary*/
    if (num == 0) {
        return 0;
    }
    char bin_num[100]= "";
    int i = 0;
    while (num > 0) {
        bin_num[i++] = (num % 2 == 0) ? '0' : '1';
        num = num / 2;
    }
    // Reverse the binary number
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = bin_num[start];
        bin_num[start] = bin_num[end];
        bin_num[end] = temp;
        start++;
        end--;
    }
    bin_num[i] = '\0';  // null-terminate the string

    // Return the binary number as a string 
    return atoi(strdup(bin_num));
}

// implementation
float analog_signal_generator(asignal signal, int t)
{
	/*This function returns the analog waveform value with the given A,omega and sigma values at a given instance*/
	float new_signal = (signal.A) *  sin((signal.omega*t)+signal.sigma);
	return new_signal;
}
void sampler(float *samples, int interval, asignal signal)
{
	/*This function updates the given samples array with the relevant samples*/
	int count = (signal.duration/interval);
	for(int i=0;i<=count;i++){
		samples[i]=analog_signal_generator(signal,(i*interval));
	}
	samples[count+1]=INFINITY;  //Sentinel set to INFINITY
}
void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
	/*This function produces the PCM pulses*/
	float *ptr = samples;
	float sentinel = INFINITY; // Defining the sentinel value
	int i=0;
	
    while (*ptr != sentinel) {  //Iterating through the samples array
        ptr++;
		int pulse = floor(((samples[i]+A)/(2*A))*levels);
		pcmpulses[i]=pulse;    //PCM pulse generation
		i++;
    }
	pcmpulses[i]=-1;  //Sentinel of pcmpulses array
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	/*This function prints the pcm encoded output binary stream*/
	int *ptr = pcmpulses;
	int sentinel = -1; // Defining the sentinel value
	int i=0;
	
    while (*ptr != sentinel) {  //Iterating through the pcmpulses array
        ptr++;
		printf("%0*d",encoderbits,decimal_to_binary(pcmpulses[i]));  //Converting the pcm code to binary
		i++;
    }
	pcmpulses[i]=-1;
	
}