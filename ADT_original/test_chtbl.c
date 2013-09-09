#include "include.h"

#ifdef TEST_CHTBL


#include "include.h"

static int h(const void *data)
{
	return *(int *)data;
}

static void debug_free(void* data)
{
	printf("%d is freeing \n",*(int*)data);
	free(data);
}
static int match(const void *key1, const void *key2)
{
	if(*(int *)key1 == *(int *)key2)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

#define N   55
#define BUCKETS     10
int main(int argc, char const *argv[])
{
	int i;
	int *iPtr[N] = {NULL};
	CHTbl table;
	//init
	table = chtbl_create(BUCKETS, h, match, debug_free);

	//insert
	for(i = 0; i < N; i++)
	{
		iPtr[i] = (int *)malloc(sizeof(int));
		*iPtr[i] = i;
		chtbl_insert(table, iPtr[i]);
	}

	chtbl_debug(table);

	//remove
	for(i = 0; i < N / 2; i++)
	{
		chtbl_remove(table, &iPtr[i]);
		free(iPtr[i]);
	}

	chtbl_debug(table);
	//destroy
	chtbl_destroy(table);
	getchar();
	return 0;
}
#endif