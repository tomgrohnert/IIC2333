#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "./repartidor.h"
#include "../file_manager/manager.h"

int all_traffic_lights_deliveries[3] = {1, 1, 1};

void resultados(FILE* output_file, Repartidor* repartidor)
{
  fprintf(output_file,"TIEMPO_SEMAFORO1,TIEMPO_SEMAFORO2,TIEMPO_SEMAFORO3,TIEMPO_BODEGA\n");
  fprintf(output_file,"%d,%d,%d,%d\n",repartidor->t1,repartidor->t2,repartidor->t3,repartidor->t_bodega);
}

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
  int state_received = siginfo->si_value.sival_int;
  if (all_traffic_lights_deliveries[state_received] == 0)
  {
    all_traffic_lights_deliveries[state_received] = 1;
  } else
  {
    all_traffic_lights_deliveries[state_received] = 0;
  }
}

int resting(int traffic_light_id)
{
  int counter = 0;
  while (all_traffic_lights_deliveries[traffic_light_id] == 0)
  {
    printf("waiting light %d to change", traffic_light_id);
    sleep(1);
    counter += 1;
  }
  return counter;
}

void avanzar(Repartidor* repartidor, int position_1, int position_2, int position_3, int finish_position) // position_<i> -> position of the traffic light <i>
{
  bool boolean = true;
  int total_time;
  int time_resting;
  int auxiliar_time;
  while (boolean) // Esto tiene que ser hasta que el repartidor llegue a la bodega
  {
    connect_sigaction(SIGUSR1, handle_sigusr1);
    int *current_position = malloc(sizeof(int));
    *current_position = repartidor->posicion_actual;
    repartidor->posicion_actual = *current_position + 1;
    free(current_position);
    if (repartidor->posicion_actual == finish_position)
    {
      printf("Repartidor %d llego: Posicion %d\n", repartidor->id, repartidor->posicion_actual);
      boolean = false;
    } 
    else if (repartidor->posicion_actual == position_1)
    {
      if (all_traffic_lights_deliveries[0] == 0)
      {
        time_resting = resting(0);
        auxiliar_time = time_resting + total_time;
        repartidor->t1 = auxiliar_time;
        total_time = auxiliar_time;
        auxiliar_time = 0;
      }

       
    }
    else if (repartidor->posicion_actual == position_2)
    {
      if (all_traffic_lights_deliveries[1] == 0)
      {
        time_resting = resting(1);
        auxiliar_time = time_resting + total_time;
        repartidor->t2 = auxiliar_time;
        total_time = auxiliar_time;
        auxiliar_time = 0;
      }
     
    }
    else if (repartidor->posicion_actual == position_3)
    {
      if (all_traffic_lights_deliveries[2] == 0)
      {
        time_resting = resting(2);
        auxiliar_time = time_resting + total_time;
        repartidor->t3 = auxiliar_time;
        total_time = auxiliar_time;
        auxiliar_time = 0;
      }
      
    }
    else
    {
      printf("Repartidor %d: Posicion %d\n", repartidor->id, repartidor->posicion_actual);
      sleep(1);
      total_time += 1;
    }
  }
}

void resultados(File* output_file, Repartidor* repartidor)
{
  fprintf(output_file, "%d, %d, %d, %d\n", repartidor->t1, repartidor->t2, repartidor->t3, repartidor->t_bodega);
}

int main(int argc, char const *argv[])
{
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  Repartidor* repartidor = malloc(sizeof(Repartidor));
  repartidor->id = atoi(argv[1]);
  avanzar(&repartidor, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
  char string[30];
  sprintf(string, "repartidor_%d.txt", repartidor->id);
  FILE* output = fopen(string, "w");
  resultados(output, &repartidor);
  // kill itself
}