#pragma once

#include <stdbool.h>

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

extern const size_t BASE_CAPACITY;
