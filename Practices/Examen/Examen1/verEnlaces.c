#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <dirent.h>

 int RecorrerDirectorio(char* rutaDirectorio, ino_t inodo)
 {
	  DIR* directorio;
	  struct dirent* entrada;
	  struct stat atributos;
	  char nuevaRuta[512];
	  int contador = 0;
	if((directorio=opendir(rutaDirectorio))==NULL)//abro el argumeto que le paso(el directorio)
  	{
   	 	perror("no se ha podido leer el directorio\n");
  	  	exit (-1);
  	}

  while((entrada = readdir(directorio)) != NULL)
  {
    sprintf(nuevaRuta, "%s/%s", rutaDirectorio, entrada->d_name);//rutaDirectorio --> argv[1]
    //printf("\nRUTA: %s \n\n",nuevaRuta);  FALLA EN LA RECURSIVIDAD
    if(stat(nuevaRuta,&atributos)<0)
	{
		perror("ERROR al intentar acceder a los atributos del archivo\n");
		exit (-1);
	}

    if(S_ISDIR(atributos.st_mode))
    {
      contador += RecorrerDirectorio(nuevaRuta, inodo);  //RECURSIVIDAD
    }
    if(inodo == entrada->d_ino)
    {
      contador++;
    }
  }
  return contador;
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    printf("Uso: ....");
    exit(1);
  }

  struct stat atributos;
  if(stat(argv[1], &atributos) < 0)
  {
  	perror("Error al intentar acceder a los atributos del archivo\n");
	exit (-1);
  }

  printf("El no de enlaces es: %d\n",RecorrerDirectorio("/home/miguel/Escritorio/", atributos.st_ino));

}
/*
  	 struct dirent *entrada;  //para visualizar el interior de mi directorio
  	struct stat atributos,atributos2;
  	DIR *carpeta;
  	if((carpeta=opendir(argv[1]))==NULL)//abro el argumeto que le paso(el directorio)
  	{
   	 	perror("no se ha podido leer el directorio\n");
  	  	exit (-1);
  	}
  	while ((entrada=readdir(carpeta))!=NULL)//voy recorriendo todos los ficheros del directorio que le paso como ruta
  	{
  		char ruta[512];// me creo un char para guardar el directorio/nombre.txt actual
   		sprintf(ruta,"%s/%s",argv[1],entrada->d_name);//esto es el directorio/lo de dentro
    	if(stat(ruta,&atributos)<0)
    	{
    		perror("Error al intentar acceder a los atributos del archivo\n");
    		exit (-1);
    	}
    	if(atributos.st_nlink>0)
    	{
    		printf("%s/%s \n",argv[1],entrada->d_name);
    	}
  	}
	return 0;
}
*/
