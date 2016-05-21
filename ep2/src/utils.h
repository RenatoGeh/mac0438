/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercício-Programa                                    **/
/** Arquivo: utils.h                                              **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/*******************************************************************/


#ifndef UTILS_H_
#define UTILS_H_

#include <sys/types.h>
#include <pthread.h>
#include <time.h>

/* Renames struct timespec to timespec_t. */
typedef struct timespec timespec_t;

/* Milliseconds. */
typedef long int ms_t;

/** Generates a pseudo-random number uniformally distributed in range [0,1).
 */
double urand(void);

/** Generates a pseudo-random integer uniformally distributed in range [min, max].
 */
int uirand(int min, int max);

/** Generates a pseudo-random long uniformall distributed in range [min, max].
 */
long int ulrand(long int min, long int max);

/** Generates a pseudo-random number uniformally distributed in range [min, max].
 */
double udrand(double min, double max);

/** Generates a pseudo-random number uniformally distributed in range [0, max].
 */
double udmrand(double max);

/** Generates a pseudo-random number uniformally distributed in range [min, max).
 */
double uderand(double min, double max);

#endif
