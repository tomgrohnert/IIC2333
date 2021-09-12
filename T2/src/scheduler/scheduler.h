#include <stdlib.h>

typedef struct process
{
    int pid;
    char* name;
    int factory_id;
    int state; // State -> Ready = 0, Running = 1, Waiting = 2, Finished = 3
    int n_burst;
    int time;
} Process;

int quantum(int Q, int n, int f);