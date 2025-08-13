#!/bin/bash

## This script checks the status of CAEN digitizers across all servers.
## This is done by using CAENA2795_Status. 
## Verbosity levels:
## 0: connection/failures check only. No status or legend printed
## 1: prints full board status (default)
## 2: prints software releases, legend and temperatures

verbosity=0
if [ $# -gt 0 ]; then 
  verbosity=$1
fi

for server in icarus-tpc{01..23}.fnal.gov icarus-tpc25.fnal.gov;
do

  ssh -Y icarus@$server "~mvicenzi/CAEN-scripts/build/CAENA2795_Status $verbosity"

done
