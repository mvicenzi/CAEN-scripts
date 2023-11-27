/*-----------------------------------------------------------
File: CAENReset.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script sends a software reset signal to V1730 digitizers.
 All internal registers and states are restored to default values.

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "BoardDB.h"
#include "Utilities.h"

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
  utils::CheckSoftwareReleases();
  
  if ( argc < 2 )
  {
    printf("****** missing input parameters *****\n"
           "Usage:   CAENReset [link 0] [link 1] [link 2] ...\n");
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
      printf("Link %d (%s) is resetting\n",link, boards[link].name);
      
      retcod = CAEN_DGTZ_Reset(handle);
      if ( retcod != CAEN_DGTZ_Success )
        printf("[ERROR] CAEN_DGTZ_Reset %d\n",retcod);
      
      retcod = CAEN_DGTZ_ClearData(handle);      
      if ( retcod != CAEN_DGTZ_Success )
	printf("[ERROR] CAEN_DGTZ_ClearData %d\n",retcod);

      sleep(0.1);   
      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else printf("[ERROR] CAEN_DGTZ_OpenDigitizer %s\n", retcod);      
  }

}
