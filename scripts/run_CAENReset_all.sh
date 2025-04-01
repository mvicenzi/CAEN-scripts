#!/bin/bash

## This script resets CAEN digitizers across all servers.
## This is done by using CAENReset.

for server in icarus-pmt01.fnal.gov icarus-tpc27.fnal.gov icarus-pmt03.fnal.gov icarus-pmt04.fnal.gov; 
do

  ssh icarus@$server "~mvicenzi/CAEN-scripts/build/CAENReset 0 1 2 4 5 6"

done
