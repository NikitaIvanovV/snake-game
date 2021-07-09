#ifndef NIKITA_SG_VECTOR_H
#define NIKITA_SG_VECTOR_H

#include <stdbool.h>

typedef struct
{
    int x, y;
} Vector;

Vector vector_sum(Vector x, Vector y);

Vector vector_scale(Vector vec, int num);

bool vector_eq(Vector x, Vector y);

#endif