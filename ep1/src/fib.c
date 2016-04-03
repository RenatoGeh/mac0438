#include "fib.h"

#include <stdio.h>

#include "utils.h"

unsigned long long int compute_fib(int n) {
  if (n < 3) return 1;
  else return compute_fib(n-1) + compute_fib(n-2);
}

int fib(int n) {
  LOG_STR("Process fib started.");

  LOG("Computing the %d-th Fibonacci number...", n);
  LOG("F(%d)=%llu", n, compute_fib(n));

  LOG_STR("Process fib ready to join.");

  return 0;
}
