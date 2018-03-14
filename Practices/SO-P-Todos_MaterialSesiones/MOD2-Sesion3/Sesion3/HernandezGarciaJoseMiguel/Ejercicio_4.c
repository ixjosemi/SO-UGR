/* JOSE MIGUEL HERNANDEZ GARCIA */
/* 2ºC GRUPO C2                 */
/* EJERCICIO 4 MOD 2 SESION 3   */

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(){
   int i;
   int estado;
   pid_t PID;

   // Creamos los cinco procesos hijos
   for(i = 0; i < 5; i++){

      if((PID = fork()) <  0){
         perror("Error en fork\n");
         exit(-1);
      }

      if(PID == 0){   // El proceso hijo imprime el mensaje y se termina
         printf("Soy el hijo PID = %i\n", getpid());
         exit(0);
      }
   }

   // Esperamos a que los procesos hijos finalicen
   for(i = 4; i >= 0; i--){
      PID = wait(&estado);
      printf("Ha finalizado mi hijo con PID = %i\n", PID);
      printf("Solo me quedan %i hijos vivos\n", i);
   }
}
