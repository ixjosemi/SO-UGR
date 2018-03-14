#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

// Función principal de nuestro programa
int main(int argc, char *argv[]){

   DIR *direct;
   unsigned int permisos;
   char *path_name;
   struct stat atributos;
   struc dirent *ed;
   char cad_1[100];
   char cad_2[100];
   extern int errno;

   // Hacemos las distintas comprobaciones
   if(argc == 3){
      path_name = argv[1];
      direct = opendir(path_name);
      permisos = strtol (argv[2], NULL, 8);
   }
   else{
      printf ("Uso: Ejercicio_2.c <path_name> <permisos>\n");
      exit (-1);
   }

   readdir(direct);

   while((ed = readdir(direct)) != NULL){
      sprintf(cad_1, "%s%s", path_name, ed ->d_name);

      if(stat(cad_1, &atributos) < 0){
         printf("\nError al intentar acceder a los atributos de archivo");
         perror("\nError en lstat");
         exit (-1);
      }

      if(S_ISREG(atributos.st_mode)){
         sprintf(cad_2, "%s", ed -> d_name);

         printf("%s : %o", cad_2, atributos.st_mode);

         chmod(cad_1, permisos);

         if(chmod(cad_1, permisos) < 0)
            printf("Error: %s\n", strerror(errno));

         else{
            stat(cad_1, &atributos);
            printf("%o \n", atributos.st_mode);
         }
      }
   }

}
