#include "include.h"

#ifdef TEST_BITREE


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
	BiTree tree;

	// 10 test data
	for (i = 0; i< 10; i++)
	{
		data[i] = (int*)malloc(sizeof(int));
		*data[i] = i;
	}

	tree = bitree_create(debug_free);

	//add data to tree
	bitree_ins_left(tree,NULL,data[0]);
	bitree_debug(tree);
	bitree_ins_left(tree,bitree_root(tree),data[1]);
	bitree_debug(tree);
	bitree_ins_right(tree,bitree_root(tree),data[2]);
	bitree_debug(tree);

	bitree_preorder_trvs(bitree_root(tree));
	bitree_inorder_trvs(bitree_root(tree));
	bitree_postorder_trvs(bitree_root(tree));

	//remove data from tree
	bitree_rmv_left(tree,bitree_root(tree));
	bitree_debug(tree);
	
	bitree_destroy(tree);

	return 0;
}
#endif