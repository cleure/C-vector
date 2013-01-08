#pragma once

#ifndef VECTOR_EXPORT
    #define VECTOR_EXPORT(SYM) SYM
#endif

typedef void * VECTOR_EXPORT(vector_ptr);

extern
const char *
VECTOR_EXPORT(vector_errmsg)(int r);

extern
struct VECTOR_EXPORT(vector *)
VECTOR_EXPORT(vector_new)
(uint32_t capacity, size_t elmsize);

extern
void
VECTOR_EXPORT(vector_delete)
(struct VECTOR_EXPORT(vector *) v);

extern
uint32_t
VECTOR_EXPORT(vector_get_len)
(struct VECTOR_EXPORT(vector *) v);

extern
uint32_t
VECTOR_EXPORT(vector_get_elmsize)
(struct VECTOR_EXPORT(vector *) v);

extern
uint32_t
VECTOR_EXPORT(vector_get_capacity)
(struct VECTOR_EXPORT(vector *) v);

extern
int
VECTOR_EXPORT(vector_resize)
(struct VECTOR_EXPORT(vector *)v, size_t capacity);

extern
void
VECTOR_EXPORT(vector_clear)
(struct VECTOR_EXPORT(vector *)v);

extern
int
VECTOR_EXPORT(vector_set)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx, void *d);

extern
int
VECTOR_EXPORT(vector_append)
(struct VECTOR_EXPORT(vector *) v, void *d);

extern
void *
VECTOR_EXPORT(vector_getptr)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx);

extern
int
VECTOR_EXPORT(vector_getcpy)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx, void *dst);

extern
int
VECTOR_EXPORT(vector_del)
(struct VECTOR_EXPORT(vector *) v, uint32_t idx);
