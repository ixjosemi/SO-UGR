#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
  char buffer[50];
  int bytes;
  while((bytes=read(STDIN_FILENO,buffer,50*sizeof(char)))>0)
  {
    if(write(STDOUT_FILENO,buffer,bytes*sizeof(char))<0)
    {
      perror("error a la hora de escrtibir");
      exit(1);
    }
  }
  return 0;
}
