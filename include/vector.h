#ifndef NIKITA_SG_VECTOR
#define NIKITA_SG_VECTOR

#include <stdbool.h>

typedef struct
{
    int x, y;
} Vector;

Vector vector_sum(Vector x, Vector y);

bool vector_eq(Vector x, Vector y);

Vector vector_scale(Vector vec, int num);

#endif