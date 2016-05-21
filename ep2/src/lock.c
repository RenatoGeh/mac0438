#include "lock.h"

#include <stdio.h>
#include <stdarg.h>

#include <pthread.h>

mutex_t end_lock  = PTHREAD_MUTEX_INITIALIZER;

mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

int tprintf(const char *format, ...) {
  int res;
  va_list args;

  mutex_lock(&print_lock);
  va_start(args, format);
  res = vprintf(format, args);
  va_end(args);
  mutex_unlock(&print_lock);

  return res;
}

int tputs(const char *str) {
  int res;

  mutex_lock(&print_lock);
  res = puts(str);
  mutex_unlock(&print_lock);

  return res;
}
