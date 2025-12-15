/*-----------------------------------------------------------
File: ErrorUtils.h
Author: M. Vicenzi (mvicenzi@bnl.gov)

Description:
 This file stores CAEN V1730 error codes, and the associated
  helper function for error printing.

-------------------------------------------------------------*/

#include <stdio.h>
#include "CAENDigitizerType.h"
#include "CAENVMEtypes.h"
#include "CAENComm.h"

namespace errors
{

  inline const char *CAEN_DGTZ_ErrorToString(int code)
  {
    switch (code)
    {
    case CAEN_DGTZ_Success:                  return "Success";
    case CAEN_DGTZ_CommError:                return "Communication error";
    case CAEN_DGTZ_GenericError:             return "Generic error";
    case CAEN_DGTZ_InvalidParam:             return "Invalid parameter";
    case CAEN_DGTZ_InvalidLinkType:          return "Invalid link type";
    case CAEN_DGTZ_InvalidHandle:            return "Invalid handle";
    case CAEN_DGTZ_MaxDevicesError:          return "Max devices exceeded";
    case CAEN_DGTZ_BadBoardType:             return "Bad board type";
    case CAEN_DGTZ_BadInterruptLev:          return "Bad interrupt level";
    case CAEN_DGTZ_BadEventNumber:           return "Bad event number";
    case CAEN_DGTZ_ReadDeviceRegisterFail:   return "Register read failed";
    case CAEN_DGTZ_WriteDeviceRegisterFail:  return "Register write failed";
    case CAEN_DGTZ_InvalidChannelNumber:     return "Invalid channel number";
    case CAEN_DGTZ_ChannelBusy:              return "Channel busy";
    case CAEN_DGTZ_FPIOModeInvalid:          return "Invalid FPIO mode";
    case CAEN_DGTZ_WrongAcqMode:             return "Wrong acquisition mode";
    case CAEN_DGTZ_FunctionNotAllowed:       return "Function not allowed";
    case CAEN_DGTZ_Timeout:                  return "Communication timeout";
    case CAEN_DGTZ_InvalidBuffer:            return "Invalid buffer";
    case CAEN_DGTZ_EventNotFound:            return "Event not found";
    case CAEN_DGTZ_InvalidEvent:             return "Invalid event";
    case CAEN_DGTZ_OutOfMemory:              return "Out of memory";
    case CAEN_DGTZ_CalibrationError:         return "Calibration error";
    case CAEN_DGTZ_DigitizerNotFound:        return "Digitizer not found";
    case CAEN_DGTZ_DigitizerAlreadyOpen:     return "Digitizer already open";
    case CAEN_DGTZ_DigitizerNotReady:        return "Digitizer not ready";
    case CAEN_DGTZ_InterruptNotConfigured:   return "IRQ not configured";
    case CAEN_DGTZ_DigitizerMemoryCorrupted: return "Flash memory corrupted";
    case CAEN_DGTZ_DPPFirmwareNotSupported:  return "DPP firmware not supported";
    case CAEN_DGTZ_InvalidLicense:           return "Invalid license";
    case CAEN_DGTZ_InvalidDigitizerStatus:   return "Invalid digitizer status";
    case CAEN_DGTZ_UnsupportedTrace:         return "Unsupported trace";
    case CAEN_DGTZ_InvalidProbe:             return "Invalid probe";
    case CAEN_DGTZ_NotYetImplemented:        return "Not yet implemented";
    default:                                 return "Unknown error";
    }
  }

  // ------------------------------------------------------

  inline const char* CAENComm_ErrorToString(int code)
  {
      switch (code)
      {
          case CAENComm_Success:             return "Success";
          case CAENComm_VMEBusError:         return "VME bus error";
          case CAENComm_CommError:           return "Communication error";
          case CAENComm_GenericError:        return "Generic error";
          case CAENComm_InvalidParam:        return "Invalid parameter";
          case CAENComm_InvalidLinkType:     return "Invalid link type";
          case CAENComm_InvalidHandler:      return "Invalid device handler";
          case CAENComm_CommTimeout:         return "Communication timeout";
          case CAENComm_DeviceNotFound:      return "Device not found";
          case CAENComm_MaxDevicesError:     return "Maximum devices exceeded";
          case CAENComm_DeviceAlreadyOpen:   return "Device already open";
          case CAENComm_NotSupported:        return "Function not supported";
          case CAENComm_UnusedBridge:        return "No boards on this CAEN bridge";
          case CAENComm_Terminated:          return "Communication terminated by device";
          default:                           return "Unknown error";
      }
  }
  
  // ------------------------------------------------------

  inline void PrintErrorV1730(const char *what,
                              int code,
                              bool indent = true,
                              const char *tab = "    ")
  {
    const char *prefix = indent ? tab : "";
    printf("%s\033[5;31m[ERROR]\033[0m %-32s (%d) %s\n",
           prefix,
           what,
           code,
           CAEN_DGTZ_ErrorToString(code));
  }

  // ------------------------------------------------------

  inline void PrintErrorVME(const char *what,
                            CVErrorCodes code,
                            bool indent = true,
                            const char *tab = "    ")
  { 
    const char *prefix = indent ? tab : "";
    printf("%s\033[5;31m[ERROR]\033[0m %-32s (%d) %s\n",
    prefix,
    what,
    code,
    CAENVME_DecodeError(code));
  }

  // ------------------------------------------------------

  inline void PrintErrorComm(const char *what,
                             int code,
                             bool indent = true,
                             const char *tab = "    ")
  {
    const char *prefix = indent ? tab : "";
    printf("%s\033[5;31m[ERROR]\033[0m %-32s (%d) %s\n",
           prefix,
           what,
           code,
           CAENComm_ErrorToString(code));
  }

}
