#include "clist.h"

/* General-purpose swap macro */
#define SWAP1(a, b) do {\
	char c[sizeof(a)]; \
	memcpy((void *)&c, (void *)&a, sizeof(c)); \
	memcpy((void *)&a, (void *)&b, sizeof(a)); \
	memcpy((void *)&b, (void *)&c, sizeof(b)); \
} while (0)

#define SWAP2(a, b, n) do {\
	char c[n]; \
	memcpy((void *)&c, (void *)&a, n); \
	memcpy((void *)&a, (void *)&b, n); \
	memcpy((void *)&b, (void *)&c, n); \
} while (0)

typedef struct CListNode_t{
	void*		data;
	CListNode	next;
}*CListNode;

typedef struct CList_t{
	int size;

	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);

	CListNode head;
}*CList;

CList clist_create(void (*destroy)(void* data))
{
	CList list;
	if((list=(CList )malloc(sizeof(struct CList_t))) == NULL)
		printf("memory is not enough when malloc for clist !\n");

	list->size = 0;
	list->destroy = destroy;

	list->head = NULL;

	return list;
}
void clist_destroy(CList list)
{
	void* data;
	if(list == NULL)
		return;

	while(list->size > 0)
	{
		if (clist_rmv_next(list, NULL, &data) == 0)
		{
			list->destroy(data);
		}
	}
	free(list);
}
int clist_ins_next(CList list, \
				   CListNode node, const void* data)
{
	CListNode new_node;
	if(list == NULL)
		return -1;
	if((new_node=(CListNode )malloc(sizeof(struct CListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");;
	new_node->data = (void* )data;
	
	if (list->size == 0)		// list si empty
	{
		new_node->next = new_node;
		list->head = new_node;
	}
	else						//or
	{
		/* if the list has more than 1(>=) nodes */
		if(node == NULL)
		{
			new_node->next = list->head->next;
			list->head->next = new_node;
			SWAP1(list->head->data,new_node->data);
		}
		else
		{
			new_node->next = node->next;
			node->next = new_node;
		}
	}

	list->size++;
	return 0;
}
int clist_rmv_next(CList list, \
				   CListNode node, void** data)
{
	CListNode old_node;
	if(list == NULL)			//can't remove if list is NULL
		return -1;
	if( list->size == 0)		//if list is empty
	{
		printf("clist is empty \n");
		return -1;
	}

	if (node == NULL)		//remove head node
	{
		*data = list->head->data;
		if (list->size == 1)
		{
			old_node = list->head;
			list->head = NULL;
		}
		else
		{
			old_node = list->head->next;
			SWAP1(list->head->data,old_node->data);
			list->head->next = old_node->next;
		}
	}
	else
	{
		*data = node->next->data;
		if (node->next == node)		//the last one node
		{
			old_node = node->next;
			list->head = NULL;
		}
		else								//or 
		{
			old_node = node->next;
			node->next = old_node->next;
			if (clist_is_head(list,old_node)) //if head of list was changed
			{
				list->head = old_node->next;
			}
		}
	}
	
	free(old_node);
	list->size--;
	return 0;
}

__inline int clist_size(const CList list)
{
	return list->size;
}
CListNode clist_head(const CList list)
{
	return list->head;
}
__inline int clist_is_head(const CList list,\
				  const CListNode node)
{
	return (list->head == node ? 1 : 0);
}

__inline void* clist_data(const CListNode node)
{
	return node->data;
}
__inline CListNode clist_next(const CListNode node)
{
	return node->next;
}

void clist_debug(const CList list)
{
	CListNode node;
	int n = list->size;
	printf("head:");
	if (list->size > 0)
	{
		for (node = clist_head(list);n-- > 0 ; node = clist_next(node))
		{
			printf("%d->",*(int*)clist_data(node));
		}
	}
	printf("NULL \n");
}