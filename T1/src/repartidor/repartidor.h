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

void resultados(FILE* output_file);

void avanzar(int postion_1, int position_2, int position_3, int finish_position);

int resting(int traffic_light_id);

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context);