#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#ifndef VECTOR_EXPORT
    #define VECTOR_EXPORT(SYM) SYM
#endif

#ifndef COPY_MULTIPLE
    #define COPY_MULTIPLE 1
#endif

struct VECTOR_EXPORT(vector) {
    uint32_t elmsize;
    uint32_t capacity;
    uint32_t len;
    uint8_t *v;
};

#define SUCCESS                 1
#define E_GENERIC               0
#define E_RANGE                 -1
#define E_CAPACITY              -2

#define COPY_MULTIPLE_IN(vc, idx, vl) {\
    switch (v->elmsize) {\
        case 1:\
            vc->v[idx] = *((int8_t *)(vl));\
            break;\
        case 2:\
            ((int16_t *)vc->v)[idx] = *((int16_t *)(vl));\
            break;\
        case 4:\
            ((int32_t *)vc->v)[idx] = *((int32_t *)(vl));\
            break;\
        default:\
            memcpy(&(vc->v[vc->elmsize*idx]), (vl), vc->elmsize);\
            break;\
    }\
}

/**
* Get error message for error code.
**/
const char *
VECTOR_EXPORT(vector_errmsg)(int r)
{
    switch (r) {
        case 0:
            return "Generic Error";
        case -1:
            return "Out Of Range";
        case -2:
            return "Capacity Exceeded";
    }
    
    if (r < 1) {
        return "Unknown Error";
    }
    
    return "No Error";
}

/**
* Create new vector.
**/
struct VECTOR_EXPORT(vector *)
VECTOR_EXPORT(vector_new)
(uint32_t capacity, size_t elmsize)
{
    struct VECTOR_EXPORT(vector *) v;
    
    if (!(v = malloc(sizeof(*v)))) return NULL;
    if (!(v->v = malloc(elmsize * capacity))) return NULL;
    
    memset(v->v, 0, elmsize * capacity);
    v->elmsize = elmsize;
    v->capacity = capacity;
    v->len = 0;
    
    return v;
}

/**
* Delete vector, and memory associated with it.
**/
void
VECTOR_EXPORT(vector_delete)
(struct VECTOR_EXPORT(vector *) v)
{
    if (!v) return;
    if (v->v) free(v->v);
    free(v);
}

/**
* Get length of vector.
**/
uint32_t
VECTOR_EXPORT(vector_get_len)
(struct VECTOR_EXPORT(vector *) v)
{
    if (!v) return 0;
    return v->len;
}

/**
* Get element size of vector.
**/
uint32_t
VECTOR_EXPORT(vector_get_elmsize)
(struct VECTOR_EXPORT(vector *) v)
{
    if (!v) return 0;
    return v->elmsize;
}

/**
* Get capacity of vector.
**/
uint32_t
VECTOR_EXPORT(vector_get_capacity)
(struct VECTOR_EXPORT(vector *) v)
{
    if (!v) return 0;
    return v->capacity;
}

/**
* Resize vector.
**/
int
VECTOR_EXPORT(vector_resize)
(struct VECTOR_EXPORT(vector *)v, size_t capacity)
{
    uint8_t *nv;
    
    if (!v) return E_GENERIC;
    if (!(nv = realloc(v->v, v->elmsize * capacity))) return E_GENERIC;
    
    v->capacity = capacity;
    v->v = nv;
    return SUCCESS;
}

/**
* Clear (zero-out) all elements in vector.
**/
void
VECTOR_EXPORT(vector_clear)
(struct VECTOR_EXPORT(vector *)v)
{
    if (!v || !v->v) return;
    memset(v->v, 0, v->elmsize * v->capacity);
    v->len = 0;
}

/**
* Set item in vector at index.
**/
int
VECTOR_EXPORT(vector_set)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx, void *d)
{
    if (!v)                     return E_GENERIC;
    if (!(idx < v->capacity))   return E_CAPACITY;
    if (idx > v->len)           return E_RANGE;
    
    #if COPY_MULTIPLE
        COPY_MULTIPLE_IN(v, idx, d);
    #else
        memcpy(&(v->v[v->elmsize*idx]), d, v->elmsize);
    #endif
    
    v->len++;
    return SUCCESS;
}

/**
* Append item to end of vector.
**/
int
VECTOR_EXPORT(vector_append)
(struct VECTOR_EXPORT(vector *) v, void *d)
{
    if (!v)                         return E_GENERIC;
    if (!(v->len < v->capacity))    return E_CAPACITY;
    
    #if COPY_MULTIPLE
        COPY_MULTIPLE_IN(v, v->len, d);
    #else
        memcpy(&(v->v[v->elmsize*v->len]), d, v->elmsize);
    #endif
    
    v->len++;
    return SUCCESS;
}

/**
* Get pointer to data held at index.
**/
void *
VECTOR_EXPORT(vector_getptr)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx)
{
    if (!v || !(idx < v->len)) return NULL;
    return &(v->v[v->elmsize*idx]);
}

/**
* Copy data at index, to pointer dst.
**/
int
VECTOR_EXPORT(vector_getcpy)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx, void *dst)
{
    if (!v)                 return E_GENERIC;
    if (!(idx < v->len))    return E_RANGE;
    
    memcpy(dst, &(v->v[v->elmsize*idx]), v->elmsize);
    return SUCCESS;
}

/**
* Delete item at index, and possibly re-index vector.
**/
int
VECTOR_EXPORT(vector_del)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx)
{
    int i;
    if (!v)                 return E_GENERIC;
    if (!(idx < v->len))    return E_RANGE;
    
    memset(&(v->v[v->elmsize*idx]), 0, v->elmsize);
    for (i = (idx + 1); i < v->len; i++) {
        #if COPY_MULTIPLE
            COPY_MULTIPLE_IN(v, (i - 1), &v->v[v->elmsize * i]);
        #else
            memcpy(
                &v->v[v->elmsize * (i - 1)],
                &v->v[v->elmsize * i],
                v->elmsize);
        #endif
    }
    
    v->len--;
    return SUCCESS;
}
