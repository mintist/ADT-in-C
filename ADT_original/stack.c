#include "stack.h"

Stack stack_create(void (*destroy)(void* ))
{
	return list_create(destroy);
}
void stack_destroy(Stack stack)
{
	list_destroy(stack);
}
int stack_push(Stack stack, \
			   void* data)
{
	return list_ins_next((List )stack, NULL, data);
}
int stack_pop(Stack stack, \
			  void** data)
{
	return list_rmv_next((List )stack, NULL,data);
}

void* stack_peek(const Stack stack)
{
	if(stack_size(stack) == 0)
		return NULL;
	return (list_data(list_head((List )stack)));
}

__inline int stack_size(const Stack stack)
{
	return list_size((List )stack);
}

void stack_debug(const Stack stack)
{
	ListNode node;
	printf("Top:");
	if (stack_size(stack)> 0)
	{
		for (node = list_head(stack);node != NULL ; node = list_next(node))
		{
			printf("%d->",*(int*)list_data(node));
		}
	}
	printf("Bottom \n");
}