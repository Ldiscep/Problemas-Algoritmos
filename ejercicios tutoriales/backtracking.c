#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8  // Tamaño del laberinto
#define PATH 0
#define WALL 1
#define SOLUTION 2

// Coordenadas de inicio y fin
int startX = 1, startY = 1;
int endX = 2 * N - 1, endY = 2 * N - 1;
int borderLimit = 2 * N + 1;
// Direcciones para generar el laberinto (arriba, derecha, abajo, izquierda)
int directions[4][2] = {{0, 2}, {2, 0}, {0, -2}, {-2, 0}};

void generateMaze(int maze[borderLimit][borderLimit], int x, int y) {
    maze[y][x] = PATH;

    int dirIndex[4] = {0, 1, 2, 3};
    
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = dirIndex[i];
        dirIndex[i] = dirIndex[j];
        dirIndex[j] = temp;
    }

    for (int i = 0; i < 4; i++) {
        int dx = directions[dirIndex[i]][0];
        int dy = directions[dirIndex[i]][1];
        int nx = x + dx, ny = y + dy;
        int betweenX = x + dx / 2, betweenY = y + dy / 2;

        if (nx >= 0 && ny >= 0 && nx < borderLimit && ny < borderLimit && maze[ny][nx] == WALL) {
            maze[betweenY][betweenX] = PATH;
            generateMaze(maze, nx, ny);
        }
    }
}

/*
maze: Matriz de tamaño 2*N x 2*N . En cada posicion hay tres valores posibles:
PATH, indicando que hay camino para recorrer
WALL, que hay una pared
SOLUTION, indicando que es el camino para recorrer

x e y posiciones iniciales desde donde arrancar. Por lo general se la llama
en (0,0)

*/
//Devuelve 1 si existe un camino desde el inicio hasta el final del laberinto, 0 en caso contrario
//OJO que para ver una posicion del maze es maze[y][x]
int solveMaze(int maze[borderLimit][borderLimit], int x, int y) {
    if (maze[y][x] == SOLUTION) return 1;
    if(maze[y][x] == PATH) 
    return 1;
}

void printSolution(int maze[borderLimit][borderLimit]) {
    for (int y = 0; y < borderLimit; y++) {
        for (int x = 0; x < borderLimit; x++) {
            if (x == startX && y == startY) {
                printf("S");
            } else if (x == endX && y == endY) {
                printf("E");
            } else if (maze[y][x] == WALL) {
                printf("█");
            } else if (maze[y][x] == SOLUTION) {
                printf("•");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    int maze[borderLimit][borderLimit];

    // Inicializar el laberinto con paredes
    for (int i = 0; i < borderLimit; i++) {
        for (int j = 0; j < borderLimit; j++) {
            maze[i][j] = WALL;
        }
    }

    srand(time(0));

    // Generar e imprimir el laberinto
    generateMaze(maze, startX, startY);
    printf("Laberinto generado:\n");
    printSolution(maze);

    // Resolver el laberinto e imprimir la solución
    if (solveMaze(maze, startX, startY)) {
        printf("\nSolución del laberinto:\n");
        printSolution(maze);
    } else {
        printf("\nNo se encontró solución.\n");
    }

    return 0;
}