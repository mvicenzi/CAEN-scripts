# CAEN-scripts
Scripts to check status and perform simple operations on CAEN V1730 digitizers.

* `CAENBoardInfo.cc` prints the serial number, firmware and driver releases of V1730 digitizers and their A3818 bridges.
* `CAENStatus.cc` prints the acquisition status, board failure status and channel status of V1730 digitizers. 
* `CAENReset.cc` sends a software reset signal to V1730 digitizers. All internal registers and states are restored to default values.
* `CAENClockOut.cc` configures V1730 digitizers to route their internal clocks to TRGOUT for diagnosis.

## Instructions
`CAENDigitizer`, `CAENComm` and `CAENVMElib` libraries are required. 
These are available on ICARUS DAQ clusters after setting up a DAQ development area with the usual instructions.

The scripts require a standard `cmake` + `make` build:
```
cmake -B /path/to/build/dir -S /path/to/source/dir
cd /path/to/build/dir
make
```
