#include "dlist.h"

typedef struct DListNode_t{
	void*			data;

	DListNode		next;
	DListNode		prev;
}*DListNode;

typedef struct DList_t{
	int size;

	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);

	DListNode head;
	DListNode tail;
}*DList;

DList dlist_create(void (*destroy)(void* data))
{
	DList list;
	if((list=((DList )malloc(sizeof(struct DList_t)))) == NULL)
		printf("memory is not enough when malloc for dlist !\n");
	
	list->size = 0;
	
	list->head = NULL;
	list->tail = NULL;

	list->destroy = destroy;

	return list;
}
void dlist_destroy(DList list)
{
	void* data;
	if(list == NULL)
		return;

	while(list->size > 0)
	{
		/* remove the head of the list */
		if (dlist_rmv(list, dlist_head(list), &data)==0)
		{
			list->destroy(data);
		}
	}
	free(list);
}

int dlist_ins_prev(DList list, \
				   DListNode node, const void* data)
{
	DListNode new_node;
	if(list == NULL)
		return -1;
	if((new_node=(DListNode )malloc(sizeof(struct DListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");
	
	new_node->data = (void* )data;

	if (list->size == 0)		//empty list
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		list->head = new_node;
		list->tail = new_node;
	} 
	else
	{
		if(node == NULL)		//insert as head
		{
			return dlist_ins_prev(list,list->head,data);
		}
		else
		{
			new_node->next = node;
			new_node->prev = node->prev;
			if (dlist_is_head(list,node))	//insert as head
			{
				list->head->prev = new_node;
				list->head = new_node;
			} 
			else								//or other
			{
				node->prev->next = new_node;
				node->prev = new_node;
			}
		}		
	}
	list->size++;
	return 0;
}

int dlist_ins_next(DList list, \
				   DListNode node,const void* data)
{
	DListNode new_node;
	if(list == NULL)
		return -1;
	if((new_node=(DListNode )malloc(sizeof(struct DListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");
	
	new_node->data = (void* )data;

	if (list->size == 0)			//if list is empty
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		if (node == NULL)	//insert as tail
		{
			return dlist_ins_next(list,list->tail,data);
		} 
		else
		{
			new_node->prev = node;
			new_node->next = node->next;
			if (dlist_is_tail(node))		//insert as tail
			{
				list->tail->next = new_node;
				list->tail = new_node;
			}
			else							//or other
			{
				node->next->prev = new_node;
				node->next = new_node;
			}	
		}
	}

	list->size++;
	return 0;
}

int dlist_rmv(DList list, \
			  DListNode node, void** data)
{
	if(list == NULL)
		return -1;
	if (node == NULL)
	{
		*data = list->head->data;
		return dlist_rmv(list,list->head,data);
	}
	else
		*data = node->data;

	switch (list->size)
	{
		case 0:
			printf("dlist is empty \n");
			return -1;
			break;
		case 1:
			list->head = NULL;
			list->tail = NULL;
			break;
		default:
			if (dlist_is_head(list,node))
			{
				list->head = list->head->next;
				list->head->prev = NULL;	//or other node
			} 
			else
			{
				if (dlist_is_tail(node))		//the node to be removed is tail
				{
					list->tail = list->tail->prev;
					list->tail->next = NULL;
				}
				else
				{
					node->prev->next = node->next;
					node->next->prev = node->prev; //or other normal node
				}
			}
			break;
	}

	free(node);
	list->size--;
	return 0;
}

__inline int dlist_size(const DList list)
{
	return list->size;
}
__inline DListNode dlist_head(const DList list)
{
	return list->head;
}
__inline DListNode dlist_tail(const DList list)
{
	return list->tail;
}
__inline int dlist_is_head(const DList list, \
				  const DListNode node)
{
	return (node == list->head ? 1 : 0 );
}
__inline int dlist_is_tail(const DListNode node)
{
	return (node->next == NULL ? 1 :0 );
}

__inline void* dlist_data(const DListNode node)
{
	return node->data;
}
__inline DListNode dlist_next(const DListNode node)
{
	return node->next;
}
__inline DListNode dlist_prev(const DListNode node)
{
	return node->prev;
}

void dlist_debug(const DList list)
{
	DListNode node;
	printf("head:");
	if (list->size > 0)
	{
		for (node = dlist_head(list);node != NULL ; node = dlist_next(node))
		{
			printf("%d->",*(int*)dlist_data(node));
		}
	}
	printf("NULL \n");
}