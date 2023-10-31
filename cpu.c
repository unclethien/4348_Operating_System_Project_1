#include <stdio.h>
#include "registers.h"

extern int registers[7];

extern int* mem_read(int);
extern void mem_write(int, int*);

int data[2];

void fetch_instruction(int addr)
{
    int* instruct = mem_read(addr);
    registers[IR0] = instruct[0];
    registers[IR1] = instruct[1];
}

void execute_instruction()
{
    int data[2];
    data[0] = registers[MBR];
    switch(registers[IR0])
    {
        case 0: //exit
            break;
        case 1: //load_const
            registers[AC] = registers[IR1];
            break;
        case 2: //move_from_mbr
            registers[AC] = registers[MBR];
            break;
        case 3: //move_from_mar
            registers[AC] = registers[MAR];
            break;
        case 4: //move_to_mbr
            registers[MBR] = registers[AC];
            break; 
        case 5: //move_to_mar
            registers[MAR] = registers[AC];
            break;
        case 6: //load_at_addr
            registers[MBR] = mem_read(registers[MAR])[0];
            break;
        case 7: //write_at_addr
            data[0] = 0;
            data[1] = registers[MBR];
            mem_write(registers[MAR], data);
            break;
        case 8: //add
            registers[AC] += registers[MBR];
            break;
        case 9: //multiply
            registers[AC] *= registers[MBR];
            break;
        case 10: //and
            if (registers[MBR] != 0 && registers[AC] != 0)
            {
                registers[AC] = 1;
            }
            else
            {
                registers[AC] = 0;
            }
            registers[MBR] = registers[MBR] && AC;
            break;
        case 11: //or
            if (registers[MBR] != 0 || registers[AC] != 0)
            {
                registers[AC] = 1;
            }
            else
            {
                registers[AC] = 0;
            }
            break;
        case 12: //ifgo
            
            if(registers[AC] != 0)
            {
                registers[PC] = registers[IR1] - 1;
            }
            break;
        case 13: //sleep
            break;
        default:
            printf("Invalid opcode: %d\n", IR0);
            break;
        
    }
}

int mem_address(int l_addr)
{
    return registers[Base] + l_addr;
}

int clock_cycle()
{
    fetch_instruction(mem_address(registers[PC]));
    

    execute_instruction();
    registers[PC]++;
    if(registers[IR0]==0)
    {
        return 0;
    }
    return 1;
}

// Struct to hold register values
typedef struct 
{
  int registers[7]; 
} register_struct;

// New context switch function
register_struct context_switch(register_struct new_vals) 
{

  register_struct old_vals;
  
  // Save old register values
  for(int i=0; i<7; i++) 
  {
    old_vals.registers[i] = registers[i];
  }

  // Load new register values
  for(int i=0; i<7; i++) 
  {
    registers[i] = new_vals.registers[i];
  }

  return old_vals;

}