# vsdRiscvSoc
This repository documents my progress in the **VSD RISC-V SoC**

## OBJECTIVE
To successfully complete the initial task of the **VSD RISC-V SoC** by setting up a fully functional RISC-V environment using a prebuilt GCC toolchain, Spike ISA simulator, and Proxy Kernel. The goal is verified by executing a custom uniqueness test program on the simulated RISC-V platform.

## Environment Setup Instructions
# Step 1: Download Required Software
Ubuntu 22.04.5 LTS (Desktop)
🔗[Download ISO (64-bit)](https://releases.ubuntu.com/22.04/ubuntu-22.04.5-desktop-amd64.iso)  
Oracle VirtualBox (for running Ubuntu VM)
🔗[Download VirtualBox for Windows](https://www.virtualbox.org/wiki/Downloads)
# Step 2: Create a Virtual Machine in VirtualBox
After creating the VM, load the downloaded Ubuntu ISO as a startup disk and install Ubuntu normally inside the VM.
# Step 3: Ubuntu Setup (after installation)
* update Ubuntu Packages
* open Terminal (ctrl+alt+T)
* Run this command in your WSL terminal:
```sudo apt-get update```
-This makes sure your Ubuntu system is fresh and error-free before you begin Task-1.

## Task 1 — Install base developer tools 
These are common build prerequisites (compilers, linkers, autotools) and libraries 
required by the RISC‑V simulator, proxy kernel, and other tooling. GTKWaves is included for 
waveform viewing in digital design flows. 
```sudo apt-get install -y git vim autoconf automake autotools-dev curl \ 
libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex \ 
texinfo gperf libtool patchutils bc zlib1g-dev libexpat1-dev gtkwave```








