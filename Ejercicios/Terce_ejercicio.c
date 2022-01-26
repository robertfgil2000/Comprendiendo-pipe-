#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>  // Se agregó la librería time para eliminar los errores implícitos de invocación

#define READ  0
#define WRITE 1

char* mayorOMenorA500(int num){
  if (num < 500) return "menor que 500\n";
  else return "mayor o igual a 500\n";
}

int tamanioBuffer(int num){
 if (num < 500) return 14;
 else return 21;
}

int main(int argc, char *argv[]) {
  
  srand(time(NULL));
  int numeroAleatorio;
  char* mensajePadre;
  char* mensajeHijo;
  /*
  int numeroRandom = rand() % 1000 + 1;

  printf(mayorOMenorA500(numeroRandom));
  */
  
  pid_t pid;
  int   fd[2];

  if (pipe(fd) == -1) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork()) {

  case 0:
    // The child process will execute wc.
    // Close the pipe write descriptor.
    close(fd[WRITE]);
    
    read(READ, mensajePadre , tamanioBuffer(numeroAleatorio));
    //printf(mensajeHijo);
    close(fd[READ]);

  case -1:
    perror("fork() failed)");
    exit(EXIT_FAILURE);

  default:
    // Close the pipe read descriptor.
    close(fd[READ]);

    // Se hace la operación del número aleatorio con su respectivo mensaje
     numeroAleatorio= rand() % 1000 + 1;
     mensajePadre = mayorOMenorA500(numeroAleatorio);
     //printf(mensajePadre);
     //printf("xd");
    
    // Se procede a escribir el mensaje en la entrada del pipe
    write(WRITE, mensajePadre, tamanioBuffer(numeroAleatorio)); 
    // Se cierra el canal de escritura del pipe
    close(fd[WRITE]);
  }

 
  
}
