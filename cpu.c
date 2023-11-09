#include <stdio.h>
#include "registers.h"

extern int registers[7];

extern int* mem_read(int);
extern void mem_write(int, int*);

int data[2];

typedef struct {
    int AC;
    int IR0;
    int IR1;
    int MBR;
    int MAR;
    int PC;
    int Base;
} register_struct;

register_struct context_switch(register_struct new_vals) {
    register_struct old_vals = {
        .AC = registers[AC],
        .IR0 = registers[IR0],
        .IR1 = registers[IR1],
        .MBR = registers[MBR],
        .MAR = registers[MAR],
        .PC = registers[PC],
        .Base = registers[Base]
    };

    registers[AC] = new_vals.AC;
    registers[IR0] = new_vals.IR0;
    registers[IR1] = new_vals.IR1;
    registers[MBR] = new_vals.MBR;
    registers[MAR] = new_vals.MAR;
    registers[PC] = new_vals.PC;
    registers[Base] = new_vals.Base;

    return old_vals;
}

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
