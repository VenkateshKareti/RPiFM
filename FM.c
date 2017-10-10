
#include <stdio.h>

#include "FM.h"

int channelFreq[MAX_NO_CHAN+1] = {0,88100000,88300000,88500000,88700000,88900000,89100000,89300000,89500000,89700000,89900000,90100000,90300000,90500000,90700000,90900000,91100000,91300000,91500000,91700000,91900000,92100000,92300000,92500000,92700000,92900000,93100000,93300000,93500000,93700000,93900000,94100000,94300000,94500000,94700000,94900000,95100000,95300000,95500000,95700000,95900000,96100000,96300000,96500000,96700000,96900000,97100000,97300000,97500000,97700000,97900000,98100000,98300000,98500000,98700000,98900000,99100000,99300000,99500000,99700000,99900000,100100000,100300000,100500000,100700000,100900000,101100000,101300000,101500000,101700000,101900000,102100000,102300000,102500000,102700000,102900000,103100000,103300000,103500000,103700000,103900000,104100000,104300000,104500000,104700000,104900000,105100000,105300000,105500000,105700000,105900000,106100000,106300000,106500000,106700000,106900000,107100000,107300000,107500000,107700000,107900000,108100000};


int initFM(){
  
  return TRUE;
}


int frequencyMap(int chanNo,int amp){

  int freqMap = 0;
  
  /* param checks */
  if(chanNo > 101 || chanNo < 1){
    return FALSE;
  }
  if(amp < 0 || amp > AMP_LIMIT){
    return FALSE;
  }


  freqMap = ((BANDWIDTH-1)*amp)/AMP_LIMIT;
  freqMap += channelFreq[chanNo];

  return freqMap;
}


int preparePCMFile(char *src_filePath, char *dst_filePath){
  int ret_val = 0;

  /* param check */
  if(src_filePath == NULL){
    return FALSE;
  }
  if(dst_filePath == NULL){
    return FALSE;
  }

  /* prepare PCM generate cmd */
  char cmd[10000] = "mpg123 -s --mono -r 44100 ";
  strcat(cmd,src_filePath);
  strcat(cmd,"  > ");
  strcat(cmd,dst_filePath);

  /* generate PCM file */
  ret_val = system(cmd);

  return ret_val;
}


int parsePCM(char *pcm_filePath){
  int ret_val = 0;
  FILE *openPCM = NULL;
  int buffLen = 3*60*44100;	/* 3min buffer; ~16MB */
  short sample_val[buffLen];
  int noOfSamples = 0;
  int index = 0;
  
  /* param checks */
  if(pcm_filePath == NULL){
    return FALSE;
  }
  
  /* open PCM File */
  openPCM = fopen(pcm_filePath,"rb");
  if(openPCM == NULL){
    return FALSE;
  }
  
  
  /* set current osc_frequency for each sample */
  while(1){
    if(index == noOfSamples){
      noOfSamples= fread(sample_val,2,buffLen,openPCM);/* read samples */
      if(noOfSamples == 0){
	return TRUE;		/* end of file! */
      }
      index = 0;
    }

    ret_val = frequencyMap(CHN_NO, sample_val[index]);
    if(ret_val == FALSE){
      return FALSE;
    }else{
      osc_frequency = ret_val;
    }
    
    index++;
  }
  
}


int playFM(char *filePath){
  int ret_val = 0;
  
  /* parm checks */
  if(filePath == NULL){
    return FALSE;
  }

  /* generate PCM file */
  ret_val = preparePCMFile(filePath, PCM_FILE);
  if(ret_val){
    return FALSE;
  }

  
  /* parse PCM file */
  ret_val = parsePCM(PCM_FILE);
  if(ret_val == FALSE){
    return FALSE;
  }
  
  return TRUE;
}


int main(){
  int ret_val = 0;

  ret_val = initOscillatorPi();
  if(ret_val == FALSE){
    exit(FALSE);
  }

  ret_val = playFM("BillieJean.mp3");
  if(ret_val == FALSE){
    return FALSE;
  }

  
  return TRUE;
}
