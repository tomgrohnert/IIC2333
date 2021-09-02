#include <stdio.h>
#include <unistd.h>
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

  printf("Leyendo el archivo %s...\n", filename);
  printf("- Lineas en archivo: %i\n", data_in->len);
  printf("- Contenido del archivo:\n");
  printf("veamos, %i \n", data_in->len);
  factory_pid = fork();
  //This is factory
  if (factory_pid == -1)
  {
    // If fork does not function
    exit(-1);
  }
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
        //exec("../repartidor/main.c")
      } else
      {
        // Factory
      }
      
    }

  } else
  {
    //This is the creation of traffic_lights
    for (int i = 0; i < 3; i++)
    {
      traffic_light_pid = fork();
      if (traffic_light_pid == 0)
      {
        // We have to exec everything in delivery
        // We are giving as arguments, first; time, second; we should give its time to start, last; differnece time with previous
        if (i > 0)
        {
          distance_previous_light = (atoi(data_in->lines[0][i]) - atoi(data_in->lines[0][i-1]));
        } else
        {
          distance_previous_light = 0;
        }
        
        //exec("../semaforo/main.c", atoi(data_in->lines[1][i+2]), atoi(data_in->lines[0][i]), distance_previous_light)
      } else
      {
        //parent wait for this traffic light to change light

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
