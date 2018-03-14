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
int main(int argc, char const *argv[])
{

	if(argc<2)
	{
		perror("ERROR numero argumentos");
		exit(1);
	}
	int num_hijos=argc-1;
	int fd[2];
	int PID;
	int suma=0;
	int dato=0;
	printf("NUM:%d \n",num_hijos);
	if(pipe(fd)<0)
	{
		perror("error PIPE");
		exit(1);
	}
	int i;
	for ( i = 1; i <= num_hijos; ++i)
	{
		if((PID=fork())<0)
		{
			perror("error fORK");
			exit(1);
		}
		if(PID==0)
		{
			close(fd[0]);
			if((dup2(fd[1],STDOUT_FILENO))<0)
			{
				perror("error DUP2");
				exit(1);
			}
			//int num=6;
			//write(fd[1],&num,sizeof(int));
			char ruta[256];
			sprintf(ruta,"%d.Directorio",getpid());
			execlp("./CONT","./CONT",ruta,argv[i],NULL);
			perror("error PIPE");
			exit(1);
		}
		else
		{
			if(read(fd[0],&dato,sizeof(int))<0)
			{
				perror("error READ");
				exit(1);
			}
			//printf("DATO<%d>\n",dato);
			suma=suma+dato;
			
		}
	}

	printf("total de la suma es:<%d>",suma );

	close(fd[1]);
	close(fd[0]);
	for(i=0,i<num_hijos;i++)
	{
		wait(NULL);
	}

	return 0

}
