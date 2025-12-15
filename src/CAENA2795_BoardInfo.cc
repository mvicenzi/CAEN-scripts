/*-----------------------------------------------------------
File: CAENA2795_BoardInfo.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the serial number, firmware and driver
 releases of A2795 digitizers and their A3818/A5818 bridges.

-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "CAENComm.h"
#include "CAENVMEtypes.h"

#include "Utils.h"
#include "TPCBoardDB.h"


void GetBoardInfo(int handle, int link, int bridge)
{
  int retcode=0;
  uint32_t data;

  // MODEL -- this is not working properly
  /*uint32_t model, sn, year, num;

  retcode = CAENComm_Read32(handle, 0x2000, &model);
  if (!retcode) printf("    Model: %d\n",model);
  else printf("    [ERROR] CAENComm_Read32 0x2000 %d\n",retcode);

  retcode = CAENComm_Read32(handle, 0x2004, &sn);
  if (!retcode) printf("    S/N: %d\n",sn);
  else printf("    [ERROR] CAENComm_Read32 0x2004 %d\n",retcode);

  retcode = CAENComm_Read32(handle, 0x2008, &year);
  if (!retcode) printf("    Year: %d\n",year);
  else printf("    [ERROR] CAENComm_Read32 0x2008 %d\n",retcode);

  retcode = CAENComm_Read32(handle, 0x200C, &num);
  if (!retcode) printf("    Prd. Num: %d\n",num);
  else printf("    [ERROR] CAENComm_Read32 0x200C %d\n",retcode);
  */

  // FIRMWARE
  retcode = CAENComm_Read32(handle, 0x1000, &data);
  if( retcode == CAENComm_Success )
  {
    uint8_t  version_major  = ((data & 0x0000FF00) >> 8); // these version numbers might be intended to be read as the revision_day below
    uint8_t  version_minor  = (data & 0x000000FF);        // but it's still sequential, so I don't think it matters too much
    uint8_t  revision_day   = 10*((data & 0x00F00000) >> 20) + ((data & 0x000F0000) >> 16); // this is an insane way to store a day
    uint8_t  revision_month = ((data & 0x0F000000) >> 24);
    uint16_t revision_year  = 2016 + ((data & 0xF0000000) >> 28);

    printf("    Firmware: %d.%d  Realized: %d/%d/%d\n",
           	version_major, version_minor, revision_year, revision_month, revision_day);
  }
  else printf("    [ERROR] CAENComm_Read32 FIRMWARE %d\n",retcode);

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
 
  auto errcode = CAENVME_Init2(cvAX818, &link, Device, &BHandle);
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
  else printf("    [ERROR] CAENVME_Init2 to cvA%d818 %s\n",bridge,CAENVME_DecodeError(errcode)); 

}

/*--------------------------------------------------------*/

void GetSlot(int handle)
{
  uint32_t data;
  int retcod = CAENComm_Read32(handle, 0x1018, &data);
  if ( retcod == CAENComm_Success )
  {
    int  slot = data & 0x0F;
    printf(", slot %d\n",slot);
  }
  else
  { 
    printf("  [ERROR] CAENComm_Read32 SLOT (0x1018) %d\n", retcod);
  }
}

/*--------------------------------------------------------*/

void CheckDaisyChain(int link, int nboards, int bridge)
{
  int retcode, handle;
  for (int br=0; br<nboards; br++)
  {
    printf("  Link %d - Board %d", link, br);
    retcode = CAENComm_OpenDevice2(CAENComm_OpticalLink, &link, br, 0, &handle);
    if( retcode == CAENComm_Success )
    { 
      GetSlot(handle);
      GetBoardInfo(handle,link,bridge); 
      CAENComm_CloseDevice(handle);
    }
    else printf("[ERROR] CAENComm_OpenDevice2 %d\n", retcode);
  }
}


/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  
  int link1, link2, nbr1, nbr2, bridge;
  
  // CAEN software
  utils::CheckSoftwareReleases();

  TPCBoardDB::A2795Crate crates[N_CRATES];
  TPCBoardDB::GetListOfCrates(crates);

  for ( int i=0; i<N_CRATES; i++) //loop all crates
  {
    link1 = crates[i].link1;
    link2 = crates[i].link2;
    nbr1 = crates[i].nboards1;
    nbr2 = crates[i].nboards2;
    bridge = crates[i].aX818;

    printf("----------------------\n");
    printf("Crate %s (fragmentID: %d)\n", crates[i].name, crates[i].fragmentID);
  
    // check daisy chain on link1
    CheckDaisyChain(link1, nbr1, bridge);
    // check daisy chain on link2
    CheckDaisyChain(link2, nbr2, bridge);
  }
}

