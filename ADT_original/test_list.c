#include "include.h"

#ifdef TEST_LIST

#include <stdlib.h>
#include <stdio.h>


int main(void)
{
	int i;
	int* data[10];
	List list;
	
	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	list = list_create(free);
	
	//insert after tail
	for (i = 0;i < 5 ;i++)
	{
		list_ins_next(list,NULL,data[i]);
		list_debug(list);
	}
	//insert before head
	for (i = 0;i < 5 ;i++)
	{
		list_ins_next(list,NULL,data[i+5]);
		list_debug(list);
	}
	
	//remove head
	for (i = 0; i < 10 ;i++)
	{
		list_rmv_next(list, NULL, &data[i]);
		free(data[i]);
		list_debug(list);
	}

	list_destroy(list);

	return 0;
}

#endif
