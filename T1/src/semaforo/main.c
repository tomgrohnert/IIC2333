#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "./semaforo.h"

int cambio_de_color(Semaforo* semaforo) // Tiene que recibir la señal de que todos los repartidores llegaron a la bodega
{
    bool boolean = true;
    while (boolean)
    {
      sleep(semaforo->delay);
      if (semaforo->color_actual == 1)
      {
          printf("Semaforo %d: VERDE\n", semaforo->id);
          semaforo->color_actual = 0;
      }
      else
      {
          printf("Semaforo %d: ROJO\n", semaforo->id);
          semaforo->color_actual = 1;
      }
      int *number_of_changes = malloc(sizeof(int));
      *number_of_changes = semaforo->cantidad_de_cambios;
      semaforo->cantidad_de_cambios = *number_of_changes + 1;
      free(number_of_changes);
    }
    return semaforo->cantidad_de_cambios;
}

void resultados(FILE* output_file, int counter)
{
    fprintf(output_file, "CANTIDAD_DE_CAMBIOS\n");
    fprintf(output_file, "%d\n", counter);
}

int main(int argc, char const *argv[])
{
    printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
    Semaforo* semaforo = malloc(sizeof(Semaforo));
    semaforo->id = getpid();
    semaforo->delay = atoi(argv[0]);
    semaforo->color_actual = 1;
    int counter = cambio_de_color(semaforo);
    FILE* output = fopen("semaforo.txt", "w");
    resultados(output,counter);
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
}