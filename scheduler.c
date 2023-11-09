#include <stdio.h>
#include <stdlib.h>
#include "registers.h"

#define MAX_PROCESSES 1024
#define TIME_QUANTUM 10


struct Node* ready_queue = NULL;
struct PCB process_table[MAX_PROCESSES];
int current_process_index = -1;
extern struct register_struct context_switch(struct register_struct new_vals);

void new_process(int base, int size) {
    // struct PCB pcb = (struct PCB) malloc(sizeof(struct PCB));
    struct PCB pcb;
    pcb.pid = current_process_index + 1;
    pcb.size = size;
    pcb.base = base;
    pcb.registers.registers[Base] = base;
    pcb.registers.registers[PC] = 0;

    process_table[current_process_index + 1] = pcb;
    current_process_index++;

    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->pcb = pcb;
    new_node->next = NULL;

    if (ready_queue == NULL) {
        ready_queue = new_node;
        context_switch(pcb.registers);
    } else {
        struct Node* current = ready_queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void next_process() {
    // if (ready_queue == NULL) {
    //     return;
    // }
    struct Node* current = ready_queue;
    ready_queue = ready_queue->next;
    current->next = NULL;
    if (ready_queue == NULL) {
        ready_queue = current;
    } else {
        struct Node* temp = ready_queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = current;
    }
}

// void context_switch() {
//     if (ready_queue == NULL) {
//         return;
//     }
//     PCB* current_process = ready_queue->pcb;
//     for (int i = 0; i < 10; i++) {
//         current_process->registers[i] = clock_cycle(current_process->registers[i]);
//     }
//     next_process();
// }

int schedule(int cycle_num, int process_status) {
    if (ready_queue == NULL) { 
        return 0;
    }
    if (cycle_num == 10) {
        next_process();

        struct Node* temp = ready_queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->pcb.registers = context_switch(ready_queue->pcb.registers);
    }

    if (process_status == 0) {
        struct Node* current = ready_queue;
        // struct Node* previous = NULL;
        // while (current != NULL) {
        //     if (current->pcb.pid == current_process_index) {
        //         if (previous == NULL) {
        //             ready_queue = current->next;
        //         } else {
        //             previous->next = current->next;
        //         }
        //         // free(current->pcb);
        //         free(current);
        //         current_process_index--;
        //         break;
        //     }
        //     previous = current;
        //     current = current->next;
        // }
        if (current->next == NULL) {
            // free(ready_queue);
            return 0;
        }
        else{
            ready_queue = ready_queue->next;
            // free(current);
            context_switch(ready_queue->pcb.registers); 
        }
    }
    return 1;
}
