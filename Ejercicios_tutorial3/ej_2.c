#include <stdio.h>
#include <stdlib.h>

typedef struct Persona {
    char* nombre;
    char* apellido;
    char* domicilio;
    int edad;
} Persona;

void masGrande(Persona** personas,int n){ //OJO que es un array de punteros a personas
    int edadpersona0= personas[0]->edad;
    char nombrepersona0= personas[0]->nombre;
    for (int i = 1; i < n; i++){
        int edadpersona= personas[i]->edad;
        if(edadpersona > edadpersona0) {
            edadpersona0 = edadpersona;
            nombrepersona0= personas[i]-> nombre;
        }
    }

        
    printf("la persona mas vieja es %c con %d años\n", nombrepersona0, edadpersona0);
}

int main() {
    // ejemplo
    Persona* personas[] = { //referencio a las personas porque hay que pasar un array de punteros a personas
        &(Persona){"Juan", "Pérez", "Calle 123", 30},
        &(Persona){"Ana", "Gómez", "Avenida 456", 45},
        &(Persona){"Luis", "Martínez", "Boulevard 789", 40}
    };
    masGrande(personas, 3);
    return 0;
}

