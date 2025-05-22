#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#define C_I 170// capacidad inicial sugerida por el copilot 😶‍🌫️

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
    if (indice > dictionary->capacidad) return false;
    if (dictionary->tabla[indice].ocupado == true) {
      indice ++;
      continue;
    }
    dictionary->tabla[indice].key = (char *)hashed_key;
    dictionary->tabla[indice].value= value;
    dictionary->tabla[indice].ocupado = true;
    dictionary->cantidad ++ ;
    return true;
  }
}

void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true || dictionary->tabla[indice].borrado==true ){ 

    if (hashed_key == (unsigned long)dictionary->tabla[indice].key) {
      err = false;
      return dictionary->tabla[indice].value;}
    else indice++;

    if (indice ==dictionary->capacidad) return false;
  }
  *err= true;
  return NULL;
}


bool dictionary_delete(dictionary_t *dictionary, const char *key) {
  
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true || dictionary->tabla[indice].borrado==true ){ 

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
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true || dictionary->tabla[indice].borrado==true ){ 

    if (hashed_key == (unsigned long)dictionary->tabla[indice].key) {
      dictionary->tabla[indice].ocupado = false;
      dictionary->tabla[indice].borrado= true;
      dictionary->cantidad --;
      * err= false;
      return dictionary->tabla[indice].value;
    }
    indice++;
    if (indice ==dictionary->capacidad) {*err=true ;return NULL;}
  }
  *err = true;
  return NULL;
};

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  unsigned long hashed_key =funcion_hash(key,dictionary->capacidad);
  int indice = (int)hashed_key;
  while (dictionary->tabla[indice].ocupado == true || dictionary->tabla[indice].borrado==true ){ 

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


void dictionary_destroy(dictionary_t *dictionary){};
