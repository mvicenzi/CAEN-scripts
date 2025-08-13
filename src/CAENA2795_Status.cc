/*-----------------------------------------------------------
File: CAENA2795_Status.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the acquisition status, failure status
 and channel status of A2795 digitizers. 

-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "CAENComm.h"

#include "TPCBoardDB.h"
#include "Utilities.h"

void PrintStatusLegend()
{
  printf("*** Status legend:\n"
         "RUN  : 0=stopped, 1=running\n"
         "DRDY : 0=data not available, 1=data ready\n"
         "BUSY : 0=board not full, 1=board full\n");
}

void GetStatus(int handle, int verbosity)
{
  uint32_t data;
  bool verb = verbosity > 0;
  int retcod = CAENComm_Read32(handle, 0x1018, &data);
  if ( retcod == CAENComm_Success )
  {
    int  slot = data & 0x0F;
    bool run  = data & 0x10;
    bool drdy = data & 0x20;
    bool busy = data & 0x40;

    printf(", slot %d",slot);
    if(verb || busy) //print if verbose, or issue detected
      printf(" - RUN: %d  DRDY: %d  BUSY: %d", run, drdy, busy);
  }
  else
  { 
    printf("  [ERROR] CAENComm_Read32 STATUS (0x1018) %d", retcod);
  }
  printf("\n");
}

void GetTemperatures(int handle, int verbosity)
{
  uint32_t data;
  bool verb = verbosity > 1;
  int retcod = CAENComm_Read32(handle, 0x1108, &data);
  if ( retcod == CAENComm_Success )
  {
    uint8_t t1 = (data & 0xff);
    uint8_t t2 = ((data & 0xff0000) >> 16);

    if(verb || t1 > 40 || t2 > 40) //print if verbose
      printf("    TEMP1 [C]: %d  TEMP2 [C]: %d\n", t1, t2);
  }
  else
  { 
    printf("    [ERROR] CAENComm_Read32 TEMPS (0x1108) %d\n", retcod);
  }
}

void CheckDaisyChain(int link, int nboards, int verbosity)
{
  int retcode, handle;
  
  for (int br=0; br<nboards; br++)
  {
    printf("  Link %d - Board %d", link, br);
    retcode = CAENComm_OpenDevice2(CAENComm_OpticalLink, &link, br, 0, &handle);
    if( retcode == CAENComm_Success )
    { 
      GetStatus(handle,verbosity);
      GetTemperatures(handle,verbosity); 
      CAENComm_CloseDevice(handle);
    }
    else printf("[ERROR] CAENComm_OpenDevice2 %d\n", retcode);
  }
}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  
  int verbosity = 1;
  if ( argc > 1 ) verbosity = atoi(argv[1]);

  int link1, link2, nbr1, nbr2;
 
  if ( verbosity > 1 ){ 
    utils::CheckSoftwareReleases();
    PrintStatusLegend();
  }
  printf("==============================\n");
  
  TPCBoardDB::A2795Crate crates[N_CRATES];
  TPCBoardDB::GetListOfCrates(crates);

  for ( int i=0; i<N_CRATES; i++) //loop all crates
  {
    link1 = crates[i].link1;
    link2 = crates[i].link2;
    nbr1 = crates[i].nboards1;
    nbr2 = crates[i].nboards2;

    if(verbosity > 0) printf("----------------------\n");
    printf("Crate %s (fragmentID: %d)\n", crates[i].name, crates[i].fragmentID);
  
    // check daisy chain on link1
    CheckDaisyChain(link1, nbr1, verbosity);
    // check daisy chain on link2
    CheckDaisyChain(link2, nbr2, verbosity);
  }
}

