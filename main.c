#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lib.h"


int main(void)
{
    IntVector vec;
    vec_init(&vec);

    for (int i = 0; i < 10; i++)
    {
        if (!vec_push(&vec, i * 10))
        {
            vec_free(&vec);
            return 1;
        }
    }

    for (size_t i = 0; i < vec.size; i++)
    {
        int value;
        if (vec_get(&vec, i, &value))
        {
            printf("%d ", value);
        }
    }

    printf("\nsize: %zu\n", vec.size);
    printf("capacity: %zu\n", vec.capacity);

    vec_free(&vec);
    return 0;
}
