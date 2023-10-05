#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"

#include "Utilities.h"
#include "BoardDB.h"

void GetBoardInfo(int fHandle, int fLink){

  int retcod=0;
  CAEN_DGTZ_BoardInfo_t info;

  // digitizer FIRMWARE
  retcod = CAEN_DGTZ_GetInfo(fHandle,&info);
  if( retcod == CAEN_DGTZ_Success ){
    std::cout << "    " << info.ModelName << " S/N: " << info.SerialNumber 
              << "\n    Firmware ROC: " << info.ROC_FirmwareRel 
              << "\n    Firmware AMC: " << info.AMC_FirmwareRel << std::endl;
  }
  else std::cout << "[ERROR] CAEN_DGTZ_GetInfo " << retcod << std::endl;

  // A3818 Firmware / Driver
  short Device = 0;
  int32_t BHandle;
 
  auto errcode = CAENVME_Init2(cvA3818, &fLink, Device, &BHandle);
  if( errcode == cvSuccess ) {
  
    char fwrev[100];
    char drrev[100];
    
    auto ret = CAENVME_BoardFWRelease(BHandle,fwrev);
    std::cout << "    A3818 firmware: ";
    if (!ret) std::cout << fwrev << std::endl;
    else std::cout << CAENVME_DecodeError(ret) << std::endl;
    
    ret = CAENVME_DriverRelease( BHandle, drrev );
    std::cout << "    A3818 driver: ";
    if (!ret) std::cout << drrev << std::endl;
    else std::cout << CAENVME_DecodeError(ret) << std::endl;
   
    CAENVME_End(BHandle);
  }
  else std::cout << "[ERROR] CAENVME_Init2 to cvA3818 " << CAENVME_DecodeError(errcode) << std::endl; 

}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
  
  // CAEN software
  caensoft::CheckSoftwareReleases();

  boardDB::V1730 boards[N_LINKS];
  boardDB::GetListOfBoards(boards);

  for ( int i=0; i<N_LINKS; i++) //loop all boards
  {
    link = boards[i].link;

    std::cout << "----------------------" << std::endl; 
    std::cout << "Optical link: " << link << " - " << boards[i].name
              << " (fragmentID: " << boards[i].fragmentID 
              << ", boardID: " << boards[i].boardID << ") " << std::endl;
    
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success){ 
      std::cout << "    -- Board info:" << std::endl;
      GetBoardInfo(handle, link);
      CAEN_DGTZ_CloseDigitizer(handle); 
   }
    else{
      std::cout << "[ERROR] CAEN_DGTZ_OpenDigitizer " << retcod << std::endl;      
    }
  }

}

