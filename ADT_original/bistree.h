#ifndef _BISTREE_H
#define _BISTREE_H

#ifdef __cplusplus
extern"C"{
#endif

#include "comm.h"

typedef struct BisTree_t* BisTree;
typedef struct BisTreeNode_t* BisTreeNode;

typedef enum BISTREE_STATE{
	SUCCESS = 0,
	EXIST	= 1,
	FAILED	= -1
}bistree_state;

/*
Return Value None.
Description Initializes the binary search tree specified by tree. This operation 
must be called for a binary search tree before the tree can be used with any
other operation. The function pointercomparespecifies a user-defined function
to compare elements. This function should return 1 if key1>key2,0ifkey1=
key2, and 每1 if key1<key2. The destroyargument provides a way to free
dynamically allocated data whenbistree_destroyis called. It works in a manner
similar to that described forbitree_destroy. For a binary search tree containing data
that should not be freed, destroyshould be set to NULL.
Complexity O(1)
*/

BisTree bistree_create(void (*compare)(const ElmtType key1, const ElmtType key2),\
						void (*destroy)(ElmtType data));
/*
Return Value None.
Description Destroys the binary search tree specified bytree. No other operations
are permitted after callingbistree_destroyunlessbistree_initis called again.
Thebistree_destroyoperation removes all nodes from a binary search tree and
calls the function passed as destroyto bistree_initonce for each node as it is
removed, provideddestroywas not set to NULL.
Complexity O(n), wherenis the number of nodes in the binary search tree.
*/
void	bistree_destroy(BisTree tree);
/*
Return Value 0 if inserting the node is successful, 1 if the node is already in the
tree, or 每1 otherwise.
Description Inserts a node into the binary search tree specified by tree. The
new node contains a pointer todata, so the memory referenced by datashould
remain valid as long as the node remains in the binary search tree. It is the
responsibility of the caller to manage the storage associated withdata.
Complexity O(lg n), where nis the number of nodes in the binary search
tree.
*/
int		bistree_insert(BisTree tree, const ElmtType data);
/*
Return Value 0 if removing the node is successful, or 每1 otherwise.
Description Removes the node matchingdatafrom the binary search tree
specified by tree. In actuality, this operation only performs a lazy removal, in
which the node is simply marked as hidden. Thus, no pointer is returned to the
data matchingdata. The data in the tree must remain valid even after it has been
removed. Consequently, the size of the binary search tree, as returned by bistree_
size, does not decrease after removing a node. This approach is explained further
in the implementation and analysis section.
Complexity O(lg n), where nis the number of nodes in the binary search
tree.
*/
int		bistree_remove(BisTree tree, const ElmtType data);
/*
Return Value 0 if the data is found in the binary search tree, or 每1 otherwise.
Description Determines whether a node matchesdatain the binary search
tree specified as tree. If a match is found, datapoints to the matching data in the
binary search tree upon return.
Complexity O(lg n), where nis the number of nodes in the binary search
tree.
*/
int		bistree_looup(const BisTree tree, ElmtType* data);
/*
Return Value Number of nodes in the tree.
Description Inline Function that evaluates to the number of nodes in the binary search
tree specified by tree.
Complexity O(1)
*/
int		bistree_size(const BisTree tree);













#ifdef __cplusplus
}
#endif

#endif