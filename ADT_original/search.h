


int linear_search(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2));

/*
Return Value Index of the target if found, or ¨C1 otherwise.
Description Uses binary search to locate target in sorted, a sorted array of
nodes. The number of nodes in sorted is specified by size. The size of
each node is specified by esize. The function pointer compare specifies a
user-defined function to compare nodes. This function should return 1 if key1
>key2, 0 if key1=key2, and ¨C1 if key1<key2.
Complexity O(lg n), where n is the number of nodes to be searched.
*/
int binary_search(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2));




int fibonacci_search(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2));

int interpolation_search(void* sorted, void* target, int size, int esize, \
					 int (*compare)(const void* key1, const void* key2));