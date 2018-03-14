// Ejercicio 3 de la sesion 5 del modulo 2
// Jose Miguel Hernandez Garcia
// 2º C

#include <stdio.h>
#include <signal.h>

int main(){

	sigset_t new_mask;

	// inicializar la nueva mascara de señales
	sigemptyset(&new_mask);
	sigfillset(&new_mask);
	sigdelset(&new_mask , SIGUSR1);

	// esperar a cualquier señal menos a SIGUSR1
	sigsuspend(&new_mask);
}
