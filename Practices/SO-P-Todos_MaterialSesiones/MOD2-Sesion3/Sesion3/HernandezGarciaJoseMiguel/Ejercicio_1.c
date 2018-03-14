/* JOSE MIGUEL HERNANDEZ GARCIA */
/* 2ºC GRUPO C2                 */
/* EJERCICIO 1 MOD 2 SESION 3   */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]){

   if (argc != 2){
      perror("\nError , parametro = un numero a comprobar");
      exit(-1);
   }

   pid_t pid;
   pid = fork();

   if (pid < 0){
      perror("\nError en el fork");
      exit(-1);
   }
   else

   if (pid == 0){
      // Proceso hijo
      printf("Hola , soy el proceso hijo y mi pid es: %d y el de mi padre es %d,"
                  " y voy a comprobar si"
                  " el numero introducido es par o impar \n ", getpid() , getppid());
      int num = atoi(argv[1]);

      if ((num % 2) == 1)
         printf("El numero %d introducido es impar \n" , num);
      else printf("El numero %d introducido es par \n" , num);
   }
   else

   if (pid){
      // Proceso padre
      printf("Hola , soy el proceso padre y mi pid es: %d y el de mi hijo"
            " es %d, y voy a comprobar si el numero introducido es divisible por 4 \n", getpid()
            , pid);
      int num = atoi(argv[1]);

      if (num % 4 == 0)
         printf("El numero %d introducido es divisible por 4 \n" , num);
      else printf("El numero %d introducido es indivisible por 4 \n" , num);
   }

   return(0);
}
