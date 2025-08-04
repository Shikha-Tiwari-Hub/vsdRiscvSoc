# Task 2 - Prove Your Local RISCV Setup (Run, Disassemble, Decode)
# OBJECTIVE 
This task demonstrates compiling and running RISC-V C programs on Spike, with identity tagging (ProofID, RunID), assembly generation, disassembly, and manual decoding.

# Tools Used
1.Ubuntu 20.04 LTS (VM)
2.`riscv64-unknown-elf-gcc` 8.3.0
   ![WhatsApp Image 2025-08-04 at 19 49 29_e6120b67](https://github.com/user-attachments/assets/a4fe0e9f-51a3-4241-8bc8-c9b9705a4597) 
   
3.`spike pk`
  ![WhatsApp Image 2025-08-04 at 19 58 42_8b5985ca](https://github.com/user-attachments/assets/470ba900-e113-490d-a7de-472684a6094d)

4.`riscv64-unknown-elf-objdump`

# A. Uniqueness mechanism (do this before compiling)
 Set identity variables in your Linux host shell so each build is user/machine specific.
 ```bash
 export U=$(id-un)
 export H=$(hostname-s)
 export M=$(cat /etc/machine-id | head-c 16)
 export T=$(date-u +%Y-%m-%dT%H:%M:%SZ)
 export E=$(date +%s)
```
![WhatsApp Image 2025-08-04 at 12 57 54_1d2f03b6](https://github.com/user-attachments/assets/09a55e5e-bc09-4a35-b5cb-2301c83db75a)

# B. Common header (save as unique.h)
## step 1 - Open nano editor
```bash
nano unique.h
```
![WhatsApp Image 2025-08-04 at 13 03 44_5a643b3a](https://github.com/user-attachments/assets/e303d853-a57b-4aa6-b0b1-35c5a899ee69)

## step 2 - Create  
📁**File**: [unique.h](./unique.h)

![WhatsApp Image 2025-08-04 at 13 00 58_5bc9a712](https://github.com/user-attachments/assets/67e1683c-d3c8-437c-93ef-df5307cb2cba)
To **save** the file: Press Ctrl + O then Press Enter, To **exit**: Press Ctrl + X

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
![WhatsApp Image 2025-08-04 at 13 07 58_1b43a1cb](https://github.com/user-attachments/assets/167e50f6-3c01-44fd-ab26-d6339851c468)
![WhatsApp Image 2025-08-04 at 13 07 30_a65fda6b](https://github.com/user-attachments/assets/43f14275-c75c-4764-9965-52d90e136850)

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
![factorial_output](https://github.com/user-attachments/assets/5bb45f52-3a4a-4c60-a354-602282efaa8f)

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
![factorial_main_asm](https://github.com/user-attachments/assets/44b90077-12eb-4010-aae3-57dee39a217f)

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

#  Programs to implement - descriptions for the other 3 programs  
## 2. max_array.c
Find the maximum value in a static integer array using a simple for loop.
```bash
#include "unique.h"
 int main(void){
 uniq_print_header("max_array");
 int a[] = {42,-7,19,88,3,88,5,-100,37};
 int n = sizeof(a)/sizeof(a[0]), max=a[0];
 for(int i=1;i<n;i++) if(a[i]>max) max=a[i];
 printf("Array length=%d, Max=%d\n", n, max);
 return 0;
 }
```
![WhatsApp Image 2025-08-04 at 13 11 19_71217351](https://github.com/user-attachments/assets/eddae24c-f1bd-440a-831d-524191a64e1a)
![WhatsApp Image 2025-08-04 at 13 11 06_7bc28d29](https://github.com/user-attachments/assets/5e52486b-a844-4553-8ab4-6f49176cb942)
![max_array_output](https://github.com/user-attachments/assets/77a9d722-5cdd-4e6a-8fc6-9ff06f9bf603)
![WhatsApp Image 2025-08-03 at 12 37 45_6435873d](https://github.com/user-attachments/assets/30625673-caa7-4185-bf68-9a7ac9761fb0)
![WhatsApp Image 2025-08-04 at 13 17 02_93670c95](https://github.com/user-attachments/assets/8b5c0dc8-fbab-440a-a03c-aea3a341ae48)

## 3. bitops.c
Perform basic bitwise operations: AND, OR, XOR, NOT, left shift, right shift.
```bash
 #include "unique.h"
 int main(void){
 uniq_print_header("bitops");
 unsigned x=0xA5A5A5A5u, y=0x0F0F1234u;
 printf("x&y=0x%08X\n", x&y);
 printf("x|y=0x%08X\n", x|y);
 printf("x^y=0x%08X\n", x^y);
 printf("x<<3=0x%08X\n", x<<3);
 printf("y>>2=0x%08X\n", y>>2);
 return 0;
 }
```
![WhatsApp Image 2025-08-04 at 13 22 33_16399ef1](https://github.com/user-attachments/assets/85d8f98e-8d2a-4104-909a-c17606ef8996)
![WhatsApp Image 2025-08-04 at 13 22 14_60d09f5d](https://github.com/user-attachments/assets/a9f73d77-aa85-492d-b892-5aa4d2052440)
![WhatsApp Image 2025-08-04 at 12 32 53_85da4b78](https://github.com/user-attachments/assets/717eda37-b286-47ae-bbe0-c36f0b79e757)
![bitops_main_asm](https://github.com/user-attachments/assets/bdc8f209-e86c-4e76-8bba-0269706d33ea)
![WhatsApp Image 2025-08-04 at 13 24 12_0e7ee6ea](https://github.com/user-attachments/assets/b9891621-ee2f-4761-83b3-b6c6a2f5fc58)

## 4. bubble_sort.c
Sort a static integer array using bubble sort and print the sorted output.
```bash
 #include "unique.h"
 void bubble(int *a,int n){ for(int i=0;i<n-1;i++) for(int j=0;j<n-1-i;j++) if(a[j]>a[j
 +1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;} }
 int main(void){
 uniq_print_header("bubble_sort");
 int a[]={9,4,1,7,3,8,2,6,5}, n=sizeof(a)/sizeof(a[0]);
 bubble(a,n);
 printf("Sorted:"); for(int i=0;i<n;i++) printf(" %d",a[i]); puts("");
 return 0;
 }
```
![WhatsApp Image 2025-08-04 at 13 25 28_85133388](https://github.com/user-attachments/assets/a1494208-b4e4-4e31-8113-fc455ed5d076)
![WhatsApp Image 2025-08-04 at 13 25 49_411a7763](https://github.com/user-attachments/assets/8b45a6be-2790-46fb-b0dc-f0fad4d2bea4)
![bubble_sort_output](https://github.com/user-attachments/assets/e7176f3f-8f54-45fe-8bc1-7bff37db6954)
![bubble_sort_main_asm](https://github.com/user-attachments/assets/924f7a09-4704-43cd-961b-e76f92a67bfe)
![WhatsApp Image 2025-08-04 at 13 27 11_b04f43c7](https://github.com/user-attachments/assets/f0187190-9f97-4a24-93f2-ace56a7c01fc)

# 🔁 Common Steps for All Programs
The same commands were used for all 4 programs:  
*`factorial.c`, `max_array.c`, `bitops.c`, and `bubble_sort.c`.*
**To use them, just replace `filename` with the name of the program**




 
