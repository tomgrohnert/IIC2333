#include <stdlib.h>

typedef struct semaforo
{
  int id; // id del semaforo
  int delay;
  int cantidad_de_cambios;
  pid_t parent;
  int color_actual; // 0-> rojo y 1-> verde, parte con verde por default
} Semaforo;

void cambio_de_color();

void resultados(FILE* output_file, int contador);