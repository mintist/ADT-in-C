#include "include.h"

#ifdef TEST_DLIST


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
	DList list;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	list = dlist_create(debug_free);

	//insert node as head
	for (i = 0;i < 5 ;i++)
	{
		dlist_ins_prev(list,NULL,data[i]);
		dlist_debug(list);
	}

	//insert node as tail
	for (i = 0;i < 5 ;i++)
	{
		dlist_ins_next(list,NULL,data[i+5]);
		dlist_debug(list);
	}


	//remove head node
	for (i = 0; i < 5 ;i++)
	{
		dlist_rmv(list, NULL, &data[i]);
		free(data[i]);
		dlist_debug(list);
	}

	//remove tail node
	for (i = 0; i < 2 ;i++)
	{
		dlist_rmv(list, dlist_tail(list), &data[i+5]);
		free(data[i+5]);
		dlist_debug(list);
	}

	//remove head node
	for (i = 0; i < 2 ;i++)
	{
		dlist_rmv(list, dlist_head(list), &data[i+7]);
		free(data[i+7]);
		dlist_debug(list);
	}

	dlist_destroy(list);

	return 0;
}
#endif