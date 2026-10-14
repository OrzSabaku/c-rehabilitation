#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void vec_init(IntVector *vec)
{
    vec->capacity = 0;
    vec->size = 0;
    vec->data = NULL;
}

/// @brief vecへの値のプッシュおよびメモリの管理
/// @param vec 管理対象
/// @param value 追加したい値
/// @return 成功したか否か
bool vec_push(IntVector *vec, int value)
{
    if (vec->data == NULL)
    {
        vec->capacity = 4;
        vec->size = 0;
        vec->data = malloc(sizeof(int) * vec->capacity);
    }

    if (vec->size == vec->capacity)
    {
        void *ret = realloc(vec->data, sizeof(int) * vec->capacity * 2);
        if (ret == NULL)
        {
            fprintf(stderr, "Failed to re-allocate memory");
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

    *out = vec->data[--vec->size];
    return true;
}

bool vec_get(const IntVector *vec,
             size_t index, int *out)
{
    bool inRange = index < vec->size;
    if (!inRange)
    {
        fprintf(stderr, "Invalid index");
        return false;
    }

    *out = vec->data[index];
    return true;
}

void vec_free(IntVector *vec)
{
    if (vec->data != NULL)
    {
        free(vec->data);
        vec_init(vec);
    }
}
