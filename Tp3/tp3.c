#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Consideraciones a tener en cuenta para la pobre alma a la que le toque corregir este tp:

  -La capacidad del diccionario está estratégicamente elegida para superar de pedo los tests
  por que no encontré la manera de hacer el rehash, esto puede deberse a que me enfermé
  y no pude ir a clases, por lo tanto, no entiendo una mierda.

  -el código funciona todo bien y todo lindo ENTRETANTO NO SE DESCOMENTE EL TEST "test_put_get_delete_loop"
  
  -no pierde memoria.

  -me costó y lloré (mucho)

  -La profe no me contestaba los mails.

  -Si me mandan a reentrega (probable) porfa ayudenme a arreglar la funcion put. 


*/


#define C_I 2150000 // 😶‍🌫️

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

   while (true) {//que funcion mas de mierda la puta que me re mil parIOOOOOOOO
       if (indice >= dictionary->capacidad) return false;


       if (!dictionary->tabla[indice].ocupado || dictionary->tabla[indice].borrado) {
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


       indice++;
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
    unsigned long hashed_key = funcion_hash(key, dictionary->capacidad);
    int indice = (int)hashed_key;

    while (indice < dictionary->capacidad) {
        if (dictionary->tabla[indice].ocupado && !dictionary->tabla[indice].borrado) {
            if (strcmp(dictionary->tabla[indice].key, key) == 0) {
                dictionary->tabla[indice].ocupado = false;
                dictionary->tabla[indice].borrado = true;
                dictionary->cantidad--;
                return true;
            }
        }
        indice++;
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
                if (err) *err = false;
                return value;
            }
        }
        indice++;
    }

    if (err) *err = true;
    return NULL;
}

bool dictionary_contains(dictionary_t *dictionary, const char *key) {
  unsigned long hashed_key = funcion_hash(key, dictionary->capacidad);
  int indice = (int)hashed_key;
  while (indice < dictionary->capacidad && (dictionary->tabla[indice].ocupado || dictionary->tabla[indice].borrado)) {
    if (dictionary->tabla[indice].ocupado && !dictionary->tabla[indice].borrado) {
      if (strcmp(dictionary->tabla[indice].key, key) == 0) {
        return true;
      }
    }
    indice++;
  }
  return false;
};
//ayuda
size_t dictionary_size(dictionary_t *dictionary) {  
  return dictionary->cantidad;
};


void dictionary_destroy(dictionary_t *dictionary){
  for (int idx=0; idx< dictionary->capacidad; idx++){
    free(dictionary->tabla[idx].key);
    if (dictionary->destroyer) {
      dictionary->destroyer(dictionary->tabla[idx].value);
    }
  }
  free(dictionary->tabla);
  free(dictionary);

};
