#include "bitree.h"

typedef struct BiTreeNode_t{
	ElmtType	data;

	BiTreeNode	left;
	BiTreeNode	right;
}*BiTreeNode;

typedef struct BiTree_t{
	int size;

	int (*compare)(const ElmtType key1, const ElmtType key2);
	void (*destroy)(ElmtType data);

	BiTreeNode root;
}*BiTree;

/*
The bitree_create operation initializes a binary tree so that it can be used in other
operations (see Example 9-2). Initializing a binary tree is a simple operation in
which we set the size member of the tree to 0, the destroy member to
destroy, and the root pointer to NULL.
The runtime complexity ofbitree_createis O(1) because all of the steps in initializing 
a binary tree run in a constant amount of time.
*/
BiTree bitree_create(void (*destroy)(ElmtType data))
{
	BiTree tree;
	assert(NULL != (tree= (BiTree )malloc(sizeof(struct BiTree_t))));

	tree->destroy = destroy;
	tree->size = 0;
	tree->root = NULL;

	return tree;
}

/*
The bitree_destroy operation destroys a binary tree (see Example 9-2). Primarily
this means removing all nodes from the tree. The function passed as destroy to
bitree_create is called once for each node as it is removed, provided destroy was
not set to NULL.
The runtime complexity of bitree_destroy is O(n), where n is the number of nodes
in the binary tree. This is because bitree_destroy simply calls bitree_rem_left, which
runs in O(n) time, where n is the number of nodes in the tree.
*/
void bitree_destroy(BiTree tree)
{
	bitree_rmv_left(tree,NULL);
	free(tree);
}
/*
The bitree_ins_left operation inserts a node into a binary tree as the left child of a
specified node (see Example 9-2). The call sets the new node to point to the data
passed by the caller. Linking the new node into the tree is accomplished by setting 
the left pointer of node to point to the new node. If node is NULL and the
tree is empty, we set the root member of the tree data structure to the new node.
We update the size of the tree by incrementing the size member.
The runtime complexity of bitree_ins_left is O(1) because all of the steps in inserting 
a node into a binary tree run in a constant amount of time.
*/
int bitree_ins_left(BiTree tree, BiTreeNode node, const ElmtType data)
{
	BiTreeNode new_node;
	assert(NULL != tree);
	if (NULL == (new_node = (BiTreeNode )malloc(sizeof(struct BiTreeNode_t))))
		return -1;
	new_node->data = (ElmtType )data;
	if (NULL == node && tree->size == 0)
	{
		new_node->left = NULL;
		new_node->right = NULL;
		tree->root = new_node;
	}
	else
	{
		assert(NULL != node);
		assert(NULL == node->left);
		new_node->left = NULL;
		new_node->right = NULL;
		node->left = new_node;
	}

	tree->size++;

	return 0;
}
/*
The bitree_ins_right operation inserts a node into a binary tree as the right child of
a specified node (see Example 9-2). This operation works similarly to bitree_ins_left, 
except that linking the new node into the tree is accomplished by setting the
right pointer of node to point to the new node.
The runtime complexity of bitree_ins_right is O(1) because all of the steps in
inserting a node into a binary tree run in a constant amount of time.
*/
int bitree_ins_right(BiTree tree, BiTreeNode node, const ElmtType data)
{
	BiTreeNode new_node;
	assert(NULL != tree);
	if (NULL == (new_node = (BiTreeNode )malloc(sizeof(struct BiTreeNode_t))))
		return -1;

	new_node->data = (ElmtType )data;
	if (NULL == node && tree->size == 0)
	{
		new_node->left = NULL;
		new_node->right = NULL;
		tree->root = new_node;
	}
	else
	{
		assert(NULL != node);
		assert(NULL == node->right);
		new_node->left = NULL;
		new_node->right = NULL;
		node->right = new_node;
	}

	tree->size++;

	return 0;
}
/*
The bitree_rem_left operation removes the subitree rooted at the left child of a
specified node (see Example 9-2). Nodes are removed by performing a postorder
traversal beginning at the left child of node.If node is NULL, we begin the 
traversal at the root node. The function passed as destroy to bitree_create is called
once for each node as it is removed, provided destroy was not set to NULL. As
each node is removed, we update the size member of the tree data structure as
well.
The runtime complexity of bitree_rem_left is O(n), where n is the number of
nodes in the subitree rooted at the left child of node. This is because bitree_rem_left 
performs a postorder traversal to visit each of the nodes in the subitree while
all other parts of the operation run in a constant amount of time.
*/
void bitree_rmv_left(BiTree tree, BiTreeNode node)
{
	BiTreeNode *old_node;
	assert(NULL != tree && tree->size > 0);
	old_node = (node == NULL ? &tree->root : &node->left);

	if ((*old_node) != NULL)
	{
		bitree_rmv_left(tree, (*old_node));
		bitree_rmv_right(tree, (*old_node));

		tree->destroy((*old_node)->data);

		free((*old_node));
		*old_node = NULL;
		if(NULL != node)
			node->left = NULL;
		tree->size--;
	}
}
/*
The bitree_rem_right operation removes the subitree rooted at the right child of a
specified node (see Example 9-2). This operation works much like bitree_rem_left,
except that nodes are removed by performing a postorder traversal beginning at
the right child of node.
The runtime complexity of bitree_rem_rightis O(n), where n is the number of
nodes in the subitree rooted at the right child of node. This is because bitree_rem_right 
performs a postorder traversal to visit each of the nodes in the subitree while
all other parts of the operation run in a constant amount of time.
*/
void bitree_rmv_right(BiTree tree, BiTreeNode node)
{
	BiTreeNode *old_node;
	assert(NULL != tree && tree->size > 0);

	old_node = (node == NULL ? &tree->root : &node->right);

	if ((*old_node) != NULL)
	{
		bitree_rmv_left(tree, (*old_node));
		bitree_rmv_right(tree, (*old_node));

		tree->destroy((*old_node)->data);

		free((*old_node));
		if(NULL != node)
			node->right = NULL;
		tree->size--;
	}
}
/*
The bitree_merge operation merges two binary trees into a single binary tree (see
Example 9-2). First, we initialize emerge by calling bitree_create. Next, we insert data
into the merged tree at its root. The merged tree's left and right children are then
set to be the root nodes of left and right, and the size of the tree is adjusted to
reflect the sizes of the subitrees. Last, we detach the nodes now in the merged tree
from the original trees and set the size of each tree to 0.
The runtime complexity of bitree_merge is O(1) because all of the steps in merging two 
binary trees run in a constant amount of time.
*/
BiTree bitree_merge( BiTree left, BiTree right, const ElmtType data)
{
	BiTree merge;
	assert(NULL != left && NULL != right);

	merge = bitree_create(left->destroy);

	if(bitree_ins_left(merge, NULL, (ElmtType )data)  != 0)
		return NULL;

	merge->root->left = left->root;
	merge->root->right = right->root;
	merge->size = merge->size + left->size +right->size;

	free(left);
	free(right);

	return merge;
}
__inline int bitree_size(const BiTree tree)
{
	return tree->size;
}
__inline BiTreeNode bitree_root(const BiTree tree)
{
	return tree->root;
}
__inline int bitree_is_eob(const BiTreeNode node)
{
	return (node == NULL);
}
__inline int bitree_is_leaf(const BiTreeNode node)
{
	return (node->left == NULL && node->right == NULL ? 1 : 0);
}
__inline ElmtType bitree_data(const BiTreeNode node)
{
	return node->data;
}
__inline BiTreeNode bitree_left(const BiTreeNode node)
{
	return node->left;
}
__inline BiTreeNode bitree_right(const BiTreeNode node)
{
	return node->right;
}

