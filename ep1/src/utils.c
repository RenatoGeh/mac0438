/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: utils.c                                              **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int gp_counter = 0;

pid_t new_proc(int (*proc_callback) (int), int arg, int *res) {
  pid_t pid = fork();
  ++gp_counter;
  if (pid < 0) {
    /* Error. */
    fprintf(stderr, "Process creation error.\n");
  } else if (pid == 0) {
    /* Child process. */
    LOG("Process %d created.", gp_counter);
    *res = proc_callback(arg);
    exit(0);
  }

  /* Parent process. Do nothing. */

  return pid;
}

double urand(void) {
  return ((double)rand())/((double)RAND_MAX+1);
}

int uirand(int min, int max) {
  return (int)(urand()*(max-min+1) + min);
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
