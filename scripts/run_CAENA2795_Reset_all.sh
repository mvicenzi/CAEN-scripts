#!/bin/bash

## This script resets CAEN digitizers across all servers.
## This is done by using CAENA2795_Reset.

for server in icarus-tpc{01..23}.fnal.gov icarus-tpc25.fnal.gov; 
do

  ssh -Y icarus@$server "~mvicenzi/CAEN-scripts/build/CAENA2795_Reset 0 1 2 3 4 5 6 7"

done
