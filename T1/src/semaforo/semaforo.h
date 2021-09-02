#include <stdlib.h>

typedef struct semaforo
{
  int id; // id del semaforo
  int delay;
  // pid_t pid_fabrica;
  int color_actual; // 0-> rojo y 1-> verde, parte con verde por default
} Semaforo;

int cambio_de_color(Semaforo* semaforo);

void resultados(FILE* output_file, int contador);