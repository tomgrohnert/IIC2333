#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <signal.h>

#include "../file_manager/manager.h"
#include "./dccuber.h"

pid_t factory_pid;
pid_t delivery_pid;
pid_t traffic_light_pid;

void handle_sigint(int sig)
{
  // Emitir un SIGABRT a la fabrica y a los semaforos
  kill(factory_pid,SIGABRT);
  kill(traffic_light_pid,SIGABRT);
}

void handle_sigabrt_1(int sig)
{
  kill(delivery_pid,SIGABRT);
}

void handle_sigabrt_2(int sig)
{
  // Debe escribir los resultados en el archivo semaforo_<i>.txt
}

void handle_sigabrt_3(int sig)
{
  // Debe escribir los resultados en el archivo repartidor_<i>.txt
}

// MAIN PROGRAM

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  int number_of_deliveries;
  int time_of_creation;
  int status;  
  int retval;

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");
  printf("veamos, %i \n", data_in->len);


  factory_pid = fork();
  if (factory_pid == 0)
  {
    //This is the creation of delivery
    number_of_deliveries = atoi(data_in->lines[1][1]);
    time_of_creation = atoi(data_in->lines[1][0]);
    for (int i = 0; i < number_of_deliveries; i++)
    {
      sleep(time_of_creation);
      delivery_pid = fork();
      if (delivery_pid == 0)
      {
        // We have to exec everything in delivery
        char *const argv[] = {data_in->lines[0][0], data_in->lines[0][1], data_in->lines[0][2], data_in->lines[0][3], NULL};
        execv("./repartidor", argv);

        // signal(SIGABRT,handle_sigabrt_3);
        // exit(retval);
      } else {
        // Factory
        printf("FACTORY: process %d\n", getpid());
        // Recibe un SIGUSR1 con la información del estado de cada semaforo
        connect_sigaction(SIGUSR1,handle_state);

        // signal(SIGABRT,handle_sigabrt_1);

        // wait(NULL); // Tiene que esperar a que terminen los deliveries
      }
      
    }

  } 
  else
  {
      // Traffic Light 1
      traffic_light_pid = fork();
      if (traffic_light_pid == 0)
      {
        char *const argv[] = {"0", data_in->lines[1][2], itoa(factory_pid), NULL}; 
        execv("./semaforo", argv);
        // Envia el estado del semaforo a la fabrica

        // signal(SIGABRT,handle_sigabrt_2);
        exit(retval);
      } 
      else
      {
        // // Traffic Light 2
        traffic_light_pid = fork();
        if (traffic_light_pid == 0)
        {
          char *const argv[] = {"1", data_in->lines[1][3], itoa(factory_pid), NULL}; 
          execv("./semaforo", argv);
          // Envia el estado del semaforo a la fabrica

          // signal(SIGABRT,handle_sigabrt_2);
          exit(retval);
        } else
        {
          // Traffic Light 3
          traffic_light_pid = fork();
          if (traffic_light_pid == 0)
          {
            char *const argv[] = {"2", data_in->lines[1][4], itoa(factory_pid), NULL}; 
            execv("./semaforo", argv);
            // Envia el estado del semaforo a la fabrica

            // signal(SIGABRT,handle_sigabrt_2);
            exit(retval);
          } 
          else
          {
            // main proccess
            printf("MAIN: process %d\n", getpid());

          //   signal(SIGINT,handle_sigint);
          //   kill(getpid(),SIGINT);

          //   wait(NULL);
          }
        }

      }    


  }

  
  for (int i = 0; i < 4; i++)
  {
    printf("%s\n", data_in->lines[0][i]);
  } 
  
  printf("\n");

  printf("\t- ");
  for (int i = 0; i < 5; i++)
  {
    printf("%s, ", data_in->lines[1][i]);
  }
  printf("\n");

  printf("Liberando memoria...\n");
  input_file_destroy(data_in);
}
