/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: debug.h                                              **/
/**                                                               **/
/** Renato Lui Geh | 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/


#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG

#include "lock.h"

/* Prints log. */
#define LOG(str, ...) tprintf("LOG: "str"\n", __VA_ARGS__)
/* Prints raw string. */
#define SLOG(str) tputs("LOG: "str)

#else

#define LOG(str, ...)
#define SLOG(str)

#endif

#endif
