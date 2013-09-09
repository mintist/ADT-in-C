#include "include.h"
#ifdef TEST_STACK


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
	Stack stack;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	stack = stack_create(debug_free);

	//push data pointer
	for (i = 0;i < 10 ;i++)
	{
		stack_push(stack,data[i]);
		stack_debug(stack);
	}
	

	//pop data pointer
	for (i = 0; i < 8 ;i++)
	{
		stack_pop(stack,&data[i]);
		free(data[i]);
		stack_debug(stack);
	}

	stack_destroy(stack);

	return 0;
}
#endif