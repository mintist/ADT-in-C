#include "include.h"

#ifdef TEST_PQUEUE

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
	PQueue pqueue = NULL;

	srand((unsigned int)time((time_t *)NULL));
	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = rand();
	}

	pqueue = pqueue_create(compare,debug_free);
	for (i=0;i<10;i++)
	{
		pqueue_insert(pqueue,data[i]);
		pqueue_debug(pqueue);
	}

	for (i=0;i<8;i++)
	{
		pqueue_extract(pqueue,&data[i+1]);
		pqueue_debug(pqueue);
		free(data[i+1]);
	}


	pqueue_destroy(pqueue);
	return 0;
}

#endif