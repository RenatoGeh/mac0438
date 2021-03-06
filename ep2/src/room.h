/*******************************************************************/
/** MAC 438 - Programacao Concorrente                             **/
/** IME-USP - Primeiro Semestre de 2016                           **/
/** Prof. Marcel Parolin Jackowski                                **/
/**                                                               **/
/** Segundo Exercicio-Programa                                    **/
/** Arquivo: room.h                                               **/
/**                                                               **/
/** Renato Lui Geh | 8536030                                      **/
/**                                                               **/
/** 24/05/2016                                                    **/
/*******************************************************************/

#ifndef ROOM_H_
#define ROOM_H_

#include "student.h"
#include "queue.h"

/* Monitor room. */
typedef struct {
  /* Set of students currently present in the room. */
  student_t **s_v;
  /* Number of students inside room. */
  int n;
} room_t;

extern room_t *g_room;

/* Creates a room for the PARTY! <|:-) */
room_t* create_room(int n);

/* Pushes a student into the room. :D */
void room_push(room_t *r, student_t *s);

/* Pops a student from the room. :( */
void room_pop(room_t *r, student_t *s);

/* Number of students in the room. */
int room_size(room_t *r);

/* Signals to George, the guard. */
void room_signal(void);

/* Waits until the room is cleared. */
void room_wait(room_t *r);

int room_had_party(void);

/* Destroys the room. D: */
void destroy_room(room_t *r);

#endif
