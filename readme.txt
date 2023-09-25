Name: Dang Thien Nguyen
NetID: DXN210021

CS 4348 Project 1

This project simulates a simple computer architecture using C.

Files:
cpu.c - Implements the CPU logic and registers
memory.c - Implements the memory storage
disk.c - Handles loading programs and translation
main.c - Starts the simulation and handles overall flow
registers.h - Contains register definitions

To compile:
The project requires all C files to be compiled together into one executable.

On Linux/Mac:
gcc main.c cpu.c memory.c disk.c -o simulator

On Windows:
gcc main.c cpu.c memory.c disk.c -o simulator.exe

This will produce an executable called "simulator" (or simulator.exe on Windows) that can be run.

To run:
./simulator programfile

For example 
./simulator program_add.txt
./simulator program_if.txt