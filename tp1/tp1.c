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
    if(x == y) return false;
    for (i=1; i < x;i++){

        if (x%i==0){
            sum_div_x = sum_div_x + i;
        }

    }
    for (i=1; i < y;i++){
        if (y%i == 0){
            sum_div_y=sum_div_y+i;
        }
    }
    if (sum_div_x == y &&sum_div_y == x){
        return true;
    }
    return false;
}

int calculate_time_in_seconds(float di, float df, float v) {
    float distance = df-di;
    if(v==0){return -1;}
    int time = (int)(distance / v);
    return abs(time);
}

void swap(int *x, int *y) {
    int variable = *x;
    *x = *y;
    *y = variable;
    variable = 0; // para que no gaste memoria la desinicializo
    return;
}

int array_min_index(const int *array, int length) {
    if(length == 0) return -1;
    int min = array[0];
    int min_index = 0;
    for (int i = 1; i < length; i++){
        if (min > array[i]){
            min = array[i];
            min_index = i;
        }
    }
    return min_index;
}

int *copy_array(const int *array, int length) {
    if (array == NULL){
        return NULL;
    }
    int *array2=(int *)malloc(length * sizeof(int));
    
    for (int i=0;i<length;i++){
        array2[i] = array[i];
    }

    return array2;
}

void selection_sort(int *array, int length){
    if (array == NULL) {
        return;
    }
    for (int i=0; i< length; i++){
        int j ;
        for (j=0; j<(length-i); j++){
            if (*(array+i) > *(array +i+j)){
                int temp;
                temp = *(array+i);
                *(array+i)=*(array+i+j);
                *(array+i+j) = temp;
            }
        }
    }
    return ;
}


int* array_union(const int *array1, int length1, const int *array2, int length2) {
    int *joined = (int *)malloc((length1 + length2) * sizeof(int));
    int len = 0;
    for (int i = 0; i < length1; i++) {
        joined[len++] = array1[i];
    }
    for (int j = 0; j < length2; j++) {
        int found = 0;
        for (int i = 0; i < length1; i++) {
            if (array2[j] == array1[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            joined[len++] = array2[j];
        }
    }
    selection_sort(joined, len);

    return joined;
}

void matrix_map(Matriz matrix, int row_size, int col_size, int f(int)) {
    if (f == NULL) {
        return;
    }
    
    for (int r = 0; r < row_size; r++){
        for (int c = 0; c < col_size; c++/*referencia*/){
            matrix[r][c]=f(matrix[r][c]);
        }
    }
    return;
}

Matriz copy_matrix(const Matriz matrix, int row_size, int col_size) {
    if (matrix == NULL) {
        return NULL;
    }
    Matriz matriz2 = (Matriz)malloc(row_size * sizeof(int *));
    for (int r = 0; r < row_size; r++) {
        matriz2[r] = (int *)malloc(col_size * sizeof(int));
        for (int c = 0; c < col_size; c++) {
            matriz2[r][c] = matrix[r][c];
        }
    }
    return matriz2;
}

bool matrix_equal(const Matriz matrix1, int row_size1, int col_size1, const Matriz matrix2, int row_size2, int col_size2) {
    if (matrix1 == NULL || matrix2 == NULL) {
        return matrix1 == matrix2;
    }
    if (col_size1 != col_size2 || row_size1 != row_size2) return false;
    for (int r = 0; r < row_size1; r++) {
        for (int c = 0; c < col_size1; c++) {
            if (matrix1[r][c] != matrix2[r][c]) return false;
        }
    }
    return true;
}
    
  


Matriz* copy_array_of_matrices(const Matriz *array_of_matrices, const Matriz matrix_dimensions, int array_lenght) {
    if (array_of_matrices == NULL || matrix_dimensions == NULL) {
        return NULL;
    }
    
    Matriz* new_array = (Matriz *)malloc(array_lenght * sizeof(Matriz));
    for (int i = 0; i < array_lenght; i++) {
        Matriz matrix = array_of_matrices[i];
        int row_size = matrix_dimensions[i][0];
        int col_size = matrix_dimensions[i][1];
        new_array[i] = (Matriz)malloc(row_size * sizeof(int *));
        for (int r = 0; r < row_size; r++) {
            new_array[i][r] = (int *)malloc(col_size * sizeof(int));
            for (int c = 0; c < col_size; c++) {
                new_array[i][r][c] = matrix[r][c];
            }
        }
    }
    return new_array;

}
    

void free_array_of_matrices(Matriz* array_of_matrices, Matriz matrix_dimensions, int array_length) {
    for (int i = 0; i< array_length; i++){
        int rows =matrix_dimensions[i][0];
        for (int r = 0; r < rows; r++){
            free(array_of_matrices[i][r]);
        }
        free(array_of_matrices[i]);
        }
    for (int i=0; i < array_length; i++){
        free(matrix_dimensions[i]);
    }
    free(matrix_dimensions);
    
    free(array_of_matrices);
    
}

