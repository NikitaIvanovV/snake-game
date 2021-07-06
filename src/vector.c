#include <stdbool.h>
#include "vector.h"

Vector vector_sum(Vector x, Vector y)
{
    Vector z = {x.x + y.x, x.y - y.y};
    return z;
}

Vector vector_scale(Vector vec, int num)
{
    Vector vec2 = {vec.x * num, vec.y * num};
    return vec2;
}

bool vector_eq(Vector x, Vector y)
{
    return ((x.x == y.x) && (x.y == y.y));
}
