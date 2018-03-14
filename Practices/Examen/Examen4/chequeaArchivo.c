#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <math.h>
/*
  gcc -g chequeaArchivo.c - o CHE1
  mac-->>    ./CHE1 ~/Desktop/prueba/archivo1.txt
  ubuntu-->> ./CHE1 ~/Escritorio/SO_T-formacion/Examen/Examen4/archivo1.txt

  IMPRIME LA DIFERENCIA CUANDO SE MODIFIQUE EL archivo1.txt
*/
int main(int argc, char const *argv[])
{
  if(setvbuf(stdout,NULL,_IONBF,0))
  {
    perror("ERROR EN EL SETBUFF");
  }
  int tam=0,diferencia=0;
  if(argc!=2)
  {
    perror("Error numero argumentos");
    exit(1);
  }

  struct stat atributos;
  if(stat(argv[1],&atributos)<0)
  {
    perror("Error al intentar acceder a los atributos del archivo\n");
    exit (-1);
  }

  if(!(S_ISREG(atributos.st_mode)))
  {
    perror("NO ES UN ARCHIVO REGULAR\n");
    exit (-1);
  }
  else
  {
    //printf("TAM<%lu>\n",atributos.st_size );

    while(1)
    {
      tam= atributos.st_size;
      if(stat(argv[1],&atributos)<0)
      {
      perror("Error al intentar acceder a los atributos del archivo\n");
      exit (-1);
      }
      //printf("TAM<%lu>\n",atributos.st_size );
      if(tam!=atributos.st_size)
      {
        diferencia=tam-atributos.st_size;
        //fabs(diferencia);

        printf("%10d\n", diferencia);
      }
      sleep(2);
    }
  }
  return 0;
}
