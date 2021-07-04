#ifndef NIKITA_SG_UTILS
#define NIKITA_SG_UTILS

#include <stdlib.h>

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })
    
#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
   
#define calloc2(var, x, y) \
  var = calloc(x, sizeof(*var)); \
  for (int i = 0; i < x; i++) { \
    var[i] = calloc(y, sizeof(var[0])); \
  }

int rand_range(int lower, int upper);

#endif
