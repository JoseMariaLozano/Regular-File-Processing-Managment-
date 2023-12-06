#include <errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 80

int createOutputFile(int input_file){
  int output_file;
  char buffer[BUFFER_SIZE];
  char *output_filename = "salida.txt";

  if ( (output_file = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666) ) < 0){
    perror("Error creating output file");
    return -1;
  }

  int bytes_read;
  unsigned int block = 0;

  while ( (bytes_read = read(input_file, buffer, BUFFER_SIZE)) > 0){
    
    char bloque_str[BUFFER_SIZE];
    sprintf(bloque_str, "Bloque %d:\n// Datos leidos en el bloque %d\n", block, block);
    write(output_file, bloque_str, strlen(bloque_str));
    write(output_file, buffer, bytes_read);
    write(output_file, "\n\n", 2);

    block++;
  }

  close(output_file);
  close(input_file);

  return output_file;
}

int main (int argc, char **argv) {

  int input_file;

  if ( argc == 1) {
    input_file = STDIN_FILENO;

  } 
  else if ( argc == 2 ){

    char * input_filename = argv[1];
    input_file = open(input_filename, O_RDONLY);
    if (input_file == -1){
      perror("Error opening input file");
      exit(EXIT_FAILURE);

    }
  } 
  else {
    perror("Error, usage: ./outputFormatting <file_pathname> (could receive none pathname stdin will be used)");
    exit(EXIT_FAILURE);
  }

  if ( createOutputFile(input_file) == -1){
    perror("Exiting program...");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
