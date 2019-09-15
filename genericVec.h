#ifndef C_GENERIC_VECTOR_ELANAFELSI_GENERICVEC_H
#define C_GENERIC_VECTOR_ELANAFELSI_GENERICVEC_H

#include <stddef.h>

typedef enum
{
    E_OK,
    E_NULL_PTR,
    E_UNDERFLOW,
    E_ALLOCATION_ERROR,
    E_BAD_INDEX
} ErrorCode;

typedef struct Vector Vector;

Vector* vectorCreate(size_t size);
void vectorDestroy(Vector **vector);

void vectorResize(Vector *vector, size_t size);

/* Adds an item at the end. Grows if needed (by * 2) */
ErrorCode vectorPush(Vector *vector, void *value);

/* Adds an item at a certain position and shifts. Grows if needed (by * 2) */
ErrorCode vectorInsert(Vector *vector, void *value, size_t index);

/* Clears the item at the end */
ErrorCode vectorPop(Vector *vector, void **res);

/* Clears an item at a certain position and shifts. */
ErrorCode vectorRemove(Vector *vector, size_t index, void **res);

ErrorCode vectorGetElement(const Vector *vector, size_t index, void **res);
ErrorCode vectorSetElement(Vector *vector, size_t index, void *value);

size_t vectorGetSize(const Vector *vector);
size_t vectorGetCapacity(const Vector *vector);

typedef int(*compFunc) (const Vector *vector, size_t index, void* value);

/* Counts how many instances of a given value there are. */
size_t vectorCount(const Vector *vector, void *value, compFunc compare);

int my_strcmp( const char s1[], const char s2[]);

int compare_int(const Vector *vector, size_t index, void* value);

int compare_string(const Vector *vector, size_t index, void* value);


void vectorPrint(const Vector *vector);


#ifdef _DEBUG
void vectorPrint(const Vector *vector);
#endif /* _DEBUG */


#endif
