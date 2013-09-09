#include "include.h"

#ifdef TEST_HEAP

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static void debug_free(void* data)
{
	printf("%d is freeing \n",*(int*)data);
	free(data);
}
int compare(const ElmtType key1, const ElmtType key2)
{
	if (*(int*)key1 > *(int*)key2)
	{
		return 1;
	} 
	else
	{
		if (*(int*)key1 < *(int*)key2)
			return -1;
		else
			return 0;
	}
}

int main(void)
{
	int i;
	int* data[10];
	Heap heap = NULL;
	
	srand((unsigned int)time((time_t *)NULL));
	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = rand();
	}

	heap = heap_create(compare,debug_free);
	for (i=0;i<10;i++)
	{
		heap_insert(heap,data[i]);
		heap_debug(heap);
	}

	for (i=0;i<8;i++)
	{
		heap_extract(heap,&data[i+1]);
		heap_debug(heap);
		free(data[i+1]);
	}

	
	heap_destroy(heap);
	return 0;
}

#endif