#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "./repartidor.h"

void resultados(FILE* output_file, Repartidor* repartidor)
{
  fprintf(output_file,"TIEMPO_SEMAFORO1,TIEMPO_SEMAFORO2,TIEMPO_SEMAFORO3,TIEMPO_BODEGA\n");
  fprintf(output_file,"%d,%d,%d,%d\n",repartidor->t1,repartidor->t2,repartidor->t3,repartidor->t_bodega);
}

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
  int state_received = siginfo->si_value.sival_int;
  if (state_received == 0)
  {
    // Wait until the light is green
  }
}

void avanzar(Repartidor* repartidor, int position_1, int position_2, int position_3, int finish_position) // position_<i> -> position of the traffic light <i>
{
  bool boolean = true;
  while (boolean) // Esto tiene que ser hasta que el repartidor llegue a la bodega
  {
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
      // Consultar a la fabrica por el estado del semaforo 1

      // Recibir la señal con el estado actual del semaforo
      connect_sigaction(SIGUSR1,handle_sigusr1); 
    }
    else if (repartidor->posicion_actual == position_2)
    {
      // Consultar a la fabrica por el estado del semaforo 2
      connect_sigaction(SIGUSR1,handle_sigusr1); 
    }
    else if (repartidor->posicion_actual == position_3)
    {
      // Consultar a la fabrica por el estado del semaforo 3
      connect_sigaction(SIGUSR1,handle_sigusr1); 
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