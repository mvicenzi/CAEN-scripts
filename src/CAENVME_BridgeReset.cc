/*-----------------------------------------------------------
File: CAENVME_BridgeReset.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script sends a system reset signal to A3818/A5818 VME bridge.

-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#include "CAENVMEtypes.h"
#include "Utilities.h"
#include "PMTBoardDB.h"

void BridgeReset(int link, int bridge)
{
  short Device = 0; // Can be 0...7, but we only use one per optical chain
  int32_t BHandle;

  CVBoardTypes cvAX818;
  switch (bridge)
  {
    case 3:
      cvAX818 = cvA3818;
      break;
    case 5:
      cvAX818 = cvA5818;
      break;
  }

  auto errcode = CAENVME_Init2(cvAX818, &link, Device, &BHandle);
  if( errcode == cvSuccess ) 
  {
    char fwrev[100];
    char drrev[100];
    
    auto ret = CAENVME_BoardFWRelease(BHandle,fwrev);
    printf("A%d818 firmware: ",bridge);
    if (!ret) printf("%s\n",fwrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
    
    ret = CAENVME_DriverRelease( BHandle, drrev );
    printf("A%d818 driver: ",bridge);
    if (!ret) printf("%s\n",drrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
 
    ret = CAENVME_DeviceReset(BHandle);
    printf("Device reset to cvA%d818 (link %d): %s\n -- \n",bridge,link,CAENVME_DecodeError(ret));
    sleep(0.1);
    //ret = CAENVME_SystemReset(BHandle);
    //printf("System reset to cvA3818 (link %d): %s\n -- \n",link,CAENVME_DecodeError(ret));
    //sleep(0.1);

    CAENVME_End(BHandle);
  }
  else printf("[ERROR] CAENVME_Init2 to cvA%d818 (link %d): %s\n",bridge,link,CAENVME_DecodeError(errcode)); 
}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  
  utils::CheckSoftwareReleases();
  
  PMTBoardDB::V1730 boards[N_LINKS];
  PMTBoardDB::GetListOfBoards(boards);
  
  //Resetting first bridge (link 0-3)
  int link = 0;
  int bridge = boards[link].aX818
  BridgeReset(link,bridge);

  //Resetting second bridge (link 4-7)
  link = 4;
  bridge = boards[link].aX818
  BridgeReset(link,bridge);

  return 0;
}
