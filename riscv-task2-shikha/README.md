# Task 2 - Prove Your Local RISCV Setup (Run, Disassemble, Decode)
# OBJECTIVE 
This task demonstrates compiling and running RISC-V C programs on Spike, with identity tagging (ProofID, RunID), assembly generation, disassembly, and manual decoding.

# A. Uniqueness mechanism (do this before compiling)
 Set identity variables in your Linux host shell so each build is user/machine specific.
 ```bash
 export U=$(id-un)
 export H=$(hostname-s)
 export M=$(cat /etc/machine-id | head-c 16)
 export T=$(date-u +%Y-%m-%dT%H:%M:%SZ)
 export E=$(date +%s)
```
# Common header (save as unique.h)
