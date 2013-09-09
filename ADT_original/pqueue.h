#ifndef _PQUEUE_H
#define _PQUEUE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "heap.h"

/************************************************************************/
/*                      Declare a structure for heaps.                  */
/************************************************************************/
typedef Heap PQueue;


/************************************************************************/
/* ------------------------- Public Interface ------------------------- */
/************************************************************************/
/*
Return Value None.
Description Initializes the priority queue specified by pqueue. This operation
must be called for a priority queue before it can be used with any other operation. 
The compareargument is a function used by various priority queue operations in 
maintaining the priority queue¡¯s heap property. This function should
return 1 if key1>key2,0ifkey1=key2, and ¨C1 if key1<key2for a priority
queue in which large keys have a higher priority. For a priority queue in which
smaller keys have a higher priority,compareshould reverse the cases that return 1
and ¨C1. Thedestroyargument provides a way to free dynamically allocated data
whenpqueue_destroyis called. For example, if the priority queue contains data
dynamically allocated usingmalloc, destroyshould be set tofree to free the data
as the priority queue is destroyed. For structured data containing several 
dynamically allocated members, destroyshould be set to a user-defined function that
callsfree for each dynamically allocated member as well as for the structure itself.
For a priority queue containing data that should not be freed,destroyshould be
set to NULL.
Complexity O(1)
*/
extern PQueue pqueue_create(int (*compare)(const ElmtType key1, const ElmtType key2), \
				 void (*destroy)(ElmtType data));
/*
Return Value None.
Description Destroys the priority queue specified bypqueue. No other operations
are permitted after calling pqueue_destroyunlesspqueue_createis called again.
Thepqueue_destroyoperation extracts all nodes from a priority queue and calls
the function passed as destroyto pqueue_create once for each node as it is
extracted, provideddestroywas not set to NULL.
Complexity O(n), wherenis the number of nodes in the priority queue.
*/
extern void pqueue_destroy(PQueue queue);
/*
Description Inserts an node into the priority queue specified by pqueue.
The new node contains a pointer todata, so the memory referenced by data
should remain valid as long as the node remains in the priority queue. It is the
responsibility of the caller to manage the storage associated withdata.
Complexity O(lgn), wherenis the number of nodes in the priority queue.
*/
extern int pqueue_insert(PQueue queue, const ElmtType data);
/*
Return Value 0 if extracting the node is successful, or ¨C1 otherwise.
Description Extracts the node at the top of the priority queue specified by
pqueue. Upon return, datapoints to the data stored in the node that was
extracted. It is the responsibility of the caller to manage the storage associated
with the data.
Complexity O(lgn), wherenis the number of nodes in the priority queue.
*/
extern int pqueue_extract(PQueue queue,ElmtType* data);
/*
Return Value Highest priority node in the priority queue, or NULL if the priority queue is empty.
Description Inline Function that evaluates to the highest priority node in the priority
queue specified bypqueue.
*/
extern ElmtType pqueue_peek(const PQueue queue);
/*
Return Value Number of nodes in the priority queue.
Description Inline Function that evaluates to the number of nodes in the priority
queue specified by pqueue.
Complexity O(1)
*/
extern int pqueue_size(const PQueue queue);

extern void pqueue_debug(const PQueue queue);

#ifdef __cplusplus
}
#endif

#endif