# CAEN-scripts
Scripts to check status and perform simple operations on CAEN V1730 and A2795 digitizers.

## V1730
* `CAENV1730_BoardInfo.cc` prints the serial number, firmware and driver releases of V1730 digitizers and their A3818/A5818 VME bridges.
* `CAENV1730_Status.cc` prints the acquisition status, board failure status and channel status of V1730 digitizers. 
* `CAENV1730_Reset.cc` sends a software reset signal to V1730 digitizers. All internal registers and states are restored to default values. Data buffers are cleared.
* `CAENV1730_ReadRegister.cc` prints the values of the list of V1730 registers provided in input.
* `CAENV1730_ClockOut.cc` configures V1730 digitizers to route their internal clocks to TRGOUT for diagnosis.
* `CAENV1730_ClockPhaseOut.cc` configures V1730 digitizers to route their internal clock phases to TRGOUT for diagnosis.

In addition, the following scripts can be used to run the pre-compiled executable on all PMT servers at once:
* `run_CAENV1730_Status_all.sh`
* `run_CAENV1730_Reset_all.sh`

## A2795
* `CAENA2795_BoardInfo.cc` prints firmware and driver releases of A2795 digitizers and their A3818/A5818 VME bridges.
* `CAENA2795_Status.cc` prints the statuts and temperatures of A2795 digitizers. 
* `CAENA2795_Reset.cc` sends a software reset signal to A2795 digitizers. All internal registers and states are restored to default values. Data buffers are cleared.

In addition, the following scripts can be used to run the pre-compiled executable on all TPC servers at once:
* `run_CAENA2795_Status_all.sh`
* `run_CAENA2795_Reset_all.sh`

## A3818/A5818
* `CAENVME_BridgeReset.cc` sends a software reset signal to the A3818/A5818 VME bridge.

## Instructions
`CAENDigitizer`, `CAENComm` and `CAENVMElib` libraries are required. 
These are available on ICARUS DAQ clusters after setting up a DAQ development area with the usual instructions.

The scripts require a standard `cmake` + `make` build:
```
cmake -B /path/to/build/dir -S /path/to/source/dir
cd /path/to/build/dir
make
```
