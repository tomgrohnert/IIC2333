#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "./repartidor.h"

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

void avanzar(Repartidor* repartidor, int position_1, int position_2, int position_3, int finish_position) // position_<i> -> position of the traffic light <i>
{
  bool boolean = true;
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
        // wait
      }

       
    }
    else if (repartidor->posicion_actual == position_2)
    {
      if (all_traffic_lights_deliveries[1] == 0)
      {
        // wait
      }
     
    }
    else if (repartidor->posicion_actual == position_3)
    {
      if (all_traffic_lights_deliveries[2] == 0)
      {
        // wait
      }
      
    }
    else
    {
      printf("Repartidor %d: Posicion %d\n", repartidor->id, repartidor->posicion_actual);
      sleep(1);
    }
  }
}

int main(int argc, char const *argv[])
{
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  Repartidor* repartidor = malloc(sizeof(Repartidor));
  repartidor->id = getpid();
  avanzar(repartidor, atoi(argv[0]), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}