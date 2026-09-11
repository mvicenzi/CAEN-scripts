/*-----------------------------------------------------------
File: CAENV1730_Clear.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script sends a clear data command to V1730 digitizers.
 Data buffers are cleared, but internal registers and states
 are left untouched.

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "PMTBoardDB.h"
#include "Utils.h"
#include "Errors.h"

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
  utils::CheckSoftwareReleases();

  if (argc < 2)
  {
    printf("****** missing input parameters *****\n"
           "Usage:   CAENV1730_Clear [link 0] [link 1] [link 2] ...\n");
    return 1;
  }

  PMTBoardDB::V1730 boards[N_LINKS];
  PMTBoardDB::GetListOfBoards(boards);

  for (int i = 1; i < argc; i++)
  {
    link = atoi(argv[i]);
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
                                     link, board, 0, &handle);
    if (retcod == CAEN_DGTZ_Success)
    {
      printf("Link %d (%s) is clearing data\n", link, boards[link].name);

      retcod = CAEN_DGTZ_ClearData(handle);
      if (retcod != CAEN_DGTZ_Success)
        errors::PrintErrorV1730("CAEN_DGTZ_ClearData", retcod, false);

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
