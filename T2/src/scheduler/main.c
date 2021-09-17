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
  for (int i = 1; i <= limit; i++)
  {
    queue[i-1] = queue[i];
  }
}

void up_the_queue(Process** queue, int limit)
{
  for (int i = 0; i < limit; i++)
  {
    queue[i+1] = queue[i];
  }
}

void sort_input(Process** input_list)
{

}

int main(int argc, char **argv)
{

  // Variables of the main CPU
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
    process->initial_time = atoi(line[1]); 
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
  Process* process;
  while (boolean) // While existan procesos 
  {
    int f = 0;
    //rintf("Time %d, %d\n" , time, occupied);
    for (int i = 0; i < 4; i++)
    {
      if (queue->factories[i] > 0)
      {
        f += 1;
      }
    }
    // int quantum_generated = quantum(10,queue->factories[process->factory_id],f);
    if (occupied == true)
    {
      // Completed burst
      //printf("veamos %d, %d\n", process->bursts[process->index], process->running_time);
      if (process->bursts[process->index] == process->running_time)
      {
        // If finished
        if (process->index + 1 == (2*process->n_burst - 1))
        {
          process->state = 3;
          // Time to be waiting
          process->waiting_time = 0;
          // Set running_time to 0 for next burst
          process->running_time = 0;
          printf("[t = %d] El proceso %s ha pasado a estado FINISHED\n", time, process->name);
          // CPU NOT occupied
          occupied = false;
          // Low counter
          counter -= 1;
          // If all process have finished
          if (counter == 0)
          {
            boolean = false;
            break;
          }
          // Need to update queue
          rearrange(queue->process_line, counter);
        }
        // If goes back to queue
        else
        {
          // Change state to WAITING
          process->state = 2;
          // Get the index of the waiting time
          process->index += 1;
          // Time to be waiting
          process->waiting_time = process->bursts[process->index];
          // Get the index for the next CPU burst
          process->index += 1;
          // Set running_time to 0 for next burst
          process->running_time = 0;
          printf("[t = %d] El proceso %s ha pasado a estado WAITING\n", time, process->name);
          // CPU is NOT occupied
          occupied = false;
          // Need to update queue
          rearrange(queue->process_line, counter - 1);
          // Put the recent process at the end
          queue->process_line[counter - 1] = process;
          // Get new process at the same time
          for (int i = 0; i < counter; i++)
          {
            if (queue->process_line[i]->state == 0)
            {
              process = queue->process_line[i];
              quantum_generated = quantum(100,queue->factories[process->factory_id],f);
              // CPU IS occupied
              occupied = false;
              break;
            }
          }
        }
        //sleep(1);
        //time += 1;
      } 
      else
      {
        // If quantum_generated is over
        if (quantum_generated == process->running_time)
        {
          // Change state to READY
          process->state = 0;
          // Time to be waiting
          process->waiting_time = 0;
          // Set running_time to 0 for next burst
          process->running_time = 0;
          printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, process->name);
          // Need to update queue
          rearrange(queue->process_line, counter - 1);
          // Put the recent process at the end
          queue->process_line[counter - 1] = process;
          for (int i = 0; i < counter; i++)
          {
            if (queue->process_line[i]->state == 0)
            {
              process = queue->process_line[i];
              quantum_generated = quantum(100,queue->factories[process->factory_id],f);
              break;
            }
          }
        } 
       // else
     //   {
      //    sleep(1);
      //    time += 1;
      //    process->running_time += 1;
       // }
      }
     // for (int i = 0; i < counter; i++)
    //  {
    //    if (queue->process_line[i]->state == 2)
    //    {
       //   queue->process_line[i]->waiting_time -= 1;
     //     // If the process waiting time is up then is READY
     //     if (queue->process_line[i]->waiting_time == 0)
     //     {
     //       queue->process_line[i]->state = 0;
        //    printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, queue->process_line[i]->name);
       //   }
       // }
     // }
     process->running_time += 1;
    } 
    //else
    //{
      //bool process_found = false;
      //while(!process_found)
      //{
     //   for (int i = 0; i < counter; i++)
     //   {
       //   if (queue->process_line[i]->state == 0 && queue->process_line[i]->initial_time <= time)
        //  {
        //    process = queue->process_line[i];
        //    process->state = 1;
            // Adjust the queue so it can be rearrange after
        //    up_the_queue(queue->process_line, i);
         //   if (process->index == 0 && process->running_time == 0)
         //   {
         //     printf("[t = %d] El proceso %s ha sido CREADO\n", time, process->name);
         //   }
          //  printf("[t = %d] El proceso %s ha pasado a estado RUNNING\n", time, process->name);
          //  quantum_generated = quantum(100,queue->factories[process->factory_id],f);
            //process_found = true;
          //  occupied = true;
            //break;
         // }
        // if (queue->process_line[i]->state == 2)
           // {
           //   queue->process_line[i]->waiting_time -= 1;
              // If the process waiting time is up then is READY
            //  if (queue->process_line[i]->waiting_time == 0)
             //// {
             //   queue->process_line[i]->state = 0;
             //   printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, queue->process_line[i]->name);
             // }
            //}
        //}
        // If there is no process to run
        //if (!process_found)
        //{
          //sleep(1);
          //time += 1;
          // Iterate to check if there is any process waiting to substract that time
          //for (int i = 0; i < counter; i++)
          //{
           // if (queue->process_line[i]->state == 2)
            //{
              //queue->process_line[i]->waiting_time -= 1;
              // If the process waiting time is up then is READY
              //if (queue->process_line[i]->waiting_time == 0)
              //{
                //queue->process_line[i]->state = 0;
                //printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, queue->process_line[i]->name);
             // }
           // }
         // }

        //}
      //}
    //}
    for (int i = 0; i < counter; i++)
        {
          if (queue->process_line[i]->state == 0 && queue->process_line[i]->initial_time <= time && occupied == false)
          {
            process = queue->process_line[i];
            process->state = 1;
            process->running_time = 1;
            // Adjust the queue so it can be rearrange after
            up_the_queue(queue->process_line, i);
            if (process->index == 0 && process->running_time == 1)
            {
              printf("[t = %d] El proceso %s ha sido CREADO\n", time, process->name);
            }
            printf("[t = %d] El proceso %s ha pasado a estado RUNNING\n", time, process->name);
            quantum_generated = quantum(100,queue->factories[process->factory_id],f);
            //process_found = true;
            occupied = true;
            //break;
          }
         // {
            //if (queue->process_line[i]->state == 2)
             // {
              //  queue->process_line[i]->waiting_time -= 1;
                // If the process waiting time is up then is READY
              //  if (queue->process_line[i]->waiting_time == 0)
              //  {
              //    queue->process_line[i]->state = 0;
              //    printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, queue->process_line[i]->name);
              //  }
              //}
          //}
        }
        sleep(1);
        time += 1;
        for (int i = 0; i < counter; i++)
        {
          if (queue->process_line[i]->state == 2)
              {
                queue->process_line[i]->waiting_time -= 1;
                // If the process waiting time is up then is READY
                if (queue->process_line[i]->waiting_time == 0)
                {
                  queue->process_line[i]->state = 0;
                  printf("[t = %d] El proceso %s ha pasado a estado READY\n", time, queue->process_line[i]->name);
                }
              }
        }
  }

}
