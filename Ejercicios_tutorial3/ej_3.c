#include <stdio.h>
#include <stdlib.h>

typedef struct estudiante {
    char* nombre;
    char* carrera;
 } estudiante_t;

typedef struct universidad {
    char* nombre;
    int cant_inscriptos;
    estudiante_t* estudiantes;
 } universidad_t;

universidad_t* nueva_Universidad(char* nombre, int cupo){ //ponemos cupo para hacerlo mas facil, es la maxima cantidad de estudiantes que puede haber (y la cantidad que se espera)

    return ;
}

void agregar_alumno(universidad_t* uni, char* nombre, char* carrera){

}

void liberar_Universidad(universidad_t* uni){
}

int main() {
    universidad_t* udesa = nueva_Universidad("UdeSA", 5);


    agregar_alumno(udesa, "Martina", "Ingeniería en IA");
    agregar_alumno(udesa, "Juan", "Ciencias del Comportamiento");


    printf("Universidad: %s\n", udesa->nombre);
    printf("Cantidad de inscriptos: %d\n", udesa->cant_inscriptos);
    for (int i = 0; i < udesa->cant_inscriptos; i++) {
        printf("Estudiante %d: %s - %s\n", i + 1, udesa->estudiantes[i].nombre, udesa->estudiantes[i].carrera);
    }

  
    liberar_Universidad(udesa);
    return 0;
}


