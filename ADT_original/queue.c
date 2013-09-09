#include "queue.h"

Queue queue_create(void (*destroy)(void* data))
{
	return list_create(destroy);
}
void queue_destroy(Queue queue)
{
	list_destroy(queue);
}

int queue_enqueue(Queue queue, \
				  void* data)
{
	return list_ins_next((List )queue, list_tail((List )queue), data);
}
int queue_dequeue(Queue queue, \
				  void** data)
{
	return list_rmv_next((List )queue,NULL,data);
}
void* queue_peek(const Queue queue)
{
	if(queue_size(queue) == 0 )
		return NULL;
	return list_data(list_head((List )queue));
}
__inline int queue_size(const Queue queue)
{
	return list_size((List )queue);
}

void queue_debug(const Queue queue)
{
	ListNode node;
	printf("Head:");
	if (queue_size(queue)> 0)
	{
		for (node = list_head(queue);node != NULL ; node = list_next(node))
		{
			printf("%d->",*(int*)list_data(node));
		}
	}
	printf("Rear \n");
}