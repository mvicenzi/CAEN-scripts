/*-----------------------------------------------------------
File: CAENReadRegister.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the value(s) of selected registers.
 It is meant for quickly checking the V1730 configuration.

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
  
  if ( argc < 3 )
  {
    printf("****** missing input parameters *****\n"
           "Usage:   CAENReadRegister [opt_link] [reg 1] [reg 2] ...\n");
    return 1;
  }
  
  boardDB::V1730 boards[N_LINKS];
  boardDB::GetListOfBoards(boards);
    
  link = atoi(argv[1]); 
  retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				   link, board, 0, &handle);
    
  if( retcod == CAEN_DGTZ_Success)
  { 
    printf("Checking registers on link %d (%s)\n",link, boards[link].name);
  
    for (int i=2; i<argc; i++)
    {   
      uint32_t addr = strtoul(argv[i],NULL,0);
      uint32_t data;

      printf("Reading register %s (%5d): ",argv[i],addr);

      retcod = CAEN_DGTZ_ReadRegister(handle,addr,&data);

      if(retcod == CAEN_DGTZ_Success) printf("0x%X (%d)\n",data,data);
      else printf("[ERROR] Link %d CAEN_DGTZ_ReadRegister %d\n", link, retcod);      

      sleep(0.1);   
    }   
    CAEN_DGTZ_CloseDigitizer(handle);
  }
  else printf("[ERROR] Link %d CAEN_DGTZ_OpenDigitizer %d\n", link, retcod);      

}
