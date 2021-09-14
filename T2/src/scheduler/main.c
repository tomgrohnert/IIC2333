#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "../file_manager/manager.h"
#include "./scheduler.h"

int quantum(int Q, int n, int f)
{
  return floor(Q/(n*f));
}

void rearrange(Process** queue, int limit)
{
  for (int i = 1; i < limit; i++)
  {
    //Process* aux = queue[i-1];
    queue[i-1] = queue[i];
    //queue[i] = aux;
  }
}

Process** sort_input(Process** input_list)
{

}

int main(int argc, char **argv)
{

  // Variables of the main CPU
  Process* aux;
  int quantum_generated;
  bool occupied = false;
  printf("Hello T2!\n");
  

  InputFile *file = read_file("input.txt");

  printf("Reading file of length %i:\n", file->len);
  // Por que esto? no estarias contando tambien aca la primera linea?
  Process** all_processes = malloc((file->len)*sizeof(Process));
  Queue* queue = malloc(sizeof(Queue));
  Process** process_line = malloc(8*sizeof(Process));
  queue->process_line = process_line;
  queue->factories[0] = 0;
  queue->factories[1] = 0;
  queue->factories[2] = 0;
  queue->factories[3] = 0;
  int counter;
  for (int i = 0; i < file->len; i++)
  {
    char **line = file->lines[i];
    printf(
        "\tProcess %s from factory %s has init time of %s and %s bursts.\n",
        line[0], line[2], line[1], line[3]);
    Process* process = malloc(sizeof(Process));

    process->name = line[0];
    process->factory_id = atoi(line[2]);
    process->state = 0;
    process->n_burst = atoi(line[3]);
    process->pid = atoi(line[1]); 
    int* bursts = malloc((process->n_burst*2 - 1)*sizeof(int));
    process->bursts = bursts;
    process->index = 0;
    process->running_time = 0;

    for (int j = 0; j < (atoi(line[3])*2 - 1); j++)
    {
      process->bursts[j] = atoi(line[j+4]);
    }

    all_processes[i] = process;

    if (i < 8)
    {
      queue->process_line[i] = process;
      queue->factories[process->factory_id] += 1;
      counter = i + 1;
    }
  }
  printf("Contador %d\n", counter); // Para saber que proceso hay que agregar a la cola 
  int time = 0;
  bool boolean = true;
  while (boolean) // While existan procesos 
  {
    
    Process* process = queue->process_line[0];
    printf("[t = %d] El proceso %s ha sido creado\n", time, process->name);
    printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, process->name);
    int f = 0;
    // for (int i = 0; i < 4; i++)
    // {
    //   if (queue->factories[i] > 0)
    //   {
    //     f += 1;
    //   }
    // }
    // int q = quantum(100,queue->factories[process->factory_id],f);
    if (occupied == true)
    {
      if (process->bursts[process->index] == process->running_time)
      {
        if (process->index == process->n_burst)
        {
          process->state = 3;
          // Time to be waiting
          process->waiting_time = 0;
          // Set running_time to 0 for next burst
          process->running_time = 0;
          // Low counter
          
          // Need to update queue
          rearrange(queue->process_line, 2);
        }
        else
        {
          // Change state to WAITING
          process->state = 2;
          // Time to be waiting
          process->waiting_time = 0;
          // Set running_time to 0 for next burst
          process->running_time = 0;
          printf("[t = %d] El proceso %s ha pasado a estado WAITING\n", time, process->name);
          // Need to update queue
          rearrange(queue->process_line,2);
          // Put the recent process at the end
          queue->process_line[counter - 1] = process
        }

        // CPU is NOT occupied
        occupied = false;
        // Need to update queue
        rearrange(queue->process_line,2);
        sleep(1);
        time += 1;
      }
    }
    else if (process->bursts[process->index] < q)
    {
      q = process->bursts[process->index];
      process->index += 1; 
    }
    else if (process->bursts[process->index] > q)
    {
      // Guardar el tiempo restante (process->bursts[process->index] - q)
      process->index += 1; 
    }
    printf("Quantum: %d\n",q);
    for (int j = 0; j < q; j++)
    {
      process->state = 1;
      printf("[t = %d] El proceso %s ha pasado a estado RUNNING\n", time, process->name);
      sleep(1);
      time += 1;
    }
    process->running_time += q;
    for (int j = 0; j < process->bursts[process->index]; j++)
    {
      process->state = 2;
      printf("[t = %d] El proceso %s ha pasado a estado WAITING\n", time, process->name);
      sleep(1);
      time += 1;
    }
    process->index += 1; 
    if (process->index > (process->n_burst*2 - 1))
    {
      process->state = 3;
      boolean = false;
      printf("[t = %d] El proceso %s ha pasado a estado FINISHED\n", time, process->name);
    }
    else
    {
      printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, process->name);
    }
    rearrange(queue->process_line,2);
  }
}
