/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: student.h                                            **/
/**                                                               **/
/** Renato Lui Geh | 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/

#ifndef STUDENT_H_
#define STUDENT_H_

#include <sys/types.h>
#include <time.h>

#include "utils.h"

/* 1 if all students have left; 0 otherwise. */
extern int has_ended;

typedef struct {
  /* ID. */
  int id;
  /* pthread ID. */
  pthread_t pid;
  /* Arrival time. */
  timespec_t st;
  /* Stay time. */
  timespec_t dt;
} student_t;

/* Creates a student. */
student_t* create_student(ms_t t, ms_t r);

/* Executes a student's thread. */
int start_student(student_t *st);

void* student_func(void* arg);

void join_student(student_t *s);

void destroy_student(student_t *s);

#endif
