/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: utils.c                                              **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/

#include "utils.h"

#include <stdlib.h>

#include <sys/types.h>
#include <pthread.h>

double urand(void) {
  return ((double)rand())/((double)RAND_MAX+1);
}

int uirand(int min, int max) {
  return (int)(urand()*(max-min+1) + min);
}

long int ulrand(long int min, long int max) {
  return (long int)(urand()*(max-min+1) + min);
}

double udrand(double min, double max) {
  return (urand()*(max-min+1)+min);
}

double udmrand(double max) {
  return (((double)rand())/((double)RAND_MAX))*max;
}

double uderand(double min, double max) {
  return (rand()/(RAND_MAX/(max-min))) + min;
}
