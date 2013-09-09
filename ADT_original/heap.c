
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "heap.h"

/************************************************************************/
/*        Define private macros used by the heap implementation.        */
/************************************************************************/

/* General-purpose swap macro */
#define SWAP1(a, b) do {\
	char c[sizeof(a)]; \
	memcpy((void *)&c, (void *)&a, sizeof(c)); \
	memcpy((void *)&a, (void *)&b, sizeof(a)); \
	memcpy((void *)&b, (void *)&c, sizeof(b)); \
} while (0)

#define SWAP2(a, b, n) do {\
	char c[n]; \
	memcpy((void *)&c, (void *)&a, n); \
	memcpy((void *)&a, (void *)&b, n); \
	memcpy((void *)&b, (void *)&c, n); \
} while (0)


#define heap_parent(ipos) ((int)((ipos-1)/2))
#define heap_left(ipos) ((ipos)*2+1)
#define heap_right(ipos) ((ipos)*2+2)

/************************************************************************/
/*                  Define a structure for heaps.                       */
/************************************************************************/
typedef struct Heap_t{
	int size;

	int (*compare)(const ElmtType key1, const ElmtType key2);
	void (*destroy)(ElmtType data);

	ElmtType* tree;
}*Heap;

/*
The heap_create operation initializes a heap so that it can be used in other operations 
(see Example 10-2). Initializing a heap is a simple operation in which we set
the size member of the heap to 0, the destroy member to destroy, and the
tree pointer to NULL.
The runtime complexity of heap_create is O(1) because all of the steps in initializing
a heap run in a constant amount of time.
*/
Heap heap_create(int (*compare)(const ElmtType key1, const ElmtType key2), \
			   void (*destroy)(ElmtType data))
{
	Heap heap;
	if((heap = (Heap )malloc(sizeof(struct Heap_t))) == NULL)
		printf("memory is not enough when malloc for heap !\n");

	heap->size = 0;
	heap->compare = compare;
	heap->destroy = destroy;
	heap->tree = NULL;

	return heap;
}

/*
The heap_destroy operation destroys a heap (see Example 10-2). Primarily this
means removing all nodes from the heap. The function passed as destroy to
heap_create is called once for each node as it is removed, provided destroy was
not set to NULL.
The runtime complexity of heap_destroy is O(n), where n is the number of nodes
in the heap. This is because we must traverse all nodes in the heap in order to
free the data they contain. If destroy is NULL, heap_destroy runs in O(1) time
*/
void heap_destroy(Heap heap)
{
	int i;
	if(heap == NULL)
		return;
	
	for (i=0 ;i < heap->size; i++)
	{
		heap->destroy(heap->tree[i]);
	}
	heap->size = 0;
	free(heap->tree);
	heap->tree = NULL;

	free(heap);
}
/*
The heap_insert operation inserts a node into a heap (see Example 10-2). The call
sets the new node to point to the data passed by the caller. To begin, we reallocate 
storage to enable the tree to accommodate the new node. The actual process
of inserting the new node initially places it into the last position in the array.
When this causes the heap property to be violated, we must reheapify the tree
(see Figure 10-2).
To reheapify a tree after inserting a node, we need only consider the branch in
which the new node has been inserted, since the tree was a heap to begin with.
Starting at the new node, we move up the tree level by level, comparing each
child with its parent. At each level, if a parent and child are in the wrong order,
we swap their contents. This process continues until we reach a level at which no
swap is required, or we reach the top of the tree. Last, we update the size of the
heap by incrementing the size member of the heap data structure.
The runtime complexity of heap_insert is O(lgn), where n is the number of nodes
in the tree. This is because heapification requires moving the contents of the new
node from the lowest level of the tree to the top in the worst case, a traversal of
lg n levels. All other parts of the operation run in a constant amount of time.
*/
int heap_insert(Heap heap, const ElmtType data)
{
	int ipos,ppos;

	assert(NULL != heap);
	if(NULL == (heap->tree = (ElmtType*)realloc(heap->tree, (heap->size+1)*sizeof(ElmtType))))
		return -1;
	heap->tree[heap->size] = (ElmtType)data;
	
	ipos = heap->size;
	ppos = heap_parent(ipos);

	while(ipos>0 && heap->compare(heap->tree[ppos],heap->tree[ipos])<0)//extracted max
	{
		SWAP1(heap->tree[ppos], heap->tree[ipos]);

		ipos = ppos;
		ppos = heap_parent(ipos);
	}

	heap->size++;
	return 0;
}

/*
The heap_extract operation extracts the node at the top of a heap (see
Example 10-2). To begin, we set data to point to the data stored in the node
being extracted. Next, we save the contents of the last node, reallocate a smaller
amount of storage for the tree, and decrease the tree size by 1. After we are 
certain this has succeeded, we copy the contents of the saved last node to the root
node. When this causes the heap property to be violated, we must reheapify the
tree (see Figure 10-3).
To reheapify a tree after extracting a node, we start at the root node and move
down the tree level by level, comparing each node with its two children. At each
level, if a parent and its children are in the wrong order, we swap their contents
and move to the child that was the most out of order. This process continues until
we reach a level at which no swap is required, or we reach a leaf node. Last, we
update the size of the heap by decreasing the size member of the heap data
structure by 1.
The runtime complexity of heap_extract is O(lg n), where n is the number of
nodes in the tree. This is because heapification requires moving the contents of
the root node from the top of the tree to a leaf node in the worst case, a traversal
of lg n levels. All other parts of the operation run in a constant amount of time.
*/
int heap_extract(Heap heap, ElmtType* data)
{
	int ipos, lpos, rpos, mpos;

	assert(NULL != heap && heap->size > 0);

	*data = heap->tree[0];		//extracted the root node's data
	heap->tree[0] = heap->tree[heap->size-1];	//Copy the last node to the top.

	if (heap->size > 1)			//more than one modes
	{
		if(NULL == (heap->tree = (ElmtType*)realloc(heap->tree, (heap->size-1)*sizeof(ElmtType))))
			return -1;
		heap->size--;
	} 
	else						//only has one node
	{
		heap->size = 0;
		free(heap->tree);
		heap->tree = NULL;
		return 0;
	}
	/************************************************************************/
	/* Heapify the tree by pushing the contents of the new top downward.    */
	/************************************************************************/
	ipos = 0;

	while(1)
	{		
		lpos = heap_left(ipos);
		rpos = heap_right(ipos);

		if (lpos < heap->size && \
			heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
		{
			mpos = lpos;
		} 
		else
		{
			mpos = ipos;
		}

		if (rpos < heap->size && \
			heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
		{
			mpos = rpos;
		}

		if (mpos == ipos)
		{
			return 0;
		}
		else
		{
			SWAP1(heap->tree[ipos], heap->tree[mpos]);
			ipos = mpos;
		}
	}
}

/*
This macro evaluates to the number of nodes in a heap (see Example 10-1). It
works by accessing the size member of the Heap structure.
The runtime complexity of heap_size is O(1) because accessing a member of a
structure is a simple task that runs in a constant amount of time.
*/
__inline int heap_size(const Heap heap)
{
	return heap->size;
}

__inline ElmtType heap_peek(const Heap heap)
{
	return heap->tree == NULL ? NULL : heap->tree[0];
}

void heap_debug(const Heap heap)
{
	int i;
	if (heap->size > 0)
	{
		printf("heap->size = %d \n", heap->size);
		for (i=0;i<heap->size;i++)
		{
			printf("*(heap->tree[%d]) = %d\n", i, *((int *)(heap->tree[i])));
		}
		printf("\n");
	}
}