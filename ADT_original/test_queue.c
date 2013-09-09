#include "include.h"

#ifdef TEST_QUEUE


#include <stdlib.h>
#include <stdio.h>

static void debug_free(void* data)
{
	printf("%d is freeing \n",*(int*)data);
	free(data);
}

int main(void)
{
	int i;
	int* data[10];
	Queue queue;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	queue = queue_create(debug_free);

	//enqueue data pointer
	for (i = 0;i < 10 ;i++)
	{
		queue_enqueue(queue,data[i]);
		queue_debug(queue);
	}


	//dequeue data pointer
	for (i = 0; i < 8 ;i++)
	{
		queue_dequeue(queue,&data[i]);
		free(data[i]);
		queue_debug(queue);
	}

	queue_destroy(queue);

	return 0;
}
#endif