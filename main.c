#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct IntVector
{
    int *data;
    // 要素数
    size_t size;
    // 最大要素数
    size_t capacity;
} IntVector;

void vec_init(IntVector *vec);
bool vec_push(IntVector *vec, int value);
bool vec_pop(IntVector *vec, int *out);
bool vec_get(const IntVector *vec,
             size_t index, int *out);
void vec_free(IntVector *vec);

void vec_init(IntVector *vec)
{
    vec->capacity = 4;
    vec->size = 0;
    vec->data = malloc(sizeof(int) * vec->capacity);
    if (vec->data == NULL)
    {
        free(vec->data);
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

bool vec_push(IntVector *vec, int value)
{
    if (vec->size == vec->capacity)
    {
        void *ret = realloc(vec->data, sizeof(int) * vec->capacity * 2);
        if (ret == NULL)
        {
            perror("Failed to re-allocate memory");
            return false;
        }
        vec->data = ret;
        vec->capacity *= 2;
    }

    vec->data[vec->size++] = value;
    return true;
}

bool vec_pop(IntVector *vec, int *out)
{
    if (vec->size == 0)
    {
        return false;
    }

    *out = vec->data[vec->size-- - 1];
    return true;
}

bool vec_get(const IntVector *vec,
             size_t index, int *out)
{
    if (index >= vec->size - 1)
    {
        perror("Invalid index");
        return false;
    }

    *out = vec->data[index];
    return true;
}

void vec_free(IntVector *vec)
{
    free(vec->data);
}

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
