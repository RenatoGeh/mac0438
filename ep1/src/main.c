/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: main.c                                               **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*#define DEBUG*/

#include "utils.h"
#include "sort.h"
#include "fib.h"
#include "buffon.h"
#include "integ.h"

int (*fcs[4]) (int) = {sort, fib, buffon, integ};

int main(int argc, char *args[]) {
  int argv[4], i, r;
  pid_t pids[4];

  if (argc < 5)
    fprintf(stderr, "Too few arguments! Terminating execution.");

  for (i=0;i<4;++i)
    argv[i] = atoi(args[i+1]);

  /* Launches all processes "simultaneously". */
  for (i=0;i<4;++i)
    pids[i] = new_proc(fcs[i], argv[i], &r);

  for (i=0;i<4;++i) {
    waitpid(pids[i], NULL, 0);
    LOG("Process %d joined.", i);
  }

  return 0;
}
