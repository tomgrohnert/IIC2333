#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "./semaforo.h"

#include "../file_manager/manager.h"

Semaforo* semaforo;

void cambio_de_color() // Tiene que recibir la señal de que todos los repartidores llegaron a la bodega
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
      send_signal_with_int(semaforo->parent, semaforo->id);
    }
}

void resultados(FILE* output_file, int counter)
{
    fprintf(output_file, "CANTIDAD_DE_CAMBIOS\n");
    fprintf(output_file, "%d\n", counter);
}

void handle_sigabrt()
{
    char string[30];
    sprintf(string, "semaforo_%d.txt", semaforo->id);
    FILE* output = fopen(string, "w");
    resultados(output, semaforo->cantidad_de_cambios);
    exit(0);
}

void handle_sigint()
{
    char string[30];
    sprintf(string, "semaforo_%d.txt", semaforo->id);
    FILE* output = fopen(string, "w");
    resultados(output, semaforo->cantidad_de_cambios);
    free(semaforo);
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGABRT, handle_sigabrt);
    signal(SIGINT, handle_sigint);
    printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
    semaforo = malloc(sizeof(Semaforo));
    semaforo->id = atoi(argv[0]);
    semaforo->delay = atoi(argv[1]);
    semaforo->parent = atoi(argv[2]);
    semaforo->color_actual = 1;
    cambio_de_color();
    char string[30];
    sprintf(string, "semaforo_%d.txt", semaforo->id);
    FILE* output = fopen(string, "w");
    resultados(output,semaforo->cantidad_de_cambios);
    free(semaforo);
    exit(0);
}