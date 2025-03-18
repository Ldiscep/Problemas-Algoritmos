#include <stdio.h>
#include <stdlib.h>

int find_min_distance(int* nums, int nums_size) {
  int dist_min = nums_size;
  for (int i = 0; i < nums_size; i++) {
    int elem1 = nums[i];
    for (int j = i + 1; j < nums_size; j++) {
      int elem2 = nums[j];
      if (elem1 == elem2) {
        if (abs(j - i) < dist_min) {
          dist_min = abs(j - i);
        }
        break;
      }
    }
  }
  if (dist_min != nums_size) {
    return dist_min;
  }
  return -1;
}

// TESTS
typedef struct {
  int *array;
  int size;
  int expected;
} TestCase;
void run_tests() {
  int test_1[] = {1, 2, 3, 5, 6};
  int test_2[] = {1, 1, 1, 1, 1};
  int test_3[] = {3, 2, 1, 2, 3};
  int test_4[] = {};
  int test_5[] = {1, 2, 3, 1, 2, 3};

  TestCase tests[] = {
      {test_1, sizeof(test_1) / sizeof(test_1[0]), -1},
      {test_2, sizeof(test_2) / sizeof(test_2[0]), 1},
      {test_3, sizeof(test_3) / sizeof(test_3[0]), 2},
      {test_4, sizeof(test_4) / sizeof(test_4[0]), -1},
      {test_5, sizeof(test_5) / sizeof(test_5[0]), 3}
  };

  int num_tests = sizeof(tests) / sizeof(tests[0]);

  for (int i = 0; i < num_tests; i++) {
      printf("Prueba %d: Distancia mínima obtenida = %d (Esperado: %d) \n", 
             i + 1, find_min_distance(tests[i].array, tests[i].size), tests[i].expected);
  }
}

int main() {
    run_tests();
    return 0;
}
