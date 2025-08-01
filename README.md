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
-This makes sure your Ubuntu system is fresh and error-free before you begin Task-1.

# Task 1 - Install base developer tools 
These are common build prerequisites (compilers, linkers, autotools) and libraries 
required by the RISC‑V simulator, proxy kernel, and other tooling. GTKWaves is included for 
waveform viewing in digital design flows. 
```bash
sudo apt-get install -y git vim autoconf automake autotools-dev curl \ 
libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex \ 
texinfo gperf libtool patchutils bc zlib1g-dev libexpat1-dev gtkwave
```
# Task 2 - Create a Workspace Directory
Created a new directory named 'riscv_toolchain' under the home directory to store all RISC-V related files, toolchains, and build outputs. 
```bash
cd 
pwd=$PWD 
mkdir -p riscv_toolchain 
cd riscv_toolchain
```
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
# Task 4 -  Add toolchain to PATH (current shell + persistent)
## step-1 Temporarily set the path
Command (current shell):
```bash
export PATH=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH
```
## step-2 Add it to PATH permanently
Command (persistent for new terminals): 
```bash
echo 'export PATH=$HOME/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH' >> ~/.bashrc 
source ~/.bashrc
```
# Task 5 - Install Device Tree Compiler (DTC)
Some RISC-V simulators and tools rely on it - so it's required as a supporting tool.
```bash
sudo apt-get install -y device-tree-compiler
```
# Task 6 - Build and install Spike (RISC‑V ISA simulator) 
## step-1: Clone the Spike Repository
```bash
cd $pwd/riscv_toolchain 
git clone https://github.com/riscv/riscv-isa-sim.git 
cd riscv-isa-sim
```
## step-2: Build Spike
```bash
mkdir -p build && cd build 
../configure --prefix=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc
8.3.0-2019.08.0-x86_64-linux-ubuntu14 
make -j$(nproc) 
sudo make install
```
# Task 7 - Build and install the RISC‑V Proxy Kernel (riscv-pk)
The Proxy Kernel is a minimal kernal required to run C programs on Spike simulator.
## step-1: Clone the Proxy Kernel repository
```bash
cd $pwd/riscv_toolchain 
git clone https://github.com/riscv/riscv-pk.git 
cd riscv-pk
```
## step-2: Build pk
```bash
mkdir -p build && cd build 
../configure --prefix=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc
8.3.0-2019.08.0-x86_64-linux-ubuntu14 --host=riscv64-unknown-elf 
make
sudo make install
```
# Task 8 - Ensure the cross bin directory is in PATH
## step-1: Temporarily set the path
Command (current shell):
```bash
export PATH=$pwd/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH
```
## step-2: Add it to PATH permanently
Command (persistent for new terminals): 
```bash
echo 'export PATH=$HOME/riscv_toolchain/riscv64-unknown-elf-gcc-8.3.0
2019.08.0-x86_64-linux-ubuntu14/bin:$PATH' >> ~/.bashrc 
source ~/.bashrc
```
# Task 9 -  (Optional) Install Icarus Verilog
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
## step-3:  Create unique_test.c 
🗂️ **File:** [`unique_test.c`](./unique_test.c)
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
![Unique Test Output](unique_test_output_shikha.png)







