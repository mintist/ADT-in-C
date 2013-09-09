#ifndef _QUEUE_H
#define _QUEUE_H

/** ADT Queue by List
 * 
 * 
 * Operation
 * 
 * queue_create();
 * queue_destroy();
 * queue_enqueue();
 * queue_dequeue();
 * queue_peak();
 * queue_size();
 * 
 * 
 * END ADT
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

typedef List Queue;

extern Queue	queue_create(void (*destroy)(void* data));
extern void		queue_destroy(Queue queue);

extern int		queue_enqueue(Queue queue, \
				  void* data);
extern int		queue_dequeue(Queue queue, \
					void** data);
extern void*	queue_peek(const Queue queue);
extern int		queue_size(const Queue queue);

extern void		queue_debug(const Queue queue);

#ifdef __cplusplus
}
#endif

#endif