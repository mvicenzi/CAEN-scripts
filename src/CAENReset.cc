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
    std::cout << "****** missing input parameters *****" << std::endl;
    std::cout << "Usage:   CAENReset [link 0] [link 1] [link 2] ..." << std::endl;
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
      retcod = CAEN_DGTZ_Reset(handle);
      if ( retcod != CAEN_DGTZ_Success )
        std::cout << "[ERROR] CAEN_DGTZ_Reset " << retcod << std::endl;
      
      std::cout << "Link " << link << " (" << boards[link].name << ") is resetting" << std::endl;
      sleep(0.1);
      
      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else std::cout << "[ERROR] CAEN_DGTZ_OpenDigitizer " << retcod << std::endl;      
  }

}
