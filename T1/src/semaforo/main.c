#include <stdio.h>
#include <unistd.h>
#include "./semaforo.h"

int cambio_de_color(Semaforo* semaforo) // Tiene que recibir la señal de que todos los repartidores llegaron a la bodega
{
    int contador = 0;
    while (contador < 5)
    {
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
        sleep(semaforo->delay);
        contador += 1;
    }
    return contador;
}

void resultados(FILE* output_file, int contador)
{
    fprintf(output_file, "CANTIDAD_DE_CAMBIOS\n");
    fprintf(output_file, "%d\n",contador);
}

int main(int argc, char const *argv[])
{
    printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
    Semaforo* semaforo = malloc(sizeof(Semaforo));
    semaforo->id = 1;
    semaforo->delay = 6;
    semaforo->color_actual = 1;
    int contador = cambio_de_color(semaforo);
    FILE* output = fopen("semaforo.txt", "w");
    resultados(output,contador);
  printf("I'm the SEMAFORO process and my PID is: %i\n", getpid());
}