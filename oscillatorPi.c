
#include "oscillatorPi.h"


int osc_frequency;
struct timespec *rem;

int initOscillatorPi(){
  int ret_val = 0;
  pthread_t osc_thread;
  /* if(wiringPiSetup() == -1){ */
  /*   return FALSE; */
  /* } */

  /* pinMode(OSC_GPIOPIN, OUTPUT); */

  
  /* start oscillate thread */
  ret_val = pthread_create(&osc_thread, NULL, oscillate, NULL);
  if(ret_val){
    return FALSE;
  }
  
  return TRUE;
}


void *oscillate(){
  struct timespec delayTime;
  int cur_frequency = 0;
  while(1){
    delayTime.tv_nsec = 500000000/osc_frequency;
    cur_frequency = osc_frequency;
    
    while(osc_frequency == cur_frequency){
      
      /* digitalWrite(OSC_GPIOPIN,HIGH); */
      clock_nanosleep(CLOCK_MONOTONIC, 0, &delayTime, rem);/* delay */

      /* digitalWrite(OSC_GPIOPIN,LOW); */
      clock_nanosleep(CLOCK_MONOTONIC, 0, &delayTime, rem);/* delay */

    }
  }

  
}








