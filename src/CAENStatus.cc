#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"

#include "BoardDB.h"
#include "Utilities.h"

void PrintAcquisitionStatusLegend(){

  std::cout << "*** Status legend: " << std::endl;
  std::cout << "RUN  : 0=stopped, 1=running" <<std::endl;
  std::cout << "DRDY : 0=data not available, 1=data ready" << std::endl;
  std::cout << "BUSY : 0=board not full, 1=board full" << std::endl;
  std::cout << "CLK  : 0=internal, 1=external CLK-IN" << std::endl;
  std::cout << "PLL  : 0=PLL unlock, 1=PLL lock" << std::endl;
  std::cout << "RDY  : 0=not ready, 1=ready for data" << std::endl;
  std::cout << "SHUT : 0=channels ON, 1=channels shutdown" << std::endl;
}

void GetAcquisitionStatus(int fHandle){

  uint32_t data;
  auto retcod = CAEN_DGTZ_ReadRegister(fHandle,CAEN_DGTZ_ACQ_STATUS_ADD,&data);
  if ( retcod == CAEN_DGTZ_Success ){
    bool run  = data & 0x0004;
    bool drdy = data & 0x0008;
    bool full = data & 0x0010;
    bool clk  = data & 0x0020;
    bool pll  = data & 0x0080;
    bool rdy  = data & 0x0100;
    bool shut = data & 0x80000;   

    std::cout << "    RUN  : " << run;
    std::cout << "  DRDY : " << clk; 
    std::cout << "  BUSY : " << full;
    std::cout << "  CLK  : " << clk;
    std::cout << "  PLL  : " << pll;
    std::cout << "  RDY  : " << rdy;
    std::cout << "  SHUT : " << shut << std::endl;
  }
  else std::cout << "    [ERROR] CAEN_DGTZ_ACQ_STATUS " << retcod << std::endl;

}

void PrintFailureStatusLegend(){

  std::cout << "*** Failure legend: " << std::endl;
  std::cout << "PLL  : PLL lock loss" << std::endl;
  std::cout << "TEMP : Temperature failure" << std::endl;
  std::cout << "ADC  : ADC power down" << std::endl;
  std::cout << "BUS  : VME bus error" << std::endl;

}

void GetFailureStatus(int fHandle){

  uint32_t data;
  bool pll=0, temp=0, adc=0, bus=0;
  auto retcod = CAEN_DGTZ_ReadRegister(fHandle,0x8178,&data);
  if ( retcod == CAEN_DGTZ_Success ){
    pll = data & 0x0010;
    temp = data & 0x0020;
    adc = data & 0x0040; 
  } 
  else std::cout << "    [ERROR] CAEN_DGTZ_FAILURE_STATUS " << retcod << std::endl;
  
  retcod = CAEN_DGTZ_ReadRegister(fHandle,0xEF04,&data);
  if( retcod == CAEN_DGTZ_Success ){
    bus = data & 0x0004;
  }
  else std::cout << "\n    [ERROR] CAEN_DGTZ_READOUT_STATUS " << retcod << std::endl; 
  
  if( pll || temp || adc || bus ) 
      std::cout << "    PLL  : " << pll << "  TEMP : " << temp << "  ADC  : " << adc << " BUS  : " << bus << std::endl; 
}


void PrintChannelStatusLegend(){
    
  std::cout << "*** Channel status legend: " << std::endl;
  std::cout << "BUSY : 0=memory not full, 1=memory full" << std::endl;
  std::cout << "DAC  : 0=DC offset update, 1=busy" << std::endl;
  std::cout << "ADC  : 0=not calibrated, 1=calibrated" << std::endl;
  std::cout << "OFF  : 0=on, 1=off" << std::endl;
  std::cout << "TEMP : ADC temperature in Celsius" << std::endl;
}

void GetChannelStatus(int fHandle){

  uint32_t ch_temps[MAX_CHANNELS];
  uint32_t ch_status[MAX_CHANNELS]; 
  uint32_t maxT = 0;


  for(size_t ch =0; ch<MAX_CHANNELS; ch++){
  
    auto err = CAEN_DGTZ_ReadTemperature(fHandle, ch, &(ch_temps[ch]));
    if( err != CAEN_DGTZ_Success )
      std::cout << "    [ERROR] CAEN_DGTZ_ReadTemperature ch " << ch << " " << err << std::endl; 
    if( ch_temps[ch] > maxT ) maxT = ch_temps[ch];

    uint32_t chStatusAddr = 0x1088 + (ch<<8);
    auto ret = CAEN_DGTZ_ReadRegister(fHandle, chStatusAddr, &(ch_status[ch]));
    if( err != CAEN_DGTZ_Success )
      std::cout << "    [ERROR] CAEN_DGTZ_ReadChannelStatus ch " << ch << " " << err << std::endl; 
  
  }

  std::cout << "    Max Temp. [C]: " << maxT << std::endl;
  
  for(size_t ch =0; ch<MAX_CHANNELS; ch++){
  
  bool full = ch_status[ch] & 0x1;
  bool dac = ch_status[ch] & 0x4;
  bool adc = ch_status[ch] & 0x8;
  bool off = ch_status[ch] & 0x100;
 
  if( full || dac || !adc || off ) 
    printf("     Ch:%d  BUSY:%d  DAC:%d  ADC:%d  OFF:%d  TEMP:%d\n",
               ch, full, dac, adc, off, ch_temps[ch]);
  }
}

/*--------------------------------------------------------*/

int main(int argc, char **argv)
{
  int retcod, link, board, handle;
  board = 0; // Can be 0...7, but we only use one per optical chain
  
  caensoft::CheckSoftwareReleases();
  PrintAcquisitionStatusLegend();
  PrintFailureStatusLegend();
  PrintChannelStatusLegend();
  
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

      GetAcquisitionStatus(handle);
      GetFailureStatus(handle);
      GetChannelStatus(handle);

      CAEN_DGTZ_CloseDigitizer(handle);
    }
    else{
      std::cout << "[ERROR] CAEN_DGTZ_OpenDigitizer " << retcod << std::endl;      
    }
  }

}

