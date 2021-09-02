#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>

#include "../file_manager/manager.h"


int main(int argc, char const *argv[])
{
  printf("I'm the DCCUBER process and my PID is: %i\n", getpid());

  char *filename = "input.txt";
  InputFile *data_in = read_file(filename);
  int number_of_deliveries;
  int time_of_creation;
  int distance_previous_light;
  pid_t factory_pid;
  pid_t delivery_pid;
  pid_t traffic_light_pid;
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
        int const *argv[] = {atoi(data_in->lines[0][0]), atoi(data_in->lines[0][1]), atoi(data_in->lines[0][2]), atoi(data_in->lines[0][3]), NULL}
      {
        // Factory
      }
      
    }

  } else
  {
    for(int i = 1; i < 3; i++)
    {
      traffic_light_pid = fork();
      if (traffic_light_pid == 0)
      {
        int const *argv[] = {atoi(data_in->lines[1][i+2]), NULL}; // Entregar los valores para cada semaforo
        exec("../semaforo/main.c", argv)
        exit(retval);
      } else
      {
        // main proccess
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
