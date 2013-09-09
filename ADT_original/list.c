#include "list.h"

typedef struct ListNode_t{
	ElmtType		data;
	ListNode	next;
}*ListNode;

typedef struct List_t{
	int			size;

	int (*match)(const ElmtType key1, const ElmtType key2);
	void (*destroy)(ElmtType data);

	ListNode	head;
	ListNode	tail;
}*List;


List list_create(void(*destroy)(ElmtType data))
{
	List list;
	if((list=(List )malloc(sizeof(struct List_t))) == NULL)
		printf("memory is not enough when malloc for list !\n");

	list->size = 0;
	list->destroy = destroy;

	list->head = NULL;
	list->tail = NULL;

	return list;
}
void list_empty(List list)
{
	ElmtType data;
	if(list == NULL)  //do nothing if list is NULL 
		return;

	while(list->size > 0)
	{
		if (list_rmv_next(list, NULL, &data)==0)
		{
			list->destroy(data);
		}
	}
}
void list_destroy(List list)
{
	list_empty(list);
	free(list);
}



int list_ins_next(List list, \
				  ListNode node, const ElmtType data)
{	
	ListNode new_node;
	if(list == NULL) //can't insert if list is NULL
		return -1;
	if((new_node=(ListNode )malloc(sizeof(struct ListNode_t))) == NULL)
		printf("memory is not enough when malloc for node !\n");

	new_node->data = (void *)data;
	if (node == NULL)			//insert as head
	{
		new_node->next = list->head;
		list->head = new_node;
		if (list->size==0)
			list->tail = new_node;
	}
	else						//insert after head
	{
		new_node->next = node->next;
		node->next = new_node;
		if (node == list_tail(list))
		{
			list->tail = new_node;
		}
	}

	list->size++;
	return 0;
}
int list_rmv_next(List list, \
				  ListNode node, ElmtType* data)
{
	ListNode old_node;
	if(list == NULL)			//can't remove if list is NULL
		return -1;
	if( list->size == 0)		//if list is empty
	{
		printf("list is empty \n");
		return -1;
	}
	if (node == NULL)			//remove head
	{
		old_node = list->head;
		*data = old_node->data;
		if (list->size == 1)
		{
			list->head = NULL;
			list->tail = NULL;
		}
		else
		{
			list->head = list->head->next;
		}
	} 
	else
	{
		if (list_is_tail(node))		//can't remove the node after tail
		{
			return -1;
		}
		else
		{
			old_node = node->next;
			*data = old_node->data;
			node->next = old_node->next;
			if (old_node->next==NULL)		//if remove tail
			{
				list->tail = node;
			}
		}
	}
	
	free(old_node);
	list->size--;
	return 0;
}
__inline int list_size(const List list)
{
	return list->size;
}
__inline ListNode list_head(const List list)
{
	return list->head;
}
__inline ListNode list_tail(const List list)
{
	return list->tail;
}
__inline int list_is_head(const List list, \
				 const ListNode node)
{
	return (list->head == node ? 1 : 0);
}
__inline int list_is_tail(const ListNode node)
{
	return (node->next == NULL ? 1 : 0);
}
__inline ListNode list_next(const ListNode node)
{
	return node->next;
}
__inline ElmtType list_data(const ListNode node)
{
	return node->data;
}

__inline void list_set_match(List list, \
					int (*match)(const ElmtType key1, const ElmtType key2))
{
	list->match = match;
}

__inline int list_match(const List list, \
			   const ElmtType key1, const ElmtType key2)
{
	return list->match(key1, key2);
}

__inline int list_space(void)
{
	return sizeof(struct List_t);
}

void list_debug(const List list)
{
	ListNode node;
	printf("head:");
	if (list->size > 0)
	{
		for (node = list_head(list);node != NULL ; node = list_next(node))
		{
			printf("%d->",*(int*)list_data(node));
		}
	}
	printf("NULL \n");
}