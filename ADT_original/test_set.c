#include "include.h"

#ifdef TEST_SET

#include <stdlib.h>
#include <stdio.h>

static void debug_free(void* data)
{
	printf("%d is freeing \n",*(int*)data);
	free(data);
}
int match(const ElmtType key1, const ElmtType key2)
{
	if (*(int*)key1 == *(int*)key2)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}

int main(void)
{
	int i;
	int* data[10],* data1[10],* data2[10];
	Set set,set1,set2,setu,seti,setd;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}
	for (i = 0; i< 10; i++)
	{
		data1[i] = (int*)malloc(sizeof(int));
		*data1[i] = i;
	}
	for (i = 0; i< 10; i++)
	{
		data2[i] = (int*)malloc(sizeof(int));
		*data2[i] = i+6;
	}
	
	//1. set insert test
	set = set_create(match,debug_free);
	for (i=0;i<10;i++)
	{
		set_insert(set,data[i]);
		set_debug(set);
	}
	//set1 and set2
	set1 = set_create(match,debug_free);
	for (i=0;i<10;i++)
	{
		set_insert(set1,data1[i]);
		set_debug(set1);
	}
	set2 = set_create(match,debug_free);
	for (i=0;i<10;i++)
	{
		set_insert(set2,data2[i]);
		set_debug(set2);
	}
	//2. set union test
	setu = set_create(match,debug_free);
	set_union(setu,set1,set2);
	set_debug(setu);
	//3. set intersection test
	seti = set_create(match,debug_free);
	set_intersection(seti,set1,set2);
	set_debug(seti);
	//4. set difference test
	setd = set_create(match,debug_free);
	set_difference(setd,set1,set2);
	set_debug(setd);


	set_destroy(set);
	set_destroy(set1);
	set_destroy(set2);
	free(setu);
	free(seti);
	free(setd);

	return 0;
}

#endif