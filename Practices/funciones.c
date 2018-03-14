#include <unistd.h>		// Biblioteca: manejo de directorios y archivos.
#include <stdio.h>		// Biblioteca: funciones de entrada y salida.
#include <stdlib.h>		// Biblioteca: gestión de memoria y procesos.
#include <sys/types.h>// Biblioteca: busqueda, ordenamiento y manipulación de archivos y directorios.
#include <sys/stat.h>	// Biblioteca: metadatos de archivos.
#include <fcntl.h>		// Biblioteca: operaciones de control sobre el descriptor del archivo.
#include <errno.h>		// Biblioteca: informes de errores.
#include <string.h>		// Biblioteca: operaciones con cadenas de caracteres.
#include <stdbool.h>	// Biblioteca: tipo dato bool.
#include <dirent.h>   // Biblioteca: manejo de carpetas.
#include <ftw.h>      // Biblioteca: recorrido en arbol de direcorios.
#include <signal.h>   // Biblioteca: manejo de señales.
#include <limits.h>   // Biblioteca: rango de variables.

// Función que recibe un archivo como parametro y devuelve su tamaño.
int size_file (char * file) ;

// Función que recibe un directorio como parametro y devuelve los elementos que contiene.
int length_dir (char * dir) ;

// Función que recibe un directorio y me devuelve la lista de archivos.
char ** list_file (char * dir, bool full) ;

// Función que comprueba si un fichero es un directorio.
bool is_directory (char * file) ;

// Función que realiza una busqueda sobre una carpeta.
bool search (char * file, char * dir) ;

// Función que busca un fichero en un sistema de carpetas.
bool recursive_search (char * file, char * dir) ;

// Función que cuenta el numero de veces que aparece un archivo en un sistema de carpetas.
int recursive_length_dir (char * dir ) ;

// Función que cuenta el número de carpetas dentro de una carpeta.
int number_dir (char * dir) ;

// Función que realiza la lista de carpetas de una carpeta.
char ** list_dir (char * dir, bool full) ;

int main(int argc, char *argv[]) {

  if ( recursive_search (argv[1], argv[2]) )
    printf ( "Encontrado " ) ;


  return (EXIT_SUCCESS) ;
}

int size_file (char * file) {
  // DECLARACIÓN DE VARIABLES
  struct stat metadatos ;
  int size = -1 ;

  // Asignacion de metadatos.
	int metadatos_true = stat ( file , & metadatos ) ;

  // Comprobación de metadatos.
  if (metadatos_true >= 0) {
    size = metadatos.st_size ;
  }

  // SALIDA DE DATO
	return (size) ;
}

int length_dir (char * dir) {
  // DECLARACIÓN DE VARIABLES
	DIR * directorio = NULL ;
	int length = -1 ;
	struct dirent * estructura ;

	// Asignación del flujo al directorio.
	directorio = opendir ( dir ) ;

  // Comprobación de carpeta.
  if (directorio != NULL) {
    length = 0 ;
  	// CÁLCULOS
  	while ( estructura = readdir ( directorio ) ) {
  		if ( strcmp ( estructura->d_name , "." ) ) {
  			if ( strcmp ( estructura->d_name , ".." ) ) {
  				length++ ;
  			}
  		}
  	}
  }

	// SALIDA DE DATOS
	return ( length ) ;
}

char ** list_file (char * dir, bool full) {
  // DECLARACIÓN DE VARIABLES
  char ** list ;
  const int LENGTH = length_dir (dir) ;
  DIR * directorio = NULL ;
	struct dirent * estructura ;
  int i = 0 ;

  // Asignación del flujo al directorio.
	directorio = opendir ( dir ) ;

  if (directorio != NULL) {
    // Asignamos el numero de filas deseadas.
    list = (char **) malloc (LENGTH * sizeof (char *)) ;

    while ( estructura = readdir ( directorio ) ) {
      if ( strcmp ( estructura->d_name , "." ) ) {
  			if ( strcmp ( estructura->d_name , ".." ) ) {
          if (!full) {
            int size = strlen(estructura->d_name) ;
            list[i] = (char *) malloc (size * sizeof(char)) ;
            strcpy (list[i], estructura->d_name) ;
          }
          else {
            int size = strlen(dir) + sizeof("/") +  strlen(estructura->d_name) ;
            list[i] = (char *) malloc (size * sizeof(char)) ;
            strcpy (list[i], dir) ;
            strcat (list[i], "/") ;
            strcat (list[i], estructura->d_name) ;
          }
          i++ ;
  			}
  		}
    } // Fin del while
  } // Fin de comprobación de directorio.
  return (list) ;
}

bool is_directory (char * file) {
  struct stat metadatos ;

  if ( lstat(file, & metadatos) < 0 ) {
    return (false) ;
  }
  if ( S_ISDIR(metadatos.st_mode) ) {

    return (true) ;
  }
  return (false) ;
}

