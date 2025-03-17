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
    int min = *array;
    int min_index = 0;
    for (int i = 1; i < length; i++){
        if (min > *(array + i)){
            min = *(array + i);
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
        *(array2+i) = *(array +i);
    }
    
    return array2;
    free(array2);
}
void selection_sort(int *array, int length){

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
    int *joined= (int*)malloc((length1+length2)*sizeof(int));
    int length_joined;
    for (int i = 0; i<(length1);i++){
        *(joined+i) = +*(array1+i);
        length_joined++;
    }
    for (int i=0; i< length1;  i++){
        for (int j = 0;j<length2; j++){
            if (*(array2+j) == *(array1+i)){
                break;
            }
            *(joined+length1+i)=*(array2+j);
            length_joined++;
        }
    }
    selection_sort(joined, length_joined);
    return joined;
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