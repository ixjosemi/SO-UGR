#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <dirent.h>
#include<signal.h>
#include<limits.h>
void manejador( int iden)
{
  int estado,pid;
  waitpid(pid,&estado,0);
  printf(" El hijo1 con pid-> %d ha terminado con estado %d \n",pid, estado);
}
int main(int argc, char const *argv[])
 {
  if(argc!=2)
  {
    perror("error argumentos");
    exit(EXIT_FAILURE);
  }

  if(setvbuf(stdout,NULL,_IONBF,0)) {//NO SE MUY BIEN LO QUE ES
  	perror("\nError en setvbuf");
  }

struct sigaction sa;
sa.sa_handler=manejador;
if(sigaction(SIGCHLD,&sa,NULL)<0) perror("error signation"),exit(1);

  int fd,PID;
  struct dirent *entrada;
  struct stat atributos;
  DIR *carpeta;
  char ruta[PATH_MAX];
  char rutaTipo[PATH_MAX];



  if((carpeta=opendir(argv[1]))==NULL)
  {
    perror("error argumentos");
    exit(EXIT_FAILURE);
  }
  while ((entrada=readdir(carpeta))!=NULL)
  {
    sprintf(ruta,"%s/%s",argv[1],entrada->d_name);
    sprintf(rutaTipo,"%s_tipo/%s_tipo",argv[1],entrada->d_name);//creo que petara pk no se si se crea el NUEVO_DIRECTORIO

    if(stat(ruta,&atributos)<0)
    {
      perror("error ATRIBUTOS");
      exit(EXIT_FAILURE);
    }
    if((PID=fork())<0)
    {
      perror("error hijo");
      exit(EXIT_FAILURE);
    }
    if(PID==0)
    {
      if((fd=open(rutaTipo,O_CREAT|O_RDWR,0777))<0)
      {
        perror("error NUEVO_DIRECTORIO\n");
        exit(EXIT_FAILURE);
      }
      if((dup2(fd,STDOUT_FILENO))<0)
      {
        perror("error DUP2");
        exit(EXIT_FAILURE);
      }
      printf("USUARIO<%d>\n",atributos.st_uid );
      //printf( "SUID:%s\n",atributos.st_mode & S_ISUID?"true":"false"); //?????
      execlp("file","file",NULL);
      perror("error EXCLP");
      exit(EXIT_FAILURE);
    }


  }
  return 0;
}
