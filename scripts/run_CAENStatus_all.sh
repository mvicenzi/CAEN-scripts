#!/bin/bash

## This script checks the status of CAEN digitizers across all servers.
## This is done by using CAENStatus. 
## Verbosity levels:
## 0: connection/failures check only. No status or legend printed (default)
## 1: prints full board status, software releases and legend
## 2: prints channel-by-channel status and temperatures

verbosity=0
if [ $# -gt 0 ]; then 
  verbosity=$1
fi

for server in icarus-pmt01.fnal.gov icarus-tpc27.fnal.gov icarus-pmt03.fnal.gov icarus-pmt04.fnal.gov;
do

  ssh -Y icarus@$server "~mvicenzi/CAEN-scripts/build/CAENStatus $verbosity"

done
