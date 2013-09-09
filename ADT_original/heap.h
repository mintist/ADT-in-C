#ifndef _HEAP_H
#define _HEAP_H


#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************/
/* Includes                                                             */
/************************************************************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/************************************************************************/
/*                      Declare a structure for heaps.                  */
/************************************************************************/
typedef struct Heap_t* Heap;
typedef void* ElmtType;

/************************************************************************/
/* ------------------------- Public Interface ------------------------- */
/************************************************************************/

/*
Return Value None.
Description Initializes the heap specified by heap. This operation must be
called for a heap before the heap can be used with any other operation. The
compare argument is a function used by various heap operations to compare
nodes when fixing the heap. This function should return 1 if key1>key2,0 if
key1=key2, and 每1 if key1<key2 for a top-heavy heap. For a bottom-heavy
heap,compare should reverse the cases that return 1 and 每1. The destroy
argument provides a way to free dynamically allocated data when heap_destroy is
called. For example, if the heap contains data dynamically allocated using malloc,
destroy should be set to free to free the data as the heap is destroyed. For
structured data containing several dynamically allocated members, destroy
should be set to a user-defined function that calls free for each dynamically 
allocated member as well as for the structure itself. For a heap containing data that
should not be freed,destroy should be set to NULL.
Complexity O(1)
*/
extern Heap heap_create(int (*compare)(const ElmtType key1, const ElmtType key2), \
			   void (*destroy)(ElmtType data));
/*
Return Value None.
Description Destroys the heap specified by heap. No other operations are
permitted after calling heap_destroy unless heap_create is called again. The heap_
destroy operation removes all nodes from a heap and calls the function passed as
destroy to heap_create once for each node as it is removed, provided destroy was
not set to NULL.
Complexity O(n), where n is the number of nodes in the heap.
*/
extern void heap_destroy(Heap heap);
/*
Return Value 0 if inserting the node is successful, or 每1 otherwise.
Description Inserts a node into the heap specified by heap. The new node
contains a pointer to data, so the memory referenced by data should remain
valid as long as the node remains in the heap. It is the responsibility of the caller
to manage the storage associated with data.
Complexity O(lgn), where n is the number of nodes in the heap.
*/
extern int heap_insert(Heap heap, const ElmtType data);
/*
Return Value 0 if extracting the node is successful, or 每1 otherwise.
Description Extracts the node at the top of the heap specified by heap. Upon
return, data points to the data stored in the node that was extracted. It is the
responsibility of the caller to manage the storage associated with the data.
Complexity O(lgn), where n is the number of nodes in the heap.
*/
extern int heap_extract(Heap heap, ElmtType* data);
/*
Return Value Number of nodes in the heap.
Description Inline Function that evaluates to the number of nodes in the heap specified by heap.
Complexity O(1)
*/
extern int heap_size(const Heap heap);

extern ElmtType heap_peek(const Heap heap);

extern void heap_debug(const Heap heap);

#ifdef __cplusplus
}
#endif

#endif