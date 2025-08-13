/*-----------------------------------------------------------
File: CAENV1730_ClockPhaseOut.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script configures V1730 digitizers to route their
 internal clock phases to TRGOUT for diagnosis.

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "BoardDB.h"
#include "Utilities.h"

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  uint32_t data;
  board = 0; // Can be 0...7, but we only use one per optical chain
  utils::CheckSoftwareReleases();
  
  if ( argc < 2 )
  {
    printf("****** missing input parameters *****\n"
           "Usage:   CAENClockOut [link 0] [link 1] [link 2] ...\n");
    return 1;
  }
  
  boardDB::V1730 boards[N_LINKS];
  boardDB::GetListOfBoards(boards);
  
  for (int i=1; i<argc; i++)
  {
    link = atoi(argv[i]); 
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success)
    { 
      data =  0x00090000; //set bit[16:17] to 01 and bit[18:19] to 10
      retcod = CAEN_DGTZ_WriteRegister(handle, CAEN_DGTZ_FRONT_PANEL_IO_CTRL_ADD, data);
      if ( retcod != CAEN_DGTZ_Success )
        printf("[ERROR] CAEN_DGTZ_TRIG_OUT %s\n", retcod);
      
      printf("Link %d (%s) clock phase sent to TRIGOUT\n", link, boards[link].name);
      sleep(0.1);
      
      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else printf("[ERROR] Link %d CAEN_DGTZ_OpenDigitizer %d\n", link, retcod);      
  }
}
