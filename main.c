
#include <stdio.h>
#include "registers.h"
#include "scheduler.h"

extern void load_prog(char*, int);
extern int clock_cycle();
extern void mem_print();
extern void mem_init();

int main(int argc, char *argv[])
{
    #define START_ADDR 4

    // Check command line arguments
    if(argc < 2) 
    {
        printf("Usage: ./main programfile\n");
        return 1;
    }

    char* prog_file = argv[1];
    
    // Initialize memory
    mem_init();
    
    // Load first program
    load_prog(prog_file, START_ADDR);
    
    // Print memory after load
    mem_print();

    // Set registers for program 1
    registers[Base] = START_ADDR; 
    registers[PC] = 0;
    
    // Initialize scheduler
    init_scheduler();
    
    // Run clock cycles
    int cycle_count = 0;
    int run = 1;
    while(run)
    {
        run = clock_cycle();
        cycle_count++;
        schedule(run, cycle_count);
    }
    
    // Print final memory contents
    mem_print();
    
    // Print first 20 locations in memory
    printf("First 20 locations in memory:\n");
    for(int i = 0; i < 20; i++)
    {
        printf("%d ", memory[i]);
    }
    printf("\n");
    
    return 0;
}