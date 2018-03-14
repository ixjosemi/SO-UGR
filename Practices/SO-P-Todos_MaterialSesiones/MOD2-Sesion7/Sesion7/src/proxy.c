#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BLOCK_FILE "blockfile"

void lockunlock(int dbloqueo, int orden){
    struct flock cerrojo;

    // Inicio el cerrojo
    cerrojo.l_type = orden;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    // Si ya esta bloqueado, el proceso se duerme
    if (fcntl(dbloqueo, F_SETLKW, &cerrojo) == -1){
        perror ("Proxy: problemas al bloquear la impresion");
        exit(1);
    }
}

int main(int argc, char *argv[]){
    char buffer[1024];
    int nbytes, dbloqueo;
    FILE *tmp = tmpfile();
    char fifoproxy[256];

    // Leer bloques de 1024 bytes y escribirlos en tmpfile
    while ((nbytes = read(STDIN_FILENO, buffer, 1024)) > 0){
        fwrite(buffer, sizeof(char), nbytes, tmp);
    }

    // Abrir archivo "cerrojo"
    if ((dbloqueo = open(BLOCK_FILE, O_RDWR)) == 1)
        printf("Error al abrir blockfile\n");

    // Bloquear cerrojo
    lockunlock(dbloqueo, F_WRLCK);

    // Inicio de EM
    // Leer tmp hasta el final
    while (!feof(tmp)){
        fread(buffer, sizeof(char), 1024, tmp);

        // Escribir en la salida
        write(STDOUT_FILENO, buffer, 1024);
    }

    // Fin de EM
    // Desbloquear cerrojo
    lockunlock(dbloqueo, F_UNLCK);

    // Eliminar el fifo antes de terminar
    sprintf(fifoproxy, "fifo.%d", getpid());
    unlink(fifoproxy);

    exit (0);
}
