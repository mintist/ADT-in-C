
#define DATA_SIZE sizeof(int)



int slt_sort(void* data, int size, int esize, \
			 int (*compare)(const void* key1, const void* key2));
int bubl_sort(void* data, int size, int esize, \
			 int (*compare)(const void* key1, const void* key2));
int shaker_sort(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2));

/*
Return Value 0 if sorting is successful, or 每1 otherwise.
Description Uses insertion sort to sort the array of nodes indata. The
number of nodes indatais specified by size. The size of each node is
specified by esize. The function pointer compare specifies a user-defined 
function to compare nodes. This function should return 1 if key1>key2,0ifkey1
=key2, and 每1 if key1<key2for an ascending sort. For a descending sort,
compareshould reverse the cases returning 1 and 每1. When issort returns, data
contains the sorted nodes.
Complexity O(n2), wherenis the number of nodes to be sorted.
*/
int ins_sort(void* data, int size, int esize, \
					int (*compare)(const void* key1, const void* key2));

int shell_sort(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2));

/*
Return Value 0 if sorting is successful, or 每1 otherwise.
Description Uses quicksort to sort the array of nodes indata. The number of 
nodes indatais specified by size. The size of each node is specified by esize. 
The arguments iandkdefine the current partition being sorted
and initially should be 0 and size 每 1, respectively. The function pointer
comparespecifies a user-defined function to compare nodes. It should perform 
in a manner similar to that described for issort. When qksortreturns, data
contains the sorted nodes.
Complexity O(nlg n), wherenis the number of nodes to be sorted
*/
int quik_sort1(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2));

int quik_sort2(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2));

int merge_sort(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2));

int heap_sort(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2));

int radix_sort(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2));