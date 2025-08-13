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


void ResetDaisyChain(int link, int nboards)
{
  int retcode, handle;
  
  for (int br=0; br<nboards; br++)
  {
    printf("  Link %d - Board %d", link, br);
    retcode = CAENComm_OpenDevice2(CAENComm_OpticalLink, &link, br, 0, &handle);
    if( retcode == CAENComm_Success )
    { 
      // clear
      retcode = CAENComm_Write32(handle, 0x1028, 0x2);
      if(retcode<0) printf(" [ERROR] CAENComm_Write32 CLEAR %d",retcode);
      // reset
      retcode = CAENComm_Write32(handle, 0x1028, 0x1);
      if(retcode<0) printf(" [ERROR] CAENComm_Write32 RESET %d",retcode);
	
      printf("\n");
      CAENComm_CloseDevice(handle);
    }
    else printf("  [ERROR] CAENComm_OpenDevice2 %d\n", retcode);
  }
}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  int link;
  utils::CheckSoftwareReleases();
  
  if ( argc < 2 )
  {
    printf("****** missing input parameters *****\n"
           "Usage:   CAENA2795_Reset [link 0] [link 1] [link 2] ...\n");
    return 1;
  } 

  printf("==============================\n");
  
  TPCBoardDB::A2795Crate crates[N_CRATES];
  TPCBoardDB::GetListOfCrates(crates);

  for (int i=1; i<argc; i++) //loop all link
  {
    link = atoi(argv[i]);
    char name[100] = "EMPTY";
    int nbr = 5;

    for(auto c : crates)
    {
      if( c.link1 == link)
      { 
        nbr = c.nboards1;
        strncpy(name, c.name, sizeof(name));
        name[sizeof(name)-1] = '\0';
        break;
      }
      else if( c.link2 == link )
      {
        nbr = c.nboards2;
	strncpy(name, c.name, sizeof(name));
        name[sizeof(name)-1] = '\0';
        break;
      }      
    }

    printf("Link %d (%s) is resetting\n",link, name);
    ResetDaisyChain(link, nbr);
  }
}

