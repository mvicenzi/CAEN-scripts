/*-----------------------------------------------------------
File: CAENV1730_BoardInfo.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the serial number, firmware and driver
 releases of V1730 digitizers and their A3818/A5818 bridges.

-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"

#include "Utilities.h"
#include "PMTBoardDB.h"

void GetBoardInfo(int fHandle, int fLink, int bridge)
{
  int retcod=0;
  CAEN_DGTZ_BoardInfo_t info;

  // digitizer FIRMWARE
  retcod = CAEN_DGTZ_GetInfo(fHandle,&info);
  if( retcod == CAEN_DGTZ_Success )
  {
    printf("    %s S/N: %d\n"
           "    Firmware ROC: %s\n"
           "    Firmware AMC: %s\n",
           info.ModelName, info.SerialNumber, info.ROC_FirmwareRel, info.AMC_FirmwareRel);
  }
  else printf("[ERROR] CAEN_DGTZ_GetInfo %d\n",retcod);

  // A3818/A5818 firmware / driver
  short Device = 0;
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
 
  auto errcode = CAENVME_Init2(cvAX818, &fLink, Device, &BHandle);
  if( errcode == cvSuccess ) 
  {
    char fwrev[100];
    char drrev[100];
    
    auto ret = CAENVME_BoardFWRelease(BHandle,fwrev);
    printf("    A%d818 firmware: ",bridge);
    if (!ret) printf("%s\n",fwrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
    
    ret = CAENVME_DriverRelease( BHandle, drrev );
    printf("    A%d818 driver: ",bridge);
    if (!ret) printf("%s\n",drrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
   
    CAENVME_End(BHandle);
  }
  else printf("[ERROR] CAENVME_Init2 to cvA%d818 %s\n",bridge,CAENVME_DecodeError(errcode)); 

}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  int retcod, link, board, handle, bridge;
  board = 0; // Can be 0...7, but we only use one per optical chain
  bridge = 3; // either 3 or 5

  // CAEN software
  utils::CheckSoftwareReleases();

  PMTBoardDB::V1730 boards[N_LINKS];
  PMTBoardDB::GetListOfBoards(boards);

  for ( int i=0; i<N_LINKS; i++) //loop all boards
  {
    link = boards[i].link;
    bridge = boards[i].aX818;

    printf("----------------------\n" 
           "Optical link: %d - %s (fragmentID: %d, boardID: %d)\n",
            link, boards[i].name, boards[i].fragmentID, boards[i].boardID);
    
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success)
    { 
      GetBoardInfo(handle, link, bridge);
      CAEN_DGTZ_CloseDigitizer(handle); 
    }
    else printf("[ERROR] CAEN_DGTZ_OpenDigitizer %d\n",retcod);
  }

}

