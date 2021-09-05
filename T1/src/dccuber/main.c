#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <signal.h>

#include "../file_manager/manager.h"
#include "./dccuber.h"

// Declare
pid_t delivery_pid;
pid_t factory_pid;
pid_t traffic_light_pid;
int all_traffic_lights[3] = {1, 1, 1};
int number_of_deliveries;
int number_of_deliveries_finished;
int deliveries_created;
int *all_deliveries;
int all_lights[3];
int all_factories[1];

void handle_state(int sig, siginfo_t *siginfo, void *context)
{
  int state_received = siginfo->si_value.sival_int;
  if (all_traffic_lights[state_received] == 1){
    all_traffic_lights[state_received] = 0;
  } else
  {
    all_traffic_lights[state_received] = 1;
  }
  // Envia el estado recibido del semaforo al repartidor
  for (int j=0;j<deliveries_created;j++)
  {
     send_signal_with_int(all_deliveries[j], state_received);
   }
}

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

// MAIN PROGRAM

int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  int time_of_creation;
  int status;  
  int retval;
  number_of_deliveries = atoi(data_in->lines[1][1]);
  time_of_creation = atoi(data_in->lines[1][0]);
  all_deliveries = malloc(number_of_deliveries*sizeof(int));

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");


  factory_pid = fork();
  if (factory_pid == 0)
  {
    //This is the creation of delivery
    for (int i = 0; i < number_of_deliveries; i++)
    {
      delivery_pid = fork();
      all_deliveries[i] = delivery_pid;
      deliveries_created += 1;
      if (delivery_pid == 0)
      {
        // We have to exec everything in delivery
        char text[20];
        sprintf(text, "%d", i);
        char *const argv[] = {text, data_in->lines[0][0], data_in->lines[0][1], data_in->lines[0][2], data_in->lines[0][3], NULL};
        execv("./repartidor", argv);

      } else {
        // Factory
        // Recibe un SIGUSR1 con la información del estado de cada semaforo
        connect_sigaction(SIGUSR1, handle_state);
        
      }
      sleep(time_of_creation);
      
    }
    while(deliveries_created < number_of_deliveries)
    {
      // printf("Falta\n");
    }
    number_of_deliveries_finished = 0;
    for (int i = 0; i < number_of_deliveries; i++)
    {
      wait(NULL);
      number_of_deliveries_finished += 1;
    }
    // free(all_deliveries);
    exit(0);

  } 
  else
  {
      all_factories[0] = factory_pid;
      // Traffic Light 1
      traffic_light_pid = fork();
      char text_2[20];
      sprintf(text_2, "%d", factory_pid);
      if (traffic_light_pid == 0)
      {
        char *const argv[] = {"0", data_in->lines[1][2], text_2, NULL}; 
        execv("./semaforo", argv);
      } 
      else
      {
        all_lights[0] = traffic_light_pid;
        // // Traffic Light 2
        traffic_light_pid = fork();
        if (traffic_light_pid == 0)
        {
          char *const argv[] = {"1", data_in->lines[1][3], text_2, NULL}; 
          execv("./semaforo", argv);
        } else
        {
          // Traffic Light 3
          all_lights[1] = traffic_light_pid;
          traffic_light_pid = fork();
          if (traffic_light_pid == 0)
          {
            char *const argv[] = {"2", data_in->lines[1][4], text_2, NULL}; 
            execv("./semaforo", argv);
          } 
          else
          {
            all_lights[2] = traffic_light_pid;
            // main proccess
            printf("MAIN: process %d\n", getpid());

            signal(SIGINT, handle_sigint);
            
            waitpid(all_factories[0], NULL, 0);
            free(all_deliveries);
          }
        }

      }    


  }
  for (int i = 0; i < 3; i++)
  {
    kill(all_lights[i], SIGINT);
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
  return 0;
}