# vsdRiscvSoc
This repository documents my progress in the **VSD RISC-V SoC**, including setup steps, weekly tasks, unique C test, and output verification.

# OBJECTIVE
To successfully complete the initial task of the **VSD RISC-V SoC** by setting up a fully functional RISC-V environment using a prebuilt GCC toolchain, Spike ISA simulator, and Proxy Kernel. The goal is verified by executing a custom uniqueness test program on the simulated RISC-V platform.
# Prerequisites
1.  Ubuntu 20.04 or later (Linux environment recommended).
2.  Do **not** open or mount the Ubuntu ISO manually — it's only needed during OS installation.
3.  Use the terminal inside your installed Ubuntu system for all steps below.

# Environment Setup Instructions
## step 1: Download Required Software
Ubuntu 22.04.5 LTS (Desktop)\
🔗[Download ISO (64-bit)](https://releases.ubuntu.com/22.04/ubuntu-22.04.5-desktop-amd64.iso)\
Oracle VirtualBox (for running Ubuntu VM)\
🔗[Download VirtualBox for Windows](https://www.virtualbox.org/wiki/Downloads)
## step 2: Create a Virtual Machine in VirtualBox
After creating the VM, load the downloaded Ubuntu ISO as a startup disk and install Ubuntu normally inside the VM.
## step 3: Ubuntu Setup (after installation)
* update Ubuntu Packages
* open Terminal (ctrl+alt+T)
* Run this command in your WSL terminal:
```sudo apt-get update```\
![WhatsApp Image 2025-08-02 at 12 26 49_d17108ca](https://github.com/user-attachments/assets/44bab3a0-62c9-4263-8721-9ff99800c4b0)

-This makes sure your Ubuntu system is fresh and error-free before you begin Task-1.

# Task 1 - RISC-V Toolchain Setup Tasks & Uniqueness Test 

# Task 1 - Install base developer tools 
These are common build prerequisites (compilers, linkers, autotools) and libraries 
required by the RISC‑V simulator, proxy kernel, and other tooling. GTKWaves is included for 
waveform viewing in digital design flows. 
```bash
sudo apt-get install -y git vim autoconf automake autotools-dev curl \ 
libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex \ 
texinfo gperf libtool patchutils bc zlib1g-dev libexpat1-dev gtkwave
```
![WhatsApp Image 2025-08-02 at 12 50 15_1452b350](https://github.com/user-attachments/assets/7b3a0da6-f2b9-41f7-a2de-1961a8457164)

If you see ```E: Unable to locate package``` for ```libmpc-dev``` or ```texinfo```, just install them individually:
```bash
sudo apt install libmpc-dev
```
```bash
sudo apt install texinfo
```
![WhatsApp Image 2025-08-02 at 12 50 39_27c4b667](https://github.com/user-attachments/assets/b3e64062-df3c-488a-9a3a-f4edbc636853)

# Task 2 - Create a Workspace Directory
Created a new directory named 'riscv_toolchain' under the home directory to store all RISC-V related files, toolchains, and build outputs. 
```bash
cd 
pwd=$PWD 
git clone https://github.com/riscv/riscv-gnu-toolchain riscv_toolchain
cd riscv_toolchain
./configure --prefix=/opt/riscv
make
```
![WhatsApp Image 2025-08-10 at 12 23 17_0819cb29](https://github.com/user-attachments/assets/bec101fc-81ad-4f34-bb38-4ba4bdd10c86)
![WhatsApp Image 2025-08-10 at 12 18 15_8547ea85](https://github.com/user-attachments/assets/83de5114-d937-41f8-b012-b3b8c021ed55)

# Task 3-Get a prebuilt RISC‑V GCC toolchain
This Provides riscv64-unknown-elf-gcc (newlib) to compile bare‑metal/user‑space RISC‑V 
programs. Using a prebuilt toolchain avoids a long source build. 
```bash
wget "https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc
8.3.0-2019.08.0-x86_64-linux-ubuntu14.tar.gz"
```
```bash
tar -xvzf riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux
ubuntu14.tar.gz
```
![WhatsApp Image 2025-08-02 at 12 55 03_7f189116](https://github.com/user-attachments/assets/d3518b60-30a8-44a4-9a0e-f9d61f85c052)


# Task 4 -  Add toolchain to PATH (current shell + persistent)
## step-1 Temporarily set the path
Command (current shell):
```bash
export PATH=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH
```
![WhatsApp Image 2025-08-02 at 11 37 33_0e213008](https://github.com/user-attachments/assets/b9c1e254-caa6-4bee-b34b-26377fbb0231)

## step-2 Add it to PATH permanently
Command (persistent for new terminals): 
```bash
echo 'export PATH=$HOME/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH' >> ~/.bashrc 
source ~/.bashrc
```
![WhatsApp Image 2025-08-02 at 11 38 11_7e3c2eec](https://github.com/user-attachments/assets/bd3bb64e-97e7-4a9d-907b-c39eb11962ab)

# Task 5 - Install Device Tree Compiler (DTC)
Some RISC-V simulators and tools rely on it - so it's required as a supporting tool.
```bash
sudo apt-get install -y device-tree-compiler
```
![WhatsApp Image 2025-08-02 at 12 27 10_ee552365](https://github.com/user-attachments/assets/8171c44e-3145-4771-b091-a5ca980322f9)

# Task 6 - Build and install Spike (RISC‑V ISA simulator) 
## step-1: Clone the Spike Repository
```bash
cd $pwd/riscv_toolchain 
git clone https://github.com/riscv/riscv-isa-sim.git 
cd riscv-isa-sim
```
![WhatsApp Image 2025-08-10 at 12 24 41_68f5ba64](https://github.com/user-attachments/assets/4ff3d07a-8433-43db-a306-4179c350c12a)

## step-2: Build Spike
```bash
mkdir -p build && cd build 
../configure --prefix=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc
8.3.0-2019.08.0-x86_64-linux-ubuntu14 
make -j$(nproc) 
sudo make install
```
![WhatsApp Image 2025-08-02 at 12 58 26_1c5847b2](https://github.com/user-attachments/assets/aa66f40e-299b-41f5-bba7-cce424a1125a)
![WhatsApp Image 2025-08-02 at 12 58 52_cdd0627a](https://github.com/user-attachments/assets/b11eb94d-2bc3-4440-83b3-8c6b6ffee3e7)

# Task 7 - Build and install the RISC‑V Proxy Kernel (riscv-pk)
The Proxy Kernel is a minimal kernal required to run C programs on Spike simulator.
## step-1: Clone the Proxy Kernel repository
```bash
cd $pwd/riscv_toolchain 
git clone https://github.com/riscv/riscv-pk.git 
cd riscv-pk
```
![WhatsApp Image 2025-08-02 at 13 08 56_909d823e](https://github.com/user-attachments/assets/80dcc7a8-2180-4ae3-bb3d-eed6b315e218)

## step-2: Build pk
```bash
mkdir -p build && cd build 
../configure --prefix=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc-
8.3.0-2019.08.0-x86_64-linux-ubuntu14 --host=riscv64-unknown-elf 
make
sudo make install
```
![WhatsApp Image 2025-08-02 at 11 45 10_46457e10](https://github.com/user-attachments/assets/42667435-9c3e-4277-9014-5aea3c8d6933)
![WhatsApp Image 2025-08-02 at 11 46 32_ad3dba4b](https://github.com/user-attachments/assets/0074b644-10d8-424a-b7c9-67625356f46a)
![WhatsApp Image 2025-08-02 at 11 49 51_4fd51598](https://github.com/user-attachments/assets/5d62cb06-6dc8-4823-8427-000d92b7885a)

# Task 8 - Ensure the cross bin directory is in PATH
## step-1: Temporarily set the path
Command (current shell):
```bash
export PATH=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH
```
![WhatsApp Image 2025-08-02 at 11 50 44_ec0625bb](https://github.com/user-attachments/assets/bb0ed8e3-40e6-4582-982e-d0412d3860b1)

## step-2: Add it to PATH permanently
Command (persistent for new terminals): 
```bash
echo 'export PATH=$HOME/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH' >> ~/.bashrc 
source ~/.bashrc
```
![WhatsApp Image 2025-08-02 at 12 27 47_78860880](https://github.com/user-attachments/assets/5ee6333f-9224-4485-8a54-62ce09d5014c)

# Task 9 -  (Optional) Install Icarus Verilog
  For digital design education, you’ll often verify RTL with Icarus Verilog and view
waveforms with GTKWaves. \
This is not required for the C uniqueness test but is part of a 
complete RISC‑V learning toolchain. 
```bash
cd $pwd/riscv_toolchain 
git clone https://github.com/steveicarus/iverilog.git 
cd iverilog 
git checkout --track -b v10-branch origin/v10-branch 
git pull 
chmod +x autoconf.sh
```
![WhatsApp Image 2025-08-04 at 21 33 44_a76a6aec](https://github.com/user-attachments/assets/433d2ff0-e9ae-4caa-9ee1-0a81a71b8661)

```bash
./autoconf.sh 
./configure 
make -j$(nproc) 
sudo make install
```
![WhatsApp Image 2025-08-04 at 21 29 32_d2653eb8](https://github.com/user-attachments/assets/f2197a3c-a64d-41fc-9b68-8e8d228db46a)
![WhatsApp Image 2025-08-04 at 21 29 49_b7495fdd](https://github.com/user-attachments/assets/90922b3c-9a94-470d-95da-7adec089069b)
![WhatsApp Image 2025-08-04 at 21 30 13_77fa6472](https://github.com/user-attachments/assets/d31dfbf6-df45-411a-afc7-cd8b98853cd4)
![WhatsApp Image 2025-08-04 at 21 31 05_91519530](https://github.com/user-attachments/assets/6add7f44-388b-4c38-a4ba-3e6751be0097)
![WhatsApp Image 2025-08-04 at 21 31 19_478d829f](https://github.com/user-attachments/assets/4a583124-9e2a-4ed4-a571-9c57c1a08cfa)

# Task 10 -  Quick sanity checks 
```bash
which riscv64-unknown-elf-gcc 
riscv64-unknown-elf-gcc -v
```
```bash
which spike 
spike --version || spike -h
```
```bash
which pk 
```
![WhatsApp Image 2025-08-02 at 11 57 21_f571cf77](https://github.com/user-attachments/assets/bbf039ec-1498-4dfb-a78d-650703d97692)
*note: Since Spike does not support `--version`, but shows the version in `spike -h`*
![WhatsApp Image 2025-08-02 at 11 57 53_aa6bbaa6](https://github.com/user-attachments/assets/cf3e489f-0ca8-4f1d-9752-ce0b64b1f8e4)

# Final Deliverable: A Unique C Test (Username & Machine Dependent) 
A unique test file was created to verify the correctness of the RISC-V toolchain and environment.  
This test includes username and machine-specific conditions.\
The program computes a 64‑bit FNV‑1a hash of 'USERNAME@HOSTNAME' and prints it.
## step-1: View the file contents in terminal
```bash
cat ~/riscv_toolchain/unique_test.c
```
## step-2: Reopen the file in nano editor
```bash
nano ~/riscv_toolchain/unique_test.c
```
![WhatsApp Image 2025-08-02 at 12 28 48_e4a2851f](https://github.com/user-attachments/assets/222f6440-7b4b-42f1-bd12-df7adea8629f)

## step-3:  Create unique_test.c 
🗂️ **File:** [`unique_test.c`](./unique_test.c) 

![WhatsApp Image 2025-08-02 at 12 28 15_c9a8d2b4](https://github.com/user-attachments/assets/f09e6c68-d532-4594-ba56-3718a6cd2aeb)
To **save the file**: Press ```Ctrl + O``` then Press ```Enter```,
To **exit**: Press ```Ctrl + X```

## step-4: Compile with injected identity and RISC‑V flags
```bash
riscv64-unknown-elf-gcc -O2 -Wall -march=rv64imac -mabi=lp64 \ -DUSERNAME="$(id -un)" -DHOSTNAME="$(hostname -s)" \ 
unique_test.c -o unique_test
```
## step-5:  Run on Spike with the proxy kernel 
```bash
spike pk ./unique_test
```
## Expected Output
When running the unique test program on your machine, the output should look like this:
```bash
RISC-V Uniqueness Check 
User: <your-username> 
Host: <your-hostname> 
UniqueID: 0x<64-bit-hex> 
GCC_VLEN: <number>
```
![WhatsApp Image 2025-08-02 at 12 05 41_44ee91df](https://github.com/user-attachments/assets/8cc67962-ae2b-4e05-b1f8-d6adbfb1820b)



 









