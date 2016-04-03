/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: integ.c                                              **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#include "integ.h"

#include <math.h>

#include "utils.h"

#define SEC_1 1.85081571768
#define sec(x) (1.0/cos(x))

int integ(int s) {
  double x, y;
  int i, t=0;

  LOG_STR("Process integ started.");

  for (i=0;i<s;++i) {
    x = udrand(0, 1);
    y = udrand(0, SEC_1);
    if (y <= sec(x))
      ++t;
  }

  LOG("Computed area (t/s)*sec(1) = %.5f", ((double)t/(double)s)*SEC_1);
  LOG_STR("Expected area int_0^1 sec(x) dx = 1.2261911708835");

  LOG_STR("Process integ ready to join.");

  return 0;
}
