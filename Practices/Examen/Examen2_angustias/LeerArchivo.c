#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <dirent.h>
/*
  gcc -g LeerArchivo.c -o LEER
  ./LEER ((zdoc.txt))     NO PUEDO COMPILARLO asi, NO LE ESTOY PASANDO UNA RUTA, si no un archivo solo
  ./LEER ,intro y luego zdoc.txt 

    te muestra:
      Archivo--><zdoc.txt>  INODO:<151236>  TAM:<29>  PERMISOS:<100644>
*/
int main(int argc, char const *argv[]) {

/*  OJO!!! QUE PETA SI PONGO EL IF COMO EN LOS EJERCICIOS ANTERIORES
  if(argc!=2)
  {
    perror("Error numero de argumentos archivo LEERARCHIVO");
    exit(1);
  }
*/
    char cadena[10];//NO HACE FALTA HACER UN strcmp
    scanf("%s", cadena);//SE PUEDE HACER CON UN read
    /*if(read(STDIN_FILENO,&cadena,sizeof(char)*10)<0)
    {
      perror("Error AL leer");
      exit(1);
    }*/

    if(strcmp(cadena,"FIN")==0)
    {
      printf("FIN DEL PROGRAMA\n");
      exit(1);
    }
    else
    {
      //  while(scanf(%s,cadena)!="FIN")
          //printf("CONTINUAMOS\n");
          DIR *carpeta;
          struct dirent *entrada;
          struct stat atributos;
      /*  //COMO ESTOY EN EL DIRECTORIO DE TRABAJO, solo paso EL NOMBRE Y NO LA RUTA!!!!
          //entonces no abro ningun directorio
          if((carpeta=opendir("."))==NULL)
          {
            perror("Error al abrir el directorio");
            exit(1);
          }
      */
          if(stat(cadena,&atributos)<0)
          {
            perror("Error AL ACCEDER AL ARCHIVO");
            exit(1);
          }
          else
          {
            printf("Archivo--><%s>  INODO:<%lu>  TAM:<%lu>  PERMISOS:<%o>\n",cadena,atributos.st_ino,atributos.st_size,atributos.st_mode);
          }//EN MAC %llu

      }
  return 0;
}
