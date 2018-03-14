#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define tamanio 1024
#define longnombre 50
#define MAX_CLIENTS 100

static void signal_hanlder(int sigNum){
    pid_t pid;
    char fifoproxy[longnombre];

    // Obtener PID del proceso hijo y eliminar su fifo asociado
    pid = wait(NULL);
}

int main(int argc, char *argv[]){
    int fde, fds, fdc, tmp_cli;
    char nombrefifoe[longnombre];
    char nombrefifos[longnombre];
    char fifoproxy[longnombre];
    int leidos, proxypid;
    pid_t pid;

    // Comprobar que el programa funciona correctamente
    if (argc != 2){
        printf ("Uso: Servidor <nombre_fifo>");
        exit(-1);
    }

    // Manejador de señal SIGCHLD
    signal (SIGCHLD, signal_hanlder);

    // Componer el nombre del archivo fifo
    sprintf(nombrefifos, "%ss", argv[1]);
    sprintf(nombrefifoe, "%se", argv[1]);

    // Creamos los archivos fifo
    umask(0);
    mkfifo(nombrefifoe, 0666);
    mkfifo(nombrefifos, 0666);

    // Intentamos abrirlos
    if ((fds = open(nombrefifos, O_RDWR)) < 0){
        perror ("\nNo se pudo abrir el archivo fifo del servidor");
        exit(-1);
    }

    if ((fde = open(nombrefifoe, O_RDWR)) < 0){
        perror ("\nNo se pudo abrir el archivo fifo del cliente");
        exit(-1);
    }

    // Lanzar procesos mientras recibamos algo del fifo cliente
    while ((leidos = read(fde, &tmp_cli, sizeof(int))) != 0){
        pid = fork();

        if(pid == 0){

            // Obtener pid del nuevo proceso
            proxypid = getpid();

            // Construir cadena "proxy.getpid()" para el fifo
            sprintf(fifoproxy, "fifo.%d", proxypid);

            // Crear fifo
            umask(0);
            mkfifo(fifoproxy, 0666);

            // Escribir el PID del proxy en fifos
            write(fds, &proxypid, sizeof(int));

            // Abrir fifo de lectura
            int fifo = open(fifoproxy, O_RDONLY);

            // Redirigir entrada estandar a archivofifo
            execlp("./proxy", "proxy", NULL);
            exit(0);
        }
    }

    return 0;
}
