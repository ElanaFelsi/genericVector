#include "genericVec.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint-gcc.h>

typedef struct Vector{
    void **m_data;
    size_t m_size;
    size_t m_capacity;
} Vector;


Vector* vectorCreate(size_t size)
{
    Vector *vector = malloc(sizeof(Vector));

    if(vector)
    {
        if(!size)
        {
            vector->m_capacity = size + 1;
        }
        else
        {
            vector->m_capacity = size;
        }
        vector->m_size = 0;
        vector->m_data =  malloc(sizeof(void*) * size);

        if(!vector->m_data)
        {
            free(vector);
            vector = NULL;
        }
    }

    return vector;
}

void vectorDestroy(Vector **vector)
{
    if(vector && *vector) {
        (*vector)->m_data = NULL;
        free((*vector)->m_data);
        free(*vector);
        *vector = NULL;
    }
}

void vectorResize(Vector *vector, size_t size)
{
    void **data = realloc(vector->m_data, sizeof(void*) * size);
    if (data)
    {
        vector->m_data = data;
        vector->m_capacity = size;
    }
}

ErrorCode vectorPush(Vector *vector, void *value)
{
    if(!vector)
    {
        return E_NULL_PTR;
    }

    if(vector->m_size >= vector->m_capacity)
    {
        vectorResize(vector, vector->m_capacity * 2);
    }

    vector->m_data[vector->m_size++] = value;

    return E_OK;
}

ErrorCode vectorInsert(Vector *vector, void *value, size_t index)
{
    if(index >= vector->m_size)
    {
        return E_BAD_INDEX;
    }

    if(index == vector->m_size)
    {
        return vectorPush(vector, value);
    }

    if(vector->m_size == vector->m_capacity)
    {
        vectorResize(vector, vector->m_capacity * 2);
    }
    size_t i = vector->m_size;
    for (; i > index; --i){
        vector->m_data[i] = vector->m_data[i-1];
    }
    vector->m_data[index] = value;
    ++vector ->m_size;
    return E_OK;
}

ErrorCode vectorPop(Vector *vector, void **res)
{
    if(vector->m_size == 0)
    {
        return E_NULL_PTR;
    }

    *res = vector->m_data[--vector->m_size];

    //--vector->m_size;

    return E_OK;
}

ErrorCode vectorRemove(Vector *vector, size_t index, void **res)
{
    if(index >= vector->m_size)
    {
        return E_BAD_INDEX;
    }

    *res = vector->m_data[--index];

    vector->m_data[index] = NULL;

    size_t i = index;
    for (; i < vector->m_size - 1; ++i) {
        vector->m_data[i] = vector->m_data[i + 1];
        vector->m_data[i + 1] = NULL;
    }
    --vector->m_size;

    return E_OK;

}

ErrorCode vectorGetElement(const Vector *vector, size_t index, void **res)
{
    if(index >= vector->m_size)
    {
        return E_BAD_INDEX;
    }
    *res = vector->m_data[--index];
    return E_OK;
}

ErrorCode vectorSetElement(Vector *vector, size_t index, void *value)
{
    if(index >= vector->m_size)
    {
        return E_BAD_INDEX;
    }
    vector->m_data[index] = value;
    return E_OK;
}


size_t vectorGetSize(const Vector *vector)
{
    return vector->m_size;
}

size_t vectorGetCapacity(const Vector *vector)
{
    return vector->m_capacity;
}

int my_strcmp( const char s1[], const char s2[])
{
    while(*s1 && *s1++ == *s2++);
    return (*--s1 - *--s2);
}

int compare_int(const Vector *vector, size_t index, void* value)
{
    return (int* )vector->m_data[index] == (int* ) value;
}

int compare_string(const Vector *vector, size_t index, void* value)
{
    return my_strcmp((char* )(vector)->m_data[index], (char* )value);
}
size_t vectorCount(const Vector *vector, void *value, compFunc compare)
{
    size_t i=0, count=0;
    size_t size = vectorGetSize(vector);
    for (;i < size;++i) {
        if(compare(vector, i, value))
        {
            ++count;
        }
    }
    return count;
}

void *vectorGet(const Vector *vector, size_t index)
{
    if (index >= 0 && index < vector->m_size)
        return vector->m_data[index];
    return NULL;
}

void vectorPrint(const Vector *vector)
{
    printf("capacity= %zu\n", vector->m_capacity );
    printf("size= %zu\n", vector->m_size );
    size_t i=0;
    size_t size = vectorGetSize(vector);
    printf("data: ");
    for(;i < size; i++)
    {
        printf("%p, ",  (vector->m_data[i]));
    }
    printf("\n");
}

#ifdef _DEBUG
void vectorPrint(const Vector *vector)
{
    printf("capacity= %zu\n", vector->m_capacity );
    printf("size= %zu\n", vector->m_size );
    size_t i=0;
    size_t size = vectorGetSize(vector);
    printf("data: ");
    for(;i < size; i++)
    {
        printf("%p, ", (vector->m_data[i]));
    }
    printf("\n");
}
#endif /* _DEBUG */

