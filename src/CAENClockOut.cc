/*-----------------------------------------------------------
File: CAENClockOut.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script configures V1730 digitizers to route their
 internal clocks to TRGOUT for diagnosis.

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
    std::cout << "****** missing input parameters *****" << std::endl;
    std::cout << "Usage:   CAENClockOut [link 0] [link 1] [link 2] ..." << std::endl;
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
      data =  0x00050000;
      retcod = CAEN_DGTZ_WriteRegister(handle, CAEN_DGTZ_FRONT_PANEL_IO_CTRL_ADD, data);
      if ( retcod != CAEN_DGTZ_Success )
        std::cout << "[ERROR] CAEN_DGTZ_TRIG_OUT " << retcod << std::endl;
      
      std::cout << "Link " << link << " (" << boards[link].name << ") clock sent to TRIGOUT" << std::endl;
      sleep(0.1);
      
      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else std::cout << "[ERROR] CAEN_DGTZ_OpenDigitizer " << retcod << std::endl;      
  }
}
