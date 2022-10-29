/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: vec.h, header file for vector implementation
 * CREDITS: https://aticleworld.com/implement-vector-in-c/
*/

#include "include/vec.h"

int VectorTotal(Vector *v)
{
    int totalCount = UNDEFINED;
    if(v)
    {
        totalCount = v->vectorList.total;
    }
    return totalCount;
}

/**
 * Resizes the vector
 * @param v - vector
 * @param capacity - capacity
*/
int VectorResize(Vector *v, int capacity)
{
    int  status = UNDEFINED;
    if(v)
    {
        void **items = (void**)realloc(v->vectorList.items, sizeof(void *) * capacity);
        if (items)
        {
            v->vectorList.items = items;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}

/**
 * Inserts item in the vector
 * @param v - vector
 * @param capacity - item to insert
*/
int VectorPushBack(Vector *v, void *item)
{
    int  status = UNDEFINED;
    if(v)
    {
        if (v->vectorList.capacity == v->vectorList.total)
        {
            status = VectorResize(v, v->vectorList.capacity * 2);
            if(status != UNDEFINED)
            {
                v->vectorList.items[v->vectorList.total++] = item;
            }
        }
        else
        {
            v->vectorList.items[v->vectorList.total++] = item;
            status = SUCCESS;
        }
    }
    return status;
}

/**
 * Changes value of element in the vector
 * @param v - vector
 * @param index - index of element in vector
 * @param item - value of new element
*/
int VectorSet(Vector *v, int index, void *item)
{
    int  status = UNDEFINED;
    if(v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
            v->vectorList.items[index] = item;
            status = SUCCESS;
        }
    }
    return status;
}

/**
 * Returns element from the vector
 * @param v - vector 
 * @param index - index of element in vector
*/
void *VectorGet(Vector *v, int index)
{
    void *readData = NULL;
    if(v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
            readData = v->vectorList.items[index];
        }
    }

    return readData;
}

/**
 * Deletes element in the vector
 * @param v - vector
 * @param index - index of element in vector
*/
int VectorDelete(Vector *v, int index)
{
    int  status = UNDEFINED;
    int i = 0;
    if(v)
    {
        if ((index < 0) || (index >= v->vectorList.total))
            return status;
        v->vectorList.items[index] = NULL;
        for (i = index; (i < v->vectorList.total - 1); ++i)
        {
            v->vectorList.items[i] = v->vectorList.items[i + 1];
            v->vectorList.items[i + 1] = NULL;
        }
        v->vectorList.total--;
        if ((v->vectorList.total > 0) && ((v->vectorList.total) == (v->vectorList.capacity / 4)))
        {
            VectorResize(v, v->vectorList.capacity / 2);
        }
        status = SUCCESS;
    }
    return status;
}

/**
 * Deleting entire vector
 * @param v - vector
 * @param index - index of element in vector
*/
int VectorFree(Vector *v)
{
    int  status = UNDEFINED;
    if(v)
    {
        free(v->vectorList.items);
        v->vectorList.items = NULL;
        status = SUCCESS;
    }
    return status;
}

/**
 * Creates new vector
 * @param v - vector
 * @param index - index of element in vector
*/
void VectorInit(Vector *v)
{
    //init function pointers
    v->pfVectorTotal = VectorTotal;
    v->pfVectorResize = VectorResize;
    v->pfVectorAdd = VectorPushBack;
    v->pfVectorSet = VectorSet;
    v->pfVectorGet = VectorGet;
    v->pfVectorFree = VectorFree;
    v->pfVectorDelete = VectorDelete;
    //initialize the capacity and allocate the memory
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total = 0;
    v->vectorList.items = (void**)malloc(sizeof(void *) * v->vectorList.capacity);
}
