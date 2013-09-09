#include "include.h"

#ifdef TEST_SEARCH_SORT

#include <time.h>
#include <stdlib.h>

int (*sort)(void* data, int size, int esize, \
			int (*compare)(const void* key1, const void* key2)) = heap_sort;
int (*search)(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2)) = interpolation_search;

static int compare(const void* key1, const void* key2)
{
	if (*(int*)key1 > *(int*)key2)
		return 1;
	else
	{
		if (*(int*)key1 == *(int*)key2)
		{
			return 0;
		} 
		else
		{
			return -1;
		}
	}
}

#define N	100
int main(int argc, char const *argv[])
{
	int i; 
	int iPtr[N] = {0};
	int tert;

	//init
	srand((unsigned int)time(NULL));
	for (i=0;i<N;i++)
	{
		iPtr[i] = rand();
		printf("%d ",iPtr[i]);
	}
	tert = iPtr[10];
	//shaker sorting
	sort(iPtr,N,sizeof(int),compare);

	//after sorting
	printf("\n");
	for (i=0;i<N;i++)
	{
		printf("%d ",iPtr[i]);
	}
	//after search
	printf("\n");
	printf("target's index = %d", linear_search(iPtr,&tert,N,sizeof(int),compare));

	printf("\n");
	printf("target's index = %d", binary_search(iPtr,&tert,N,sizeof(int),compare));

	printf("\n");
	printf("target's index = %d", fibonacci_search(iPtr,&tert,N,sizeof(int),compare));

	printf("\n");
	printf("target's index = %d", interpolation_search(iPtr,&tert,N,sizeof(int),compare));
	
	getchar();
	return 0;
}

#endif
