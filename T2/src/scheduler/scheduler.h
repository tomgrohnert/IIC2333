#include <stdlib.h>

typedef struct process
{
    int pid;
    char* name;
    int factory_id;
    int state; // State -> Ready = 0, Running = 1, Waiting = 2, Finished = 3
    int n_burst;
    int* bursts;
    int index; // en cual cpu burst esta
    int running_time; 
} Process;

typedef struct queue
{
    Process** process_line;
    int factories[4]; // Numero de procesos en la cola por cada fabrica. Parte {0,0,0,0}
} Queue;

int quantum(int Q, int n, int f);

void rearrange(Process** queue, int limit);