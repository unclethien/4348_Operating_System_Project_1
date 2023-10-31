#include <stdio.h>
#include "scheduler.h"
#include "registers.h"

extern void load_prog(char*, int);
extern int clock_cycle();
extern void mem_print();
extern void mem_init();


int main(int argc, char *argv[])
{

    // Load programs
    load_programs("programs.txt"); 
    
    int cycles = 0;
    int status;
    
    do 
    {
        status = clock_cycle();
        
        cycles++;
        
        schedule(cycles, status);
        
    } while(schedule(cycles, status));

    // Print final memory
    for(int i=0; i<20; i++) {
        printf("mem[%d] = %d\n", i, mem_read(i)[0]); 
    }

    return 0;

}