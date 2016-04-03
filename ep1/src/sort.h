/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: sort.h                                               **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#ifndef SORT_H_
#define SORT_H_

#include "utils.h"

#ifdef DEBUG
void heap_sort(int v[], int s);
#endif

/** Sorts through heapsort. */
int sort(int m);

#endif
