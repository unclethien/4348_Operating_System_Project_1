#include <stdio.h>

// Global variables
int time_quantum = 10;
int clock_cycles = 0;

// Process Control Block struct
typedef struct PCB 
{
    int pid;
    int size;
    int base;
    register regs; 
} PCB;

// Process table array
PCB process_table[1024];
int next_pid = 1;

// Ready queue as linked list
typedef struct QueueNode 
{
    PCB pcb;
    struct QueueNode* next; 
} 
QueueNode;

QueueNode* readyQueue = NULL;

// Linked list helpers
void add_to_ready_queue(PCB pcb) 
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->pcb = pcb;
    node->next = NULL;
    
    if (readyQueue == NULL) 
    {
        readyQueue = node;
    }
    else 
    {
        QueueNode* cur = readyQueue;
        while (cur->next != NULL) 
        {
            cur = cur->next;
        }
        cur->next = node;
    }
}

// Remove PCB from ready queue
void remove_from_ready_queue(PCB pcb) 
{
  if(readyQueue != NULL && readyQueue->pcb.pid == pcb.pid) 
  {
    QueueNode* temp = readyQueue;
    readyQueue = readyQueue->next;
    free(temp);
    return;
  }
  
  QueueNode* cur = readyQueue;
  while(cur != NULL && cur->next != NULL) 
  {
    if(cur->next->pcb.pid == pcb.pid) 
    {
      QueueNode* temp = cur->next;
      cur->next = cur->next->next;
      free(temp);
      return;
    }
    cur = cur->next; 
  }

}

// Scheduler functions

int schedule(int cycle_num, int process_status) 
{
  clock_cycles += cycle_num;

  if (clock_cycles % time_quantum == 0) 
  {
    next_process();
    context_switch();
  }

  if (process_status == 0) 
  {
    remove_from_ready_queue(running_pcb); 
  }

  return readyQueue == NULL ? 0 : 1;

}

void next_process() 
{
  // Move front PCB to back of ready queue
  if(readyQueue != NULL && readyQueue->next != NULL) 
  {
    QueueNode* temp = readyQueue;
    readyQueue = readyQueue->next;
    QueueNode* cur = readyQueue;
    while(cur->next != NULL) 
    {
      cur = cur->next;
    }
    cur->next = temp;
    temp->next = NULL;
  }
  
}

void new_process(int base, int size) 
{

  // Create PCB
  PCB pcb;
  pcb.pid = next_pid++;
  pcb.size = size; // hardcoded size
  pcb.base = base;
  pcb.regs = init_regs();
  // Add to process table
  process_table[pcb.pid] = pcb;

  // Add to ready queue
  add_to_ready_queue(pcb);


}