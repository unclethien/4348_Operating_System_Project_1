#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "registers.h"

// Process control block 
typedef struct PCB {
  int pid;
  int size;
  int base;
  registers regs;
} PCB;

// Function prototypes

int schedule(int, int);
void next_process(); 
void new_process(int, int);
void add_to_ready_queue(PCB);
void remove_from_ready_queue(PCB);

// Global variables
extern PCB process_table[1024]; 
extern int time_quantum;
extern int clock_cycles;

#endif