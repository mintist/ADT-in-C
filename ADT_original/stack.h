#ifndef _STACK_H
#define _STACK_H

/** ADT Stack by List
 * 
 * 
 * Operation
 * 
 * stack_create();
 * stack_destroy();
 * stack_push();
 * stack_pop();
 * stack_peak();
 * stack_size();
 * 
 * 
 * END ADT
 */

#ifdef __cplusplus
extern "C" {
#endif

/* include */
#include "list.h"

typedef List Stack;

extern Stack stack_create(void (*destroy)(void* ));
extern void stack_destroy(Stack stack);
extern void stack_empty(Stack stack);
extern int stack_push(Stack stack, \
			   void* data);
extern int stack_pop(Stack stack, \
			  void** data);

extern void* stack_peek(const Stack stack);

extern int stack_size(const Stack stack);

extern void stack_debug(const Stack stack);


#ifdef __cplusplus
}
#endif

#endif