#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>

#include "../file_manager/manager.h"
#include "./scheduler.h"

int quantum(int Q, int n, int f)
{
  return floor(Q/(n*f));
}

int main(int argc, char **argv)
{
  printf("Hello T2!\n");

  InputFile *file = read_file("input.txt");

  printf("Reading file of length %i:\n", file->len);
  Process** queue = malloc(8*sizeof(Process));
  for (int i = 0; i < file->len; i++)
  {
    char **line = file->lines[i];
    printf(
        "\tProcess %s from factory %s has init time of %s and %s bursts.\n",
        line[0], line[2], line[1], line[3]);
    Process* process = malloc(sizeof(Process));

    process->name = line[0];
    process->pid = i;
    process->factory_id = atoi(line[2]);
    process->state = 0;
    process->n_burst = atoi(line[3]);
    process->time = atoi(line[1]); 

    queue[i] = process;

    // printf("[t = %d] El proceso %s ha pasado a estado %d\n", i, process->name, process->state);
    // sleep(1);
  }
  for (int i = 0; i < 100; i++)
  {
    Process* process = queue[0];
    printf("[t = %d] El proceso %s ha sido creado\n", i, process->name);
    printf("[t = %d] El proceso %s ha pasado a estado READY\n", i, process->name);
    for (int j = 0; j < 5; j++)
    {
      process->state = 1;
      printf("[t = %d] El proceso %s ha pasado a estado RUNNING\n", i, process->name);
      sleep(1);
      i += 1;
    }
    printf("[t = %d] El proceso %s ha pasado a estado READY\n", i, process->name);
    Process* aux = process;
    queue[0] = queue[1];
    queue[1] = aux;
  }
}
