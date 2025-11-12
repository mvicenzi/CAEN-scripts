#!/bin/bash

## This script resets CAEN digitizers across all servers.
## This is done by using CAENV1730_Reset.

for server in icarus-pmt02.fnal.gov icarus-pmt03.fnal.gov icarus-pmt04.fnal.gov icarus-pmt05.fnal.gov; 
do

  ssh -Y icarus@$server "~mvicenzi/CAEN-scripts/build/CAENV1730_Reset 0 1 2 4 5 6"

done
