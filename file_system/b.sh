#!/bin/bash
#----------------------------------------
# process B: add 80 to the current balance
# in a cooperative way
#----------------------------------------
flock --verbose /lfs/mtrattner/balance.dat ./update_balance.sh '80'