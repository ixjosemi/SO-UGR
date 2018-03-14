/* JOSE MIGUEL HERNANDEZ GARCIA */
/* 2ºC GRUPO C2                 */
/* EJERCICIO 3 MOD 2 SESION 3   */

// Jerarquía 1
/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 20

void main(){
	int i = 0;
	pid_t pid1, pid2;

	// Jerarquia de procesos tipo 1
	// Cada hijo genera un sub-hijo

	printf("Pid inicial: %d \n\n",getpid());

	for (i = 0; i < NUM_PROC; i++){

		if ((pid1 = fork()) == 0){
			printf("Hola, soy el hijo de %d. Mi PID es %d. \n",getppid(),getpid());
		}
		else

         if (pid1 < 0) {
			   printf("No ha podido crearse un hijo en la jerarquia 1.");
			   return ;
		   } else

         if (pid2 = waitpid(pid1, 0, 0) > 0) {
		      break;
		   }
   }
}
*/
// Jerarquia 2
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 20

void main(){
	int i = 0;
	pid_t pid1, pid2;

	// Jerarquia de procesos tipo 2
	// Solo el padre inicial puede generar hijos

	printf("Pid inicial: %d \n\n",getpid());

	for (i = 0; i < NUM_PROC; i++){

      if ((pid1 = fork()) == 0){
			printf("Hola soy el hijo %d, con PID %d y padre de PID %d \n",i,getpid(),getppid());
			break;
		}
		else
         if (pid1 < 0) {
			   printf("No ha podido crearse un hijo en la jerarquia 2.");
			   return;
		   } else
            if (pid2 = (waitpid(pid1, 0, 0) > 0))
               break;
	}
}
