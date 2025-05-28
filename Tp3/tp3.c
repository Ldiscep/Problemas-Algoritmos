#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define C_I 17000// capacidad inicial sugerida por el copilot 😶‍🌫️

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
unsigned long funcion_hash(const char *clave, size_t table_size) {
  unsigned long hash = 5381;
  int c;

  while ((c = *clave++)) {
      hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }

  return hash % table_size;
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
   unsigned long hashed_key = funcion_hash(key, dictionary->capacidad);
   int indice = (int)hashed_key;
  while (true){
    if (indice > dictionary->capacidad) return false; // Ensure indice does not exceed capacity
    if (dictionary->tabla[indice].ocupado == true) {
      indice++;
      continue;
    }
    // aca guardás una copia de key strcpy
    char *key2 = malloc(strlen(key) + 1);
    if (!key2) return false; 
    strcpy(key2, key);
    dictionary->tabla[indice].key = key2;
    dictionary->tabla[indice].value = value;
    dictionary->tabla[indice].ocupado = true;
    dictionary->tabla[indice].borrado = false;
    dictionary->cantidad++;
    return true;
  }
}

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
    unsigned long hashed_key = funcion_hash(key, dictionary->capacidad);
    int indice = (int)hashed_key;

    while (indice < dictionary->capacidad) {
        if (dictionary->tabla[indice].ocupado && !dictionary->tabla[indice].borrado) {
            if (strcmp(dictionary->tabla[indice].key, key) == 0) {
                *err = false;
                return dictionary->tabla[indice].value;
            }
        }
        indice++;
    }

    *err = true;
    return NULL;
}

bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true){ 

    if (hashed_key == (unsigned long)dictionary->tabla[indice].key) {
      dictionary->tabla[indice].ocupado = false;
      dictionary->tabla[indice].borrado= true;
      dictionary->cantidad --;
      return true;
    }
    else indice++;
    if (indice ==dictionary->capacidad) return false;
  }
  return false;
};

void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
    unsigned long hashed_key = funcion_hash(key, dictionary->capacidad);
    int indice = (int)hashed_key;

    while (indice < dictionary->capacidad) {
        if (dictionary->tabla[indice].ocupado && !dictionary->tabla[indice].borrado) {
            if (strcmp(dictionary->tabla[indice].key, key) == 0) {
                void *value = dictionary->tabla[indice].value;
                dictionary->tabla[indice].ocupado = false;
                dictionary->tabla[indice].borrado = true;
                dictionary->cantidad--;
                *err = false;
                return value;
            }
        }
        indice++;
    }

    *err = true;
    return NULL;
}

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true){ 

    if (hashed_key == (unsigned long)dictionary->tabla[indice].key) {
      return true;}
    else indice++;

    if (indice ==dictionary->capacidad) return false;
  }
  return true;
};
//ayuda
size_t dictionary_size(dictionary_t *dictionary) {  
  return dictionary->cantidad;
};


void dictionary_destroy(dictionary_t *dictionary){
  for (int idx=0; idx< dictionary->capacidad; idx++){
    free(dictionary->tabla[idx].key);
    //free(dictionary->tabla[idx].value);

  }
  free(dictionary->tabla);
  free(dictionary);

};
