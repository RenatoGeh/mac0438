/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: sort.c                                               **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#include "sort.h"

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

#define LEFT(i) (2*(i)+1)
#define RIGHT(i) (2*(i)+2)
#define PARENT(i) ((int)((i)/2))

#define GET_LEFT(v, i) (v)[LEFT(i)]
#define GET_RIGHT(v, i) (v)[RIGHT(i)]
#define GET_PARENT(v, i) (v)[(int)((i)/2)]

#define SWAP(a, b, t) ((t)=(b),(b)=(a),(a)=(t))

/* Heap sort implementation. */

void heapify(int v[], int s, int i) {
  int max = i;
  int l = LEFT(i), r = RIGHT(i);

  if (l < s && v[l] > v[max])
    max = l;
  if (r < s && v[r] > v[max])
    max = r;

  if (max != i) {
    int t;
    SWAP(v[i], v[max], t);
    heapify(v, s, max);
  }
}

void heap_sort(int v[], int s) {
  int i;

  for (i=s/2-1;i>=0;--i)
    heapify(v, s, i);

  for (i=s-1;i>=0;--i) {
    int t;
    SWAP(v[0], v[i], t);
    heapify(v, i, 0);
  }
}

/* Heap sort callback function. */

#define RAND_SEED 37901268

int sort(int m) {
  int *array, i;

  LOG_STR("Process sort started");

  srand(RAND_SEED);

  array = (int*) malloc(m*sizeof(int));

  LOG("Generating %d integers in range [0, 100) with seed %d.\nA = {", m, RAND_SEED);

  for (i=0;i<m-1;++i) {
    array[i] = uirand(0, 100);
    LOG_N("%d, ", array[i]);
  }
  array[m-1] = uirand(0, 100);
  LOG_N("%d\n}\n", array[m-1]);

  LOG_STR("Heap sorting...");

  heap_sort(array, m);

  LOG_STR("Resulting sorted array:\n  A = {");
  for (i=0;i<m-1;++i)
    LOG_N("%d, ", array[i]);
  LOG_N("%d\n}\n", array[m-1]);

  LOG_STR("Process sort ready to join.");

  return 0;
}
