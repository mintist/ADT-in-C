#include "include.h"
#ifdef TEST_CDLIST


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
	CDList list;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	list = cdlist_create(debug_free);

	//insert node
	for (i = 0;i < 5 ;i++)
	{
		cdlist_ins_prev(list,cdlist_head(list),data[i]);
		cdlist_debug(list);
	}

	//insert node
	for (i = 0;i < 5 ;i++)
	{
		cdlist_ins_next(list,cdlist_head(list),data[i+5]);
		cdlist_debug(list);
	}

	//remove head node
	for (i = 0; i < 8 ;i++)
	{
		cdlist_rmv(list, cdlist_head(list), &data[i]);
		free(data[i]);
		cdlist_debug(list);
	}

	cdlist_destroy(list);

	return 0;
}
#endif