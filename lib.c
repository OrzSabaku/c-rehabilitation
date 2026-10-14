#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

const size_t BASE_CAPACITY = 4;

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
    // capacityについて条件を問う方が自然。
    // なぜならcapacityはバロメーターそのもの，dataは管理対象だから。
    if (vec->capacity == 0)
    {
        // mallocの失敗を考慮しよう。
        vec->data = malloc(sizeof(int) * BASE_CAPACITY);
        if (vec->data == NULL)
        {
            return false;
        }

        vec->capacity = BASE_CAPACITY;
        vec->size = 0;
    }

    if (vec->size == vec->capacity)
    {
        void *ret = realloc(vec->data, sizeof(int) * vec->capacity * 2);
        if (ret == NULL)
        {
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
    bool in_range = index < vec->size;
    if (!in_range)
    {
        return false;
    }

    *out = vec->data[index];
    return true;
}

void vec_free(IntVector *vec)
{
    // freeに関してはあえてNULLか否かを確認する必要がない
    free(vec->data);
    vec_init(vec);
}
