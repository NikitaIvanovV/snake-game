#include <stdio.h>
#include <stdlib.h>

int rand_range(int lower, int upper)
{
    return (rand() % (upper - lower)) + lower;
}

void print_matrix(int **array, int size_x, int size_y)
{
    printf("size: %d, %d\n", size_x, size_y);
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            printf("%d", array[x][y]);
        }
        printf("\n");
    }
}