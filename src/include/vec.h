/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: vec.h, header file for vector implementation
 * CREDITS: https://aticleworld.com/implement-vector-in-c/
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINED  -1
#define SUCCESS 0
#define VECTOR_INIT(vec) Vector vec;\
VectorInit(&vec)

/* Store and track the stored data */
typedef struct __vector_list
{
    void **items;
    int capacity;
    int total;
} _vector_list;

/* Structure contain the function pointer */
typedef struct _vector Vector;
struct _vector
{
    _vector_list vectorList;

    /* Function pointers */
    int (*pfVectorTotal)(Vector *);
    int (*pfVectorResize)(Vector *, int);
    int (*pfVectorAdd)(Vector *, void *);
    int (*pfVectorSet)(Vector *, int, void *);
    void *(*pfVectorGet)(Vector *, int);
    int (*pfVectorDelete)(Vector *, int);
    int (*pfVectorFree)(Vector *);
};

/**
 * Function which returns number of elements in vector
 * @param v - vector
*/
int VectorTotal(Vector *v);

/**
 * Resizes the vector
 * @param v - vector
 * @param capacity - capacity
*/
int VectorResize(Vector *v, int capacity);

/**
 * Inserts item in the vector
 * @param v - vector
 * @param capacity - item to insert
*/
int VectorPushBack(Vector *v, void *item);

/**
 * Changes value of element in the vector
 * @param v - vector
 * @param index - index of element in vector
 * @param item - value of new element
*/
int VectorSet(Vector *v, int index, void *item);

/**
 * Returns element from the vector
 * @param v - vector 
 * @param index - index of element in vector
*/
void *VectorGet(Vector *v, int index);

/**
 * Deletes element in the vector
 * @param v - vector
 * @param index - index of element in vector
*/
int VectorDelete(Vector *v, int index);

/**
 * Deleting entire vector
 * @param v - vector
 * @param index - index of element in vector
*/
int VectorFree(Vector *v);

/**
 * Creates new vector
 * @param v - vector
 * @param index - index of element in vector
*/
void VectorInit(Vector *v);
