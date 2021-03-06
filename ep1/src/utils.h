/*******************************************************************/
/** MAC 438 - Programação Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Primeiro Exercício-Programa                                   **/
/** Arquivo: utils.h                                              **/
/**                                                               **/
/** Renato Lui Geh - 8536030                                      **/
/**                                                               **/
/** 04/04/2016                                                    **/
/*******************************************************************/


#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <sys/types.h>

/** Logs to stdout. */
#ifndef _LOG_
#define _LOG_
#define LOG(str, ...) fprintf(stdout, "LOG: "str"\n", __VA_ARGS__)
#define LOG_STR(str) fprintf(stdout, "LOG: "str"\n")
#define LOG_N(str, ...) fprintf(stdout, str, __VA_ARGS__)
#endif

/** Number of process created in total.
 */
extern int gp_counter;

/** Creates a new process.
 * proc_callback: function callback the new process should run.
 *           arg: proc_callback's argument.
 *           res: pointer to the return value of proc_callback.
 */
pid_t new_proc(int (*proc_callback) (int), int arg, int *res);

/** Generates a pseudo-random number uniformally distributed in range [0,1).
 */
double urand(void);

/** Generates a pseudo-random integer uniformally distributed in range [min, max].
 */
int uirand(int min, int max);

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
