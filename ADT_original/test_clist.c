#include "include.h"
#ifdef TEST_CLIST

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
	CList list;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	list = clist_create(debug_free);

	//insert node after head
	for (i = 0;i < 5 ;i++)
	{
		clist_ins_next(list,clist_head(list),data[i]);
		clist_debug(list);
	}

	//insert node as head
	for (i = 0;i < 5 ;i++)
	{
		clist_ins_next(list,NULL,data[i+5]);
		clist_debug(list);
	}

	//remove node after head
	for (i = 0; i < 5 ;i++)
	{
		clist_rmv_next(list, clist_head(list), &data[i]);
		free(data[i]);
		clist_debug(list);
	}
	//remove head node
	for (i = 0; i < 3 ;i++)
	{
		clist_rmv_next(list, NULL, &data[i+5]);
		free(data[i+5]);
		clist_debug(list);
	}

	clist_destroy(list);

	return 0;
}


#endif