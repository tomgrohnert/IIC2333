#include <stdlib.h>

typedef struct repartidor
{
    int id;
    int t1; // tiempo que se demora en pasar el primer semaforo
    int t2; // tiempo que se demora en pasar el segundo semaforo
    int t3; // tiempo que se demora en pasar el tercer semaforo
    int t_bodega; // tiempo que se demora en llegar a la fabrica
    int posicion_actual; // posicion en la que esta el repartidor
} Repartidor;

void resultados(FILE* output_file, Repartidor* repartidor);

void avanzar(Repartidor* repartidor, int finish_position);