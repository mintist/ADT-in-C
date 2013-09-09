#ifndef _BITREE_H
#define _BITREE_H

#ifdef __cplusplus
extern"C"{
#endif

typedef struct BiTree_t* BiTree;
typedef struct BiTreeNode_t* BiTreeNode;
typedef void* ElmtType;

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
Return Value None.
Description Initializes the binary tree specified by tree. This operation must
be called for a binary tree before the tree can be used with any other operation.
The destroy argument provides a way to free dynamically allocated data when
bitree_destroy is called. For example, if the tree contains data dynamically 
allocated using malloc, destroy should be set to free to free the data as the binary
tree is destroyed. For structured data containing several dynamically allocated
members,destroy should be set to a user-defined function that calls free for each
dynamically allocated member as well as for the structure itself. For a binary tree
containing data that should not be freed,destroy should be set to NULL.
Complexity O(1)
*/
extern BiTree bitree_create(void (*destroy)(ElmtType data));
/* 
Return Value None.
Description Destroys the binary tree specified by tree. No other operations
are permitted after calling bitree_destroy unless bitree_create is called again. The
bitree_destroy operation removes all nodes from a binary tree and calls the function 
passed as destroy to bitree_createonce for each node as it is removed, provided destroy was not set to NULL.
Complexity O(n), where n is the number of nodes in the binary tree.
*/
extern void bitree_destroy(BiTree tree);
/*
Return Value 0 if inserting the node is successful, or 每1 otherwise.
Description Inserts a node as the left child of node in the binary tree specified
by tree.If node already has a left child,bitree_ins_left returns 每1. If node is
NULL, the new node is inserted as the root node. The tree must be empty to insert
a node as the root node; otherwise,bitree_ins_left returns 每1. When successful, the
new node contains a pointer to data, so the memory referenced by data should
remain valid as long as the node remains in the binary tree. It is the responsibility
of the caller to manage the storage associated with data.
Complexity O(1)
*/
extern int bitree_ins_left(BiTree tree, BiTreeNode node, const ElmtType data);
/*
Return Value 0 if inserting the node is successful, or 每1 otherwise.
Description This operation is similar tobitree_ins_left, except that it inserts a
node as the right child of node in the binary tree specified by tree.
Complexity O(1)
*/
extern int bitree_ins_right(BiTree tree, BiTreeNode node, const ElmtType data);
/*
Return Value None.
Description Removes the subitree rooted at the left child of node from the
binary tree specified bytree.If node is NULL, all nodes in the tree are removed.
The function passed as destroy to bitree_create is called once for each node as it is
removed, provided destroy was not set to NULL.
Complexity O(n), where n is the number of nodes in the subitree.
*/
extern void bitree_rmv_left(BiTree tree, BiTreeNode node);
/*
Return Value None.
Description This operation is similar to bitree_rem_left, except that it removes
the subitree rooted at the right child of node from the binary tree specified by
tree.
Complexity O(n), where n is the number of nodes in the subitree.
*/
extern void bitree_rmv_right(BiTree tree, BiTreeNode node);
/*
Return Value 0 if merging the trees is successful, or 每1 otherwise.
Description Merges the two binary trees specified by left and right into the
single binary tree merge. After merging is complete, merge contains data in its
root node, and left and right are the left and right subitrees of its root. Once the
trees have been merged, left and right are as if bitree_destroy had been called
on them.
Complexity O(1)
*/
extern BiTree bitree_merge( BiTree left, BiTree right, const ElmtType data);


/*
Return Value Number of nodes in the tree.
Description Inline Function that evaluates to the number of nodes in the binary tree
specified by tree.
Complexity O(1)
*/
extern int bitree_size(const BiTree tree);
/*
Return Value Node at the root of the tree.
Description Inline Function that evaluates to the node at the root of the binary tree
specified by tree.
Complexity O(1)
*/
extern BiTreeNode bitree_root(const BiTree tree);
/*
Return Value 1 if the node marks the end of a branch, or 0 otherwise.
Description Inline Function that determines whether the node specified as node marks
the end of a branch in a binary tree.
Complexity O(1)
*/
extern int bitree_is_eob(const BiTreeNode node);
/*
Return Value 1 if the node is a leaf node, or 0 otherwise.
Description Inline Function that determines whether the node specified as node is a
leaf node in a binary tree.
Complexity O(1)
*/
extern int bitree_is_leaf(const BiTreeNode node);
/*
Return Value Data stored in the node.
Description Inline Function that evaluates to the data stored in the node of a binary
tree specified by node.
Complexity O(1)
*/
extern ElmtType bitree_data(const BiTreeNode node);
/*
Return Value Left child of the specified node.
Description Inline Function that evaluates to the node of a binary tree that is the left
child of the node specified bynode.
Complexity O(1)
*/
extern BiTreeNode bitree_left(const BiTreeNode node);
/*
Return Value Right child of the specified node.
Description Inline Function that evaluates to the node of a binary tree that is the right
child of the node specified bynode.
Complexity O(1)
*/
extern BiTreeNode bitree_right(const BiTreeNode node);


void bitree_preorder_trvs(const BiTreeNode node);
void bitree_inorder_trvs(const BiTreeNode node);
void bitree_postorder_trvs(const BiTreeNode node);


extern void bitree_debug(const BiTree tree);

#ifdef __cplusplus
}
#endif

#endif