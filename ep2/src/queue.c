/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: queue.c                                              **/
/**                                                               **/
/** Renato Lui Geh | 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/

#include "queue.h"

#include <stdlib.h>

queue_t* create_queue(int n) {
  queue_t *q;

  q = (queue_t*) malloc(sizeof(queue_t));

  q->data = (int*) malloc(n*sizeof(int));
  q->f = q->l = 0;
  q->capacity = n;

  return q;
}

void queue_push(queue_t *q, int v) {
  q->data[((q->l)++)%(q->capacity)] = v;
}

int queue_pop(queue_t *q) {
  return q->data[(q->f)++];
}

void destroy_queue(queue_t *q) {
  free(q->data);
  free(q);
}
