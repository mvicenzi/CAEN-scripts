#!/bin/bash

## This script checks the status of CAEN digitizers across all servers.
## This is done by using CAENStatus. Default verbosity is 0 (no legend is shown).

verbosity=0
if [ $# -gt 0 ]; then 
  verbosity=$1
fi

for server in icarus-pmt01.fnal.gov icarus-pmt02.fnal.gov icarus-pmt03.fnal.gov;
do

  ssh icarus@$server "~mvicenzi/CAEN-scripts/build/bin/CAENStatus $verbosity"

done
