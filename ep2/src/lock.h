#ifndef LOCK_H_
#define LOCK_H_

#include <pthread.h>

/* Mutex. */
typedef pthread_mutex_t mutex_t;
/* Conditional variable. */
typedef pthread_cond_t cond_t;

/* P */
#define mutex_lock(arg) pthread_mutex_lock(arg)
/* V */
#define mutex_unlock(arg) pthread_mutex_unlock(arg)
/* destroy */
#define mutex_destroy(arg) pthread_mutex_destroy(arg)

/* wait */
#define cond_wait(cond, lock) pthread_cond_wait(cond, lock)
/* signal */
#define cond_signal(arg) pthread_cond_signal(arg)
/* broadcast */
#define cond_broadcast(arg) pthread_cond_broadcast(arg)
/* destroy */
#define cond_destroy(arg) pthread_cond_destroy(arg)

/* A special thread-safe printf. */
int tprintf(const char *format, ...);
/* A special thread-safe puts. */
int tputs(const char *str);

/* Globals. */

/* End mutex. */
extern mutex_t end_lock;

#endif
