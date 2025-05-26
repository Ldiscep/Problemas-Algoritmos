#include <stdio.h>
#include <stdlib.h>

void ejercicio(const char *buffer, unsigned int len){
  int cant_palabras = 1;

  for (int i = 0; i < len; i++){
    
    if (buffer[i] == ' ') {
      cant_palabras++;
      printf("\n");
      continue;
    }
    printf("%c", buffer[i]);
  }
  printf("Cantidad de palabras: %d\n", cant_palabras);

}

int main(int argc, char **argv) {
  char *buffer = NULL;
  size_t len;
  int read = getline(&buffer, &len, stdin);
  if (read != -1) {
    ejercicio(buffer, len);
  } else {
    printf("No se leyó ninguna línea\n");
  }

  free(buffer);
  return 0;
}

