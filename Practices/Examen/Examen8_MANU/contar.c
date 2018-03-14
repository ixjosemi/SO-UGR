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
/*gcc -g contar.c -o CONT
	./CONT DOC.txt ~/Escritorio/prueba/

*/

int main(int argc, char const *argv[])
{

	//numero parametros maximo permitido
	if(argc!=3)
	{
		perror("error numero argumentos");
		exit(EXIT_FAILURE);
	}

	//variables necesarias para el funcionameinto del programa
	char ruta[256];//obtener la ruta
	int suma=0;
	mode_t permisos= S_IXOTH;


	//estructuras para recorrer directorio y sus datos
	struct dirent *entrada;
	struct stat atributos;
	DIR *carpeta;
	int arc;
	/////////APERTURA/////////
	int fd=open(argv[1],O_WRONLY| O_CREAT,0644);

	int PID;
//////////////////////////////////////////////////////////////////////////
	if((carpeta=opendir(argv[2]))==NULL)
	{
		perror("Error apertura DIRECTORIO");
		exit(EXIT_FAILURE);
	}


	while((entrada=readdir(carpeta))!=NULL)
	{
		if(!strcmp(entrada->d_name,".") ) continue;
		if(!strcmp(entrada->d_name,"..") ) continue;
		sprintf(ruta,"%s/%s",argv[2],entrada->d_name);
		if(stat(ruta,&atributos))
		{
			perror("Error apertura ATRIBUTOS");
			exit(EXIT_FAILURE);
		}


			if(S_ISDIR(atributos.st_mode))
			{


				if((atributos.st_mode & permisos)== permisos)
				{
					if((PID=fork())<0)
					{
						perror("error en el fork");
						exit(EXIT_FAILURE);
					}
					if(PID==0)
					{
						if((dup2(fd,STDOUT_FILENO))<0)
						{
							perror("Error DUP2");
							exit(EXIT_FAILURE);
						}
						printf("Nombre:<%s> , Tam<%lu>",entrada->d_name,atributos.st_size );//imprimo el nombre, y el tam
						exit(0);
					}


					suma=suma+atributos.st_size;
					wait(NULL);
				}

			}

	}
	close(fd);
	//close(carpeta);
	//printf("%d",suma );
	write(STDOUT_FILENO,&suma,sizeof(int));
	return 0;
}
