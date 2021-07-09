#ifndef NIKITA_SG_UTILS_H
#define NIKITA_SG_UTILS_H

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
  ({ var = calloc(x, sizeof(*var)); \
    for (int i = 0; i < x; i++) { \
      var[i] = calloc(y, sizeof(var[0])); \
    } })

#define free2(var, x) \
  ({ for (int i = 0; i < x; i++) { \
      free(var[i]); \
    } \
    free(var); })

int rand_range(int lower, int upper);

void print_matrix(int **array, int size_x, int size_y);

#endif