void bitree_preorder_trvs(const BiTreeNode node)
{
	if(node == NULL)
		return;
	printf("%d ",*(int*)bitree_data(node));
	bitree_preorder_trvs(bitree_left(node));
	bitree_preorder_trvs(bitree_right(node));
}
void bitree_inorder_trvs(const BiTreeNode node)
{
	if(node == NULL)
		return;
	bitree_inorder_trvs(bitree_left(node));
	printf("%d ",*(int*)bitree_data(node));
	bitree_inorder_trvs(bitree_right(node));
}
void bitree_postorder_trvs(const BiTreeNode node)
{
	if(node == NULL)
		return;
	bitree_postorder_trvs(bitree_left(node));
	bitree_postorder_trvs(bitree_right(node));
	printf("%d ",*(int*)bitree_data(node));
}

void bitree_debug(const BiTree tree)
{
	if (tree->size > 0)
	{
		printf("tree->size = %d \n", tree->size);
		printf("*(tree->root->data) = %d\n", *((int *)(tree->root->data)));
		if (tree->root->left != NULL)
		{
			printf("*(tree->root->left->data) = %d\n", *((int *)(tree->root->left->data)));
		}

		if (tree->root->right != NULL)
		{
			printf("*(tree->root->right->data) = %d\n", *((int *)(tree->root->right->data)));
		}
	}
}