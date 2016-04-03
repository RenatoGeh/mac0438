#include "buffon.h"

#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define PI 3.14159265
#define G 1.0
#define L 1.0

#define RAND_SEED 314159265

int buffon(int r) {
  int i, t=0;
  double d, theta, disc;

  LOG_STR("Process buffon started.");

  srand(RAND_SEED);

  LOG("Generating %d samples...", r);

  for (i=0;i<r;++i) {
    d = uderand(0, G);
    theta = uderand(0, 2*PI);
    disc = d + L*sin(theta);
    if (disc <= 0 || disc >= G)
      ++t;
  }

  LOG("Computed probability Pr(0 > d + L*sin(theta) > G) = t/r = %.5f", ((double)t)/((double)r));
  LOG("Expected probability Pr(0 > d + L*sin(theta) > G) = (2/PI)*(L/G) = %.5f", (2.0/PI)*(L/G));

  LOG_STR("Process buffon ready to join.");

  return 0;
}
