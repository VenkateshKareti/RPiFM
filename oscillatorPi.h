
#ifndef OSCILLATOR_PI_H
#define OSCILLATOR_PI_H

/* #include <wiringPi.h> */
#include <time.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

#define OSC_GPIOPIN 0


extern int osc_frequency;
extern struct timespec *rem;


int initOscillatorPi();
void *oscillate();



#endif
