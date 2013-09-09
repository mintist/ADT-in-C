#include "bistree.h"

typedef struct BisTreeNode_t{
	ElmtType data;

	BisTreeNode left;
	BisTreeNode right;
}*BisTreeNode;

typedef struct BisTree_t{
	BisTreeNode root;
	int			size;
	void (*destroy)(ElmtType data);
	void (*compare)(const ElmtType key1, const ElmtType key2);
}*BisTree;

BisTree bistree_create(void (*compare)(const ElmtType key1, const ElmtType key2),\
					   void (*destroy)(ElmtType data))
{

}

void	bistree_destroy(BisTree tree)
{

}
int		bistree_insert(BisTree tree, const ElmtType data)
{

}
int		bistree_remove(BisTree tree, const ElmtType data)
{

}
int		bistree_looup(const BisTree tree, ElmtType* data)
{

}
__inline int		bistree_size(const BisTree tree)
{
	return (tree->size);
}
