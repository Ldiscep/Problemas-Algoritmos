#include "tp1.h"
#include <stdio.h>
#include <stdlib.h>

bool are_friends_numbers(int x, int y){
   /*primer forma pero va a perder memoria y es un quilombo 
    int *dividers_x = malloc(x * sizeof(int));
    int *dividers_y = malloc(y * sizeof(int));*/
    int i;
    int sum_div_x=0;
    int sum_div_y=0;
    for (i=0; i <= x;i++){

        if (x%i==0){
            sum_div_x = sum_div_x + i;
        }

    }
    for (i=0; i <= y;i++){
        if (y%i == 0){
            sum_div_y=sum_div_y+i;
        }
    }
    if (sum_div_x == x && sum_div_y == y){
        return true;
    }
    return false;
}

int calculate_time_in_seconds(float di, float df, float v) {
    float distance = df-di;
    float time =distance / v;
    return time;
}

void swap(int *x, int *y) {
    int variable = *x;
    *x = *y;
    *y = variable;
    variable = 0; // para que no gaste memoria la desinicializo
    return;
}

int array_min_index(const int *array, int length) {
    return -1;
}

int *copy_array(const int *array, int length) {
    return NULL;
}

void selection_sort(int *array, int length){
    return;
}

int* array_union(const int *array1, int length1, const int *array2, int length2) {
    return NULL;
}

void matrix_map(Matriz matrix, int row_size, int col_size, int f(int)) {
    return;
}

Matriz copy_matrix(const Matriz matrix, int row_size, int col_size) {
    return NULL;
}

bool matrix_equal(const Matriz matrix1, int row_size1, int col_size1, const Matriz matrix2, int row_size2, int col_size2) {
    return true;
}

Matriz* copy_array_of_matrices(const Matriz *array_of_matrices, const Matriz matrix_dimensions, int array_lenght) {
    return NULL;
}

void free_array_of_matrices(Matriz* array_of_matrices, Matriz matrix_dimensions, int array_lenght) {
    return;
}

