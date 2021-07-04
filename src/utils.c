#include <stdlib.h>

int rand_range(int lower, int upper) {
    return (rand() % (upper - lower)) + lower;
}
