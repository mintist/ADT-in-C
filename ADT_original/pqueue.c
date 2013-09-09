
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pqueue.h"


__inline PQueue pqueue_create(int (*compare)(const ElmtType key1, const ElmtType key2), \
				 void (*destroy)(ElmtType data))
{
	return heap_create(compare,destroy);
}

__inline void pqueue_destroy(PQueue queue)
{
	heap_destroy(queue);
}
__inline int pqueue_insert(PQueue queue, const ElmtType data)
{
	return heap_insert(queue, data);
}
__inline int pqueue_extract(PQueue queue,ElmtType* data)
{
	return heap_extract(queue, data);
}
__inline ElmtType pqueue_peek(const PQueue queue)
{
	return heap_peek(queue);
}
__inline int pqueue_size(const PQueue queue)
{
	return heap_size(queue);
}

__inline void pqueue_debug(const PQueue queue)
{
	heap_debug(queue);
}