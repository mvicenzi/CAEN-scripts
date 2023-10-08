/*-----------------------------------------------------------
File: Utilities.h
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This file contains support functions shared between different scripts.

-------------------------------------------------------------*/

#include "CAENDigitizer.h"
#include "CAENVMElib.h"
#include "CAENComm.h"

namespace utils {

// check CAEN software in use
void CheckSoftwareReleases()
{
  char CommSWrel[100], VMESWrel[100], DGTZSWrel[100];
  int retcod = CAEN_DGTZ_SWRelease( DGTZSWrel );
  retcod = CAENVME_SWRelease( VMESWrel );
  retcod = CAENComm_SWRelease( CommSWrel );
  printf("==============================\n"
         "CAEN software releases\n"
         "CAENDGTZ: %s\n"
         "CAENVME: %s\n"
         "CAENComm: %s\n"
         "==============================\n",
         DGTZSWrel, VMESWrel, CommSWrel);
}

}
