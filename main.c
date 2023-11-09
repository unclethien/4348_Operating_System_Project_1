
#include <stdio.h>
#include "registers.h"

extern void load_programs(char[]);
extern void load_prog(char*, int);
extern int clock_cycle();
extern void mem_print();
extern void mem_init();
int schedule(int, int );

int main(int argc, char *argv[])
{
    // Check command line arguments
    if(argc < 2) 
    {
        printf("Usage: ./main programfile\n");
        return 1;
    }

    char* prog_file = argv[1];
    
    // Initialize memory
    mem_init();
    
    // Load all programs
    load_programs(prog_file);
    
    // // Print memory after load
    // mem_print();

    // // Set registers for program 1
    // registers[Base] = START_ADDR; 
    // registers[PC] = 0;
    
    // // Initialize scheduler
    // init_scheduler();
    
    // Run clock cycles
    int cycle_count = 0;
    int run = 1;
    while(schedule(cycle_count, clock_cycle()))
    {
        
        cycle_count++;
        
        if(cycle_count > 10){
            cycle_count = 1;
        }

        // run = clock_cycle();    
        // schedule(run, cycle_count);
        
    }
    
    // Print final memory contents
    mem_print();
    
    // // Print first 20 locations in memory
    // printf("First 20 locations in memory:\n");
    // for(int i = 0; i < 20; i++)
    // {
    //     int* memory = mem_read(i);
    //     printf("Location %d: %d %d\n", i, memory[0],  memory[1]);
    // }
    // printf("\n");
    
    return 0;
}