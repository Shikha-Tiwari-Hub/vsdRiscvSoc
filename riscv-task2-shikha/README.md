# Task 2 - Prove Your Local RISCV Setup (Run, Disassemble, Decode)
# OBJECTIVE 
This task demonstrates compiling and running RISC-V C programs on Spike, with identity tagging (ProofID, RunID), assembly generation, disassembly, and manual decoding.

# Tools Used
1. Ubuntu 20.04 LTS (VM)
2. `riscv64-unknown-elf-gcc` 8.3.0
3. `spike pk`
4. `riscv64-unknown-elf-objdump`

# A. Uniqueness mechanism (do this before compiling)
 Set identity variables in your Linux host shell so each build is user/machine specific.
 ```bash
 export U=$(id-un)
 export H=$(hostname-s)
 export M=$(cat /etc/machine-id | head-c 16)
 export T=$(date-u +%Y-%m-%dT%H:%M:%SZ)
 export E=$(date +%s)
```
# B. Common header (save as unique.h)
📁**File**: 
To **save** the file: Press Ctrl + O then Press Enter \ To **exit**: Press Ctrl + X
# C.  Programs to implement
Each program must include unique.h and print the header first.
## 1. factorial.c
Recursive calculation of factorial of 12 using ```unsigned long long``` with identity print.
```bash
 #include "unique.h"
 static unsigned long long fact(unsigned n){ return (n<2)?1ULL:n*fact(n-1); }
 int main(void){
 uniq_print_header("factorial");
 unsigned n = 12;
 printf("n=%u, n!=%llu\n", n, fact(n));
 return 0;
 }
```
*Note: All steps (compilation, spike execution, `.s` generation, disassembly, and instruction decoding) were completed **program-by-program**, not all at once.*
*This ensured:*
- Identity-tagged builds were correct and visible per program
- Output screenshots and disassemblies matched the compiled source
- Decoding stayed organized with each program’s context
  
# D. Common Compile & Run Steps (Used for All)
## step 1 - **Compile example:**
```bash
 riscv64-unknown-elf-gcc-O0-g-march=rv64imac-mabi=lp64 \-DUSERNAME="\"$U\""-DHOSTNAME="\"$H\""-DMACHINE_ID="\"$M\"" \-DBUILD_UTC="\"$T\""-DBUILD_EPOCH=$E \
 factorial.c-o factorial
```
## step 2 -  Run on Spike:
```bash
 spike pk ./factorial
```
# E. Produce assembly and disassembly
## step 1 -  Assembly (.s):
```bash
 riscv64-unknown-elf-gcc-O0-S factorial.c-o factorial.s
```
## step 2 - Disassembly of main only:
```bash
riscv64-unknown-elf-objdump-d ./factorial | sed-n '/<main>:/,/^$/p' | tee
 factorial_main_objdump.txt
```
# F. Instruction decoding (integer type)
 Decode at least 5 RISC-V integer instructions from your `.s` or `.objdump`. Use the following
 format in a markdown file:
 ## step 1 - run command
 ```bash
nano Instruction_decoding.md
```
## step 2 - For each program, selected 5 instructions from the ```main()``` disassembly.
- All decoded instructions are stored in ```instruction_decoding.md```
- Included:
   - Opcode, funct3, funct7
   - Register Fields (rd, rs1, rs2)
   - Binary hex value

![WhatsApp Image 2025-08-04 at 00 24 52_0c141e41](https://github.com/user-attachments/assets/df92fc6b-ec57-455f-b571-62bac6c4d558)






 