bool search (char * file, char * dir) {
  // Comprobación de que es una carpeta.
  if (!is_directory(dir)) {
    return (false) ;
  }

  // DECLARACIÓN DE VARIABLES
  const int LENGTH = length_dir (dir) ;
  char ** list = list_file (dir,false) ;
  bool existe = false ;

  // CÁLCULOS Y SALIDA DE DATOS
  for (int i = 0 ; i < LENGTH && !existe ; i++) {
    printf("comprobando: %s\n", list[i]);
    if ( strcmp (file, list[i]) == 0 ) {
      existe = true ;
    }
  }

  for (int i = 0 ; i < LENGTH ; i++) {
    free (list[i]) ;
  }
  free (list) ;

  return (existe) ;
}

bool recursive_search (char * file, char * dir ) {
  // Comprobación de que es una carpeta.
  if (!is_directory(dir) || length_dir(dir) <= 0) {
    return (false) ;
  }
  // Comprobación de que esta el archivo en la carpeta actual.
  if ( search (file, dir) ) {
    return (true) ;
  }

  // DECLARACIÓN DE CONSTANTES
  const int LENGTH = number_dir (dir) ;

  printf("%s\n", dir);

  // DECLARACIÓN DE VARIABLES
  char ** list_dir_long = list_dir (dir,true) ;

  for (int i = 0 ; i < LENGTH ; i++) {
    if ( recursive_search (file, list_dir_long[i]) ) {
      return (true) ;
    }
  }

  for (int i = 0 ; i < LENGTH ; i++) {
    free (list_dir_long[i]) ;
  }
  free (list_dir_long) ;

  return (false) ;
}

int recursive_length_dir (char * dir ) {
  // Comprobación de que es una carpeta.
  if (!is_directory(dir)) {
    return (false) ;
  }

  // DECLARACIÓN DE VARIABLES
  const int LENGTH = length_dir (dir) ;
  char ** list = list_file (dir,true) ;
  int occurrence = 0 ;
  char * new_p_dir = NULL ;

  for (int i = 0 ; i < LENGTH ; i++) {
    if ( is_directory(list[i]) ) {
      occurrence += recursive_length_dir (list[i]) ;
    }
    else {
      occurrence++ ;
    }
  }

  return (occurrence) ;
}

int number_dir (char * dir) {
  // DECLARACIÓN DE VARIABLES
	DIR * directorio = NULL ;
	int length = -1 ;
	struct dirent * estructura ;

	// Asignación del flujo al directorio.
	directorio = opendir ( dir ) ;

  // Comprobación de carpeta.
  if (directorio != NULL) {
    length = 0 ;
  	// CÁLCULOS
  	while ( estructura = readdir ( directorio ) ) {
  		if ( strcmp ( estructura->d_name , "." ) ) {
  			if ( strcmp ( estructura->d_name , ".." ) ) {
          int size = strlen(dir) + sizeof("/") +  strlen(estructura->d_name) ;
          char * new_p_dir = (char *) malloc (size * sizeof(char)) ;
          strcpy (new_p_dir, dir) ;
          strcat (new_p_dir, "/") ;
          strcat (new_p_dir, estructura->d_name) ;
          if ( is_directory(new_p_dir) ) {
  				  length++ ;
          }
  			}
  		}
  	}
  }

	// SALIDA DE DATOS
	return ( length ) ;
}

char ** list_dir (char * dir, bool full) {
  // DECLARACIÓN DE VARIABLES
  char ** list ;
  const int LENGTH = length_dir (dir) ;
  DIR * directorio = NULL ;
	struct dirent * estructura ;
  int i = 0 ;

  // Asignación del flujo al directorio.
	directorio = opendir ( dir ) ;

  if (directorio != NULL) {
    // Asignamos el numero de filas deseadas.
    list = (char **) malloc (LENGTH * sizeof (char *)) ;

    while ( estructura = readdir ( directorio ) ) {
      if ( strcmp ( estructura->d_name , "." ) ) {
  			if ( strcmp ( estructura->d_name , ".." ) ) {
          int size = strlen(dir) + sizeof("/") +  strlen(estructura->d_name) ;
          char * new_p_dir = (char *) malloc (size * sizeof(char)) ;
          strcpy (new_p_dir, dir) ;
          strcat (new_p_dir, "/") ;
          strcat (new_p_dir, estructura->d_name) ;
          if (is_directory(new_p_dir)) {
            if (!full) {
              int size = strlen(estructura->d_name) ;
              list[i] = (char *) malloc (size * sizeof(char)) ;
              strcpy (list[i], estructura->d_name) ;
            }
            else {
              int size = strlen(dir) + sizeof("/") +  strlen(estructura->d_name) ;
              list[i] = (char *) malloc (size * sizeof(char)) ;
              strcpy (list[i], dir) ;
              strcat (list[i], "/") ;
              strcat (list[i], estructura->d_name) ;
            }
            i++ ;
          }
  			}
  		}
    } // Fin del while
  } // Fin de comprobación de directorio.
  return (list) ;
}
