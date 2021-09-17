#include <stdlib.h>

typedef struct process
{
    int initial_time;
    char* name;
    int factory_id;
    int state; // State -> Ready = 0, Running = 1, Waiting = 2, Finished = 3
    int n_burst;
    int* bursts;
    int index; // en cual cpu burst esta
    int running_time;
    int waiting_time;
    //Statistics
    int times_cpu;
    int interruptions;
    int turnaround_time;
    int response_time;
    int waiting_stat;
    int position;
} Process;

typedef struct queue
{
    Process** process_line;
    int factories[4]; // Numero de procesos en la cola por cada fabrica. Parte {0,0,0,0}
} Queue;

int quantum(int Q, int n, int f);

void rearrange(Process** queue, int limit);

void sort_input(Process** input_list);

void up_the_queue(Process** queue, int limit);

void write_results(Process** process_completed, FILE* output_file, int number_process);