#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 

#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);

  // printf("Leyendo el archivo %s...\n", filename);
  // printf("- Lineas en archivo: %i\n", data_in->len);
  // printf("- Contenido del archivo:\n");

  // printf("\t- ");

  int dist_semaforo1 = data_in->lines[0][0];
  int dist_semaforo2 = data_in->lines[0][1];
  int dist_semaforo3 = data_in->lines[0][2];
  int dist_bodega = data_in->lines[0][3];

  int tiempo_repartidores = data_in->lines[1][0];
  int n_repartidores = data_in->lines[1][1];
  int tiempo_semaforo1 = data_in->lines[1][2];
  int tiempo_semaforo2 = data_in->lines[1][3];
  int tiempo_semaforo3 = data_in->lines[1][4];

  int status;  
  int retval;

  pid_t fabrica_pid = fork();
    
  if (fabrica_pid >= 0) /* fork succeeded */
  {
      if (fabrica_pid == 0) /* fork() returns 0 to the child process */
      {
        printf("FABRICA: I am the child process!\n");
        printf("FABRICA: Here's my PID: %d\n", getpid());
        printf("FABRICA: My parent's PID is: %d\n", getppid());
        printf("FABRICA: The value of my copy of fabrica_pid is: %d\n", fabrica_pid);

        // Aca empiezan a correr los procesos de semaforos con exec() y repartidores
        char const *argv[] = {"1",NULL}; // Entregar los valores para cada semaforo
        execv("./repartidor", argv);
        // Aca debiese esperar a que lleguen 
        printf("FABRICA: Goodbye!\n");    
        exit(retval); /* child exits with user-provided return code */
      }
      else /* fork() returns new pid to the parent process */
      {
        printf("MAIN: I am the parent process!\n");
        printf("MAIN: Here's my PID: %d\n", getpid());
        char const *argv[] = {"1",NULL}; // Entregar los valores para cada semaforo
        execv("./semaforo", argv);
        printf("MAIN: The value of my copy of fabrica_pid is %d\n", fabrica_pid);
        printf("MAIN: I will now wait for my child to exit.\n");
        printf("MAIN: Goodbye!\n");             
        exit(0);  /* parent exits */  
      }
  }
  else /* fork returns -1 on failure */
  {
      perror("fork"); /* display error message */
      exit(0); 
  }

  // for (int i = 0; i < 4; i++)
  // {
  //   printf("%s, ", data_in->lines[0][i]);
  // }
  // printf("\n");

  // printf("\t- ");
  // for (int i = 0; i < 5; i++)
  // {
  //   printf("%s, ", data_in->lines[1][i]);
  // }
  printf("\n");

  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
}
