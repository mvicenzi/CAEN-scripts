/*-----------------------------------------------------------
File: CAENV1730_BoardInfo.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the serial number, firmware and driver
 releases of V1730 digitizers and their A3818 bridges.

-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"

#include "Utilities.h"
#include "BoardDB.h"

void GetBoardInfo(int fHandle, int fLink)
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

  // A3818 Firmware / Driver
  short Device = 0;
  int32_t BHandle;
 
  auto errcode = CAENVME_Init2(cvA3818, &fLink, Device, &BHandle);
  if( errcode == cvSuccess ) 
  {
    char fwrev[100];
    char drrev[100];
    
    auto ret = CAENVME_BoardFWRelease(BHandle,fwrev);
    printf("    A3818 firmware: ");
    if (!ret) printf("%s\n",fwrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
    
    ret = CAENVME_DriverRelease( BHandle, drrev );
    printf("    A3818 driver: ");
    if (!ret) printf("%s\n",drrev);
    else printf("%s\n",CAENVME_DecodeError(ret));
   
    CAENVME_End(BHandle);
  }
  else printf("[ERROR] CAENVME_Init2 to cvA3818 %s\n",CAENVME_DecodeError(errcode)); 

}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
  
  // CAEN software
  utils::CheckSoftwareReleases();

  boardDB::V1730 boards[N_LINKS];
  boardDB::GetListOfBoards(boards);

  for ( int i=0; i<N_LINKS; i++) //loop all boards
  {
    link = boards[i].link;

    printf("----------------------\n" 
           "Optical link: %d - %s (fragmentID: %d, boardID: %d)\n",
            link, boards[i].name, boards[i].fragmentID, boards[i].boardID);
    
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success)
    { 
      GetBoardInfo(handle, link);
      CAEN_DGTZ_CloseDigitizer(handle); 
    }
    else printf("[ERROR] CAEN_DGTZ_OpenDigitizer %d\n",retcod);
  }

}

