#include <stdio.h>
#include <unistd.h>
#include "./repartidor.h"

void resultados(FILE* output_file, Repartidor* repartidor)
{
  fprintf(output_file,"TIEMPO_SEMAFORO1,TIEMPO_SEMAFORO2,TIEMPO_SEMAFORO3,TIEMPO_BODEGA\n");
  fprintf(output_file,"%d,%d,%d,%d\n",repartidor->t1,repartidor->t2,repartidor->t3,repartidor->t_bodega);
}

void avanzar(Repartidor* repartidor)
{
  for (int i=0;i<15;i++) // Esto tiene que ser hasta que el repartidor llegue a la bodega
  {
    repartidor->posicion_actual = i;
    printf("Repartidor %d: Posicion %d\n", repartidor->id, repartidor->posicion_actual);
    sleep(1);
  }
}

int main(int argc, int const *argv[])
{
  printf("I'm the REPARTIDOR process and my PID is: %i\n", getpid());
  Repartidor* repartidor = malloc(sizeof(Repartidor));
  repartidor->id = getpid();
  avanzar(repartidor);
}