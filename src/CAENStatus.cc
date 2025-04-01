/*-----------------------------------------------------------
File: CAENStatus.cc
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This script prints the acquisition status, failure status
 and channel status of V1730 digitizers. 

-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"

#include "BoardDB.h"
#include "Utilities.h"

void PrintAcquisitionStatusLegend()
{
  printf("*** Status legend:\n"
         "RUN  : 0=stopped, 1=running\n"
         "DRDY : 0=data not available, 1=data ready\n"
         "BUSY : 0=board not full, 1=board full\n"
         "CLK  : 0=internal, 1=external CLK-IN\n"
         "PLL  : 0=PLL unlock, 1=PLL lock\n"
         "RDY  : 0=not ready, 1=ready for data\n"
         "SHUT : 0=channels ON, 1=channels shutdown\n");
}

void GetAcquisitionStatus(int fHandle, int verbosity)
{
  uint32_t data;
  bool verb = verbosity > 0;
  auto retcod = CAEN_DGTZ_ReadRegister(fHandle,CAEN_DGTZ_ACQ_STATUS_ADD,&data);
  if ( retcod == CAEN_DGTZ_Success )
  {
    bool run  = data & 0x0004;
    bool drdy = data & 0x0008;
    bool full = data & 0x0010;
    bool clk  = data & 0x0020;
    bool pll  = data & 0x0080;
    bool rdy  = data & 0x0100;
    bool shut = data & 0x80000;   

    if(verb || shut || !rdy || full || !clk || !pll ) //print if verbose, or issue detected
    printf("Status     RUN: %d  DRDY: %d  BUSY: %d  CLK: %d  PLL: %d  RDY: %d  SHUT: %d\n",
           run, drdy, full, clk, pll, rdy, shut);
  }
  else printf("    [ERROR] CAEN_DGTZ_ACQ_STATUS %d\n", retcod);
}

void PrintFailureStatusLegend()
{
  printf("*** Failure legend:\n"
         "PLL  : PLL lock loss\n"
         "TEMP : Temperature failure\n"
         "ADC  : ADC power down\n"
         "BUS  : VME bus error\n");
}

void GetFailureStatus(int fHandle)
{
  uint32_t data;
  bool pll=0, temp=0, adc=0, bus=0;
  auto retcod = CAEN_DGTZ_ReadRegister(fHandle,0x8178,&data);
  if ( retcod == CAEN_DGTZ_Success )
  {
    pll = data & 0x0010;
    temp = data & 0x0020;
    adc = data & 0x0040; 
  } 
  else printf("    [ERROR] CAEN_DGTZ_FAILURE_STATUS %d\n",retcod);
  
  retcod = CAEN_DGTZ_ReadRegister(fHandle,0xEF04,&data);
  if( retcod == CAEN_DGTZ_Success )
  {
    bus = data & 0x0004;
  }
  else printf("    [ERROR] CAEN_DGTZ_READOUT_STATUS %d\n",retcod); 
  
  if( pll || temp || adc || bus ) 
      printf("Failure    PLL: %d  TEMP: %d  ADC: %d  BUS: %d\n", pll, temp, adc, bus); 
}


void PrintChannelStatusLegend()
{   
  printf("*** Channel status legend:\n"
         "BUSY : 0=memory not full, 1=memory full\n"
         "DAC  : 0=DC offset update, 1=busy\n"
         "ADC  : 0=not calibrated, 1=calibrated\n"
         "OFF  : 0=on, 1=off\n"
         "TEMP : ADC temperature in Celsius\n");
}

void GetChannelStatus(int fHandle, int verbosity)
{
  uint32_t ch_temps[MAX_CHANNELS];
  uint32_t ch_status[MAX_CHANNELS]; 
  uint32_t maxT = 0;

  for(size_t ch =0; ch<MAX_CHANNELS; ch++)
  { 
    auto err = CAEN_DGTZ_ReadTemperature(fHandle, ch, &(ch_temps[ch]));
    if( err != CAEN_DGTZ_Success )
      printf("    [ERROR] CAEN_DGTZ_ReadTemperature ch %d %d\n", ch, err); 
    if( ch_temps[ch] > maxT ) maxT = ch_temps[ch];

    uint32_t chStatusAddr = 0x1088 + (ch<<8);
    auto ret = CAEN_DGTZ_ReadRegister(fHandle, chStatusAddr, &(ch_status[ch]));
    if( err != CAEN_DGTZ_Success )
      printf("    [ERROR] CAEN_DGTZ_ReadChannelStatus ch %d %d", ch, err); 
  
  }

  if( verbosity > 0 || maxT > 60 ) printf("    Max Temp. [C]: %d\n", maxT);
  
  bool verb = verbosity > 1; 
  for(size_t ch =0; ch<MAX_CHANNELS; ch++)
  { 
    bool full = ch_status[ch] & 0x1;
    bool dac = ch_status[ch] & 0x4;
    bool adc = ch_status[ch] & 0x8;
    bool off = ch_status[ch] & 0x100;
   
    if( full || dac || !adc || off || verb ) 
      printf("     Ch: %d  BUSY: %d  DAC: %d  ADC: %d  OFF: %d  TEMP: %d\n",
                 ch, full, dac, adc, off, ch_temps[ch]);
  }
}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  
  int verbosity = 1;
  if ( argc > 1 ) verbosity = atoi(argv[1]);

  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
 
  if ( verbosity > 0 ){ 
    utils::CheckSoftwareReleases();
    PrintAcquisitionStatusLegend();
    PrintFailureStatusLegend();
    PrintChannelStatusLegend();
  }
  printf("==============================\n");
  
  boardDB::V1730 boards[N_LINKS];
  boardDB::GetListOfBoards(boards);

  for ( int i=0; i<N_LINKS; i++) //loop all boards
  {
    link = boards[i].link;

    if(verbosity > 0) printf("----------------------\n");
    printf("Optical link: %d - %s (fragmentID: %d, boardID: %d)\n",
            link, boards[i].name, boards[i].fragmentID, boards[i].boardID);
    
    retcod = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_OpticalLink,
				     link, board, 0, &handle);
    if( retcod == CAEN_DGTZ_Success)
    { 
      GetAcquisitionStatus(handle,verbosity);
      GetFailureStatus(handle);
      GetChannelStatus(handle,verbosity);

      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else if ( boards[i].fragmentID>0 ) //only if non-empty board
      printf("[ERROR] CAEN_DGTZ_OpenDigitizer %d\n", retcod);
  }

}

