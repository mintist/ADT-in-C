#include "cdlist.h"

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

typedef struct CDListNode_t{
	void*		data;

	CDListNode next;
	CDListNode prev;
}*CDListNode;

typedef struct CDList_t{
	int size;

	void (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);

	CDListNode head;
}*CDList;

CDList cdlist_create(void (*destroy)(void* data))
{
	CDList list;
	if((list=((CDList )malloc(sizeof(struct CDList_t)))) == NULL)
		printf("memory is not enough when malloc for cdlist !\n");

	list->size = 0;
	list->head = NULL;
	list->destroy = destroy;

	return list;
}
void cdlist_destroy(CDList list)
{
	void* data;
	if( list == NULL)
		return;

	while(list->size > 0)
	{
		if (cdlist_rmv(list, list->head, &data)==0)
		{
			list->destroy(data);
		}
	}
	free(list);
}

int cdlist_ins_prev(CDList list, \
					CDListNode node,const void* data)
{
	CDListNode new_node;
	if(list == NULL)
		return -1;
	if((new_node=(CDListNode )malloc(sizeof(struct CDListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");
	new_node->data = (void* )data;

	if (list->size == 0)				//list is empty
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		list->head = new_node;
	} 
	else								//or
	{
		if(node == NULL)				//insert as head
		{
			cdlist_ins_next(list,list->head,data);
			SWAP1(list->head->data,list->head->next->data);
			return 0;
		}
		else							//or
		{
			new_node->next = node;
			new_node->prev = node->prev;
			node->prev->next = new_node;
			node->prev = new_node;

			if (cdlist_is_head(list,node))
			{
				list->head = list->head->prev;
			}
		}
	}

	list->size++;
	return 0;
}
int cdlist_ins_next(CDList list, \
					CDListNode node, const void* data)
{
	CDListNode new_node;
	if(list == NULL)
		return -1;
	if((new_node=(CDListNode )malloc(sizeof(struct CDListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");
	new_node->data = (void* )data;

	if (list->size == 0)
	{
		new_node->next = new_node;
		new_node->prev = new_node;
		list->head = new_node;
	}
	else
	{
		if (node == NULL)					//insert as head
		{
			return cdlist_ins_prev(list,NULL,data);
		} 
		else								//or
		{
			new_node->next = node->next;
			new_node->prev = node;
			node->next->prev = new_node;
			node->next = new_node;
		}
	}
	
	list->size++;
	return 0;
}
int cdlist_rmv(CDList list, \
			   CDListNode node, void** data)
{
	if(list == NULL)
		return -1;
	if (node == NULL)
	{
		*data = list->head->data;
		return cdlist_rmv(list,list->head,data);
	} 
	else
	{
		*data = node->data;
	}
	switch(list->size)
	{
		case 0:
			printf(" cdlist is empty \n");
			return -1;
			break;
		case 1:
			list->head = NULL;
			break;
		default:
			node->prev->next = node->next;
			node->next->prev = node->prev;
			if (cdlist_is_head(list,node))		//if head is removed
			{
				list->head = list->head->next;
			}
			break;
	}

	free(node);
	list->size--;

	return 0;
}

__inline int cdlist_size(const CDList list)
{
	return list->size;
}
__inline CDListNode cdlist_head(const CDList list)
{
	return list->head;
}
__inline int cdlist_is_head(const CDList list,\
				   const CDListNode node)
{
	return ((list)->head == node ? 1 : 0);
}
__inline int cdlist_is_mbr(const CDList list, \
				  const CDListNode node)
{
	return 0;
}
__inline void* cdlist_data(const CDListNode node)
{
	return node->data;
}
__inline CDListNode cdlist_next(const CDListNode node)
{
	return node->next;
}
__inline CDListNode cdlist_prev(const CDListNode node)
{
	return node->prev;
}

void cdlist_debug(const CDList list)
{
	CDListNode node;
	int n=list->size;
	printf("head:");
	if (list->size > 0)
	{
		for (node = cdlist_head(list); n-- ; node = cdlist_next(node))
		{
			printf("%d->",*(int*)cdlist_data(node));
		}
	}
	printf("NULL \n");
}