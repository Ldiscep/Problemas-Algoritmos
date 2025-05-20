#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#define C_I 17 // capacidad inicial sugerida por el copilot 😶‍🌫️

typedef struct {
  char *key;
  void *value;
  bool ocupado;// si esta celda está ocupada
  bool borrado; // para distinguir entre nunca usado y borrado
} hash_entry_t;
struct dictionary {
  hash_entry_t *tabla;
  size_t capacidad;
  size_t cantidad;
  destroy_f destroyer;
};
unsigned long funcion_hash(const char *clave, int table_size) {
  unsigned long hash = 5381;
  int c;

  while ((c = *clave++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }

  return hash % (unsigned int)table_size;
}



dictionary_t *dictionary_create(destroy_f destroy) {
  dictionary_t *dic = malloc(sizeof(dictionary_t));
  if (!dic) return NULL;
  dic->capacidad=C_I;
  dic->cantidad=0;
  dic->destroyer=destroy;
  dic->tabla = calloc(dic->capacidad, sizeof(hash_entry_t));
  if (!dic->tabla) {
      free(dic);
      return NULL;
  }

  return dic;
};

bool dictionary_put(dictionary_t *dictionary, const char *key, void *value) {
return false;
};

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  return NULL;
};

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  return true;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  return true;
};

size_t dictionary_size(dictionary_t *dictionary) { return 0; };

void dictionary_destroy(dictionary_t *dictionary){};
