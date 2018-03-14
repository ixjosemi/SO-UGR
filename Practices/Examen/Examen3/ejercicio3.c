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

int main(int argc, char const *argv[])
{
  struct flock cerrojo;
  //cerrojo.ltype=F_RDLCK;// F_WRLCK O F_UNLCK
  cerrojo.l_type=F_UNLCK;
  cerrojo.l_whence=SEEK_SET;
  cerrojo.l_start=0;
  cerrojo.l_len=0;
  int fd;
  //al crear el archivo,es para que no haya mas de un proceso ejecutando este programa
  //imagina que lo ejecuto mas de una vez
  if((fd=open("archivo3.txt",O_WRONLY|O_CREAT|O_TRUNC,0666))<0)perror("error al crear"),exit(1);
  if(fcntl(fd,F_GETLK,&cerrojo)<0)perror("error al consultar el estado"),exit(1);
  if(cerrojo.l_type !=F_UNLCK)
  {
    exit(1);//si el cerrojo esta bloqueado ya sea de tipo escritura(F_WRLCK) o tipo lectura(F_RDLCK)
            //es pk se ha ejecutado
  }
  else
  {
    char cadena[20]="HOLA QUE TAL";
    write(fd,cadena,sizeof(char)*20);
    cerrojo.l_type=F_WRLCK;
    cerrojo.l_whence=SEEK_SET;
    cerrojo.l_start=0;
    cerrojo.l_len=0;
    if(fcntl(fd,F_SETLKW,&cerrojo)<0)perror("error al bloquear el cerrojo"),exit(1);
    sleep(5);
    printf("\nFIN\n" );

    cerrojo.l_type=F_UNLCK;//Desbloqueo el archivo para que se pueda acceder luego, pero lo hago con F_SETLKW
    if(fcntl(fd,F_SETLKW,&cerrojo)<0)//PK (W)??????
    {
      perror("error al DESBLOQUEr el cerrojo");
      exit(1);
    }
  }
  return 0;
}
