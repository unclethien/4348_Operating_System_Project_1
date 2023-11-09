#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registers.h"

//Memory function

extern void mem_write(int, int*);

//Load the program with the name fname, translate it into integer OP Codes, and then store it in memory at address addr

int* translate(char*);

void trim_newline(char* line)
{
    int len = strlen(line);
    if(line[len-1] == '\n')
    {
        line[len-1] = '\0';
    }
}

void load_prog(char *fname, int addr)
{
    FILE *fp = fopen(fname, "r");
    if(fp == NULL)
    {
        printf("Error: Could not open file %s\n", fname);
        return;
    }
    char line[128];

    while (fgets(line, 128, fp) != NULL)
    {
        trim_newline(line);
        
        if (line[0] == '/' && line[1] == '/')
        {
            //Comment line, do nothing
            continue;
        }
        
        int* instruct = translate(line);

        if (instruct != NULL)
        {
            mem_write(addr, instruct);
            addr++;
        }
    }
    fclose(fp);
}

void load_program(int mem_loc, char* prog_file); 
PCB* create_pcb(int mem_loc);
void add_to_ready_queue(PCB* pcb);

void load_programs(char* fname) {

  FILE* fp = fopen(fname, "r");
  if (fp == NULL) {
    printf("Error opening file %s\n", fname);
    return;
  }

  char line[100];
  while (fgets(line, 100, fp)) {

    int mem_loc;
    char prog_file[50];
    sscanf(line, "%d %s", &mem_loc, prog_file);
    
    load_program(mem_loc, prog_file);
    
    PCB* pcb = create_pcb(mem_loc);
    add_to_ready_queue(pcb);
  }

  fclose(fp);
}
//Translate the instruction into an integer OP Code
int* translate(char *line)
{
    char opcode[16];
    int arg;

    sscanf(line, "%s %d", opcode, &arg);

    if(strcmp(opcode, "load_const") == 0)
    {
        return (int[2]){1, arg};
    }
    else if(strcmp(opcode, "move_from_mbr") == 0)
    {
        return (int[2]){2,0};
    }
    else if(strcmp(opcode, "move_from_mar") == 0)
    {
        return (int[2]){3,0};
    }
    else if(strcmp(opcode, "move_to_mbr") == 0)
    {
        return (int[2]){4,0};
    }
    else if(strcmp(opcode, "move_to_mar") == 0)
    {
        return (int[2]){5,0};
    }
    else if(strcmp(opcode, "load_at_addr") == 0)
    {
        return (int[2]){6,0};
    }
    else if(strcmp(opcode, "write_at_addr") == 0)
    {
        return (int[2]){7,0};
    }
    else if(strcmp(opcode, "add") == 0)
    {
        return (int[2]){8,0};
    }
    else if(strcmp(opcode, "multiply") == 0)
    {
        return (int[2]){9,0};
    }
    else if(strcmp(opcode, "and") == 0)
    {
        return (int[2]){10,0};
    }
    else if(strcmp(opcode, "or") == 0)
    {
        return (int[2]){11,0};
    }
    else if(strcmp(opcode, "ifgo") == 0)
    {
        return (int[2]){12,arg};
    }
    else if(strcmp(opcode, "sleep") == 0)
    {
        return (int[2]){13,0};
    }
    else if(strcmp(opcode, "exit") == 0)
    {
        return (int[2]){0,0};
    }
    
    else 
    {
        printf("Error: Invalid instruction: %s\n", line);
        return NULL;
    }

}

