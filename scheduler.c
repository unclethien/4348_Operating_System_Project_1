#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 1024
#define TIME_QUANTUM 10

typedef struct PCB {
    int pid;
    int size;
    int base;
    int registers[10];
} PCB;

typedef struct Node {
    PCB* pcb;
    struct Node* next;
} Node;

Node* ready_queue = NULL;
PCB* process_table[MAX_PROCESSES];
int current_process_index = -1;

void new_process(int base, int size) {
    PCB* pcb = (PCB*) malloc(sizeof(PCB));
    pcb->pid = current_process_index + 1;
    pcb->size = size;
    pcb->base = base;
    for (int i = 0; i < 10; i++) {
        pcb->registers[i] = 0;
    }
    process_table[current_process_index + 1] = pcb;
    current_process_index++;
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->pcb = pcb;
    new_node->next = NULL;
    if (ready_queue == NULL) {
        ready_queue = new_node;
    } else {
        Node* current = ready_queue;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void next_process() {
    if (ready_queue == NULL) {
        return;
    }
    Node* current = ready_queue;
    ready_queue = ready_queue->next;
    current->next = NULL;
    if (ready_queue == NULL) {
        ready_queue = current;
    } else {
        Node* temp = ready_queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = current;
    }
}

void context_switch() {
    if (ready_queue == NULL) {
        return;
    }
    PCB* current_process = ready_queue->pcb;
    for (int i = 0; i < 10; i++) {
        current_process->registers[i] = clock_cycle(current_process->registers[i]);
    }
    next_process();
}

int schedule(int cycle_num, int process_status) {
    if (ready_queue == NULL) {
        return 0;
    }
    if (cycle_num % TIME_QUANTUM == 0) {
        context_switch();
    }
    if (process_status == 0) {
        Node* current = ready_queue;
        Node* previous = NULL;
        while (current != NULL) {
            if (current->pcb->pid == current_process_index) {
                if (previous == NULL) {
                    ready_queue = current->next;
                } else {
                    previous->next = current->next;
                }
                free(current->pcb);
                free(current);
                current_process_index--;
                break;
            }
            previous = current;
            current = current->next;
        }
    }
    return 1;
}
