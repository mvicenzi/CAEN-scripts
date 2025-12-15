/*-----------------------------------------------------------
File: CAENV1730_ClockOut.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script configures V1730 digitizers to route their
 internal clocks to TRGOUT for diagnosis.

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "PMTBoardDB.h"
#include "Utils.h"
#include "Errors.h"

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
  
  PMTBoardDB::V1730 boards[N_LINKS];
  PMTBoardDB::GetListOfBoards(boards);
  
  for (int i=1; i<argc; i++)
  {
    link = atoi(argv[i]); 
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success)
    { 
      data =  0x00050000; //set bit[16:17] to 01 and bit[18:19] to 01
      retcod = CAEN_DGTZ_WriteRegister(handle, CAEN_DGTZ_FRONT_PANEL_IO_CTRL_ADD, data);
      if ( retcod != CAEN_DGTZ_Success )
        errors::PrintErrorV1730("CAEN_DGTZ_TRIG_OUT", retcod, false);
      
      printf("Link %d (%s) clock sent to TRIGOUT\n", link, boards[link].name);
      sleep(0.1);
      
      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else 
    {
      char desc[100];
      snprintf(desc, sizeof(desc), "Link %d CAEN_DGTZ_OpenDigitizer", link);
      errors::PrintErrorV1730(desc, retcod, false);
    }     
  }
}
