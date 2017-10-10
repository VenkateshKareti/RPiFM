
#ifndef FM_H
#define FM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oscillatorPi.h"

#define PCM_FILE "part.pcm"

#define SAMPLE_SiZE 16		/* in bits */
#define SAMPLE_RATE 44100	/* 44.1 KHz */
#define SAMPLE_DELAY 22676	/* Nano-sec; (10^9)/44100 */

#define MAX_NO_CHAN 101

#if SAMPLE_SiZE == 16
  #define AMP_LIMIT 65536
#else
  #define AMP_LIMIT 255
#endif


#define BANDWIDTH 200000	/* 200KHz */

#define CHN_NO 95		/* channel No.; not freq. */

#define TRUE 1
#define FALSE 0

/* global variables */
extern int channelFreq[MAX_NO_CHAN+1];
extern int osc_frequency;

int frequencyMap(int chanNo,int amp);
int initFM();

#endif










