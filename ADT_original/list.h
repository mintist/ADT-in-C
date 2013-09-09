/* ============================================================================================
Abstract Data Type(ADT) is placed under the MIT license
Copyright (c) 2013 Ted Lin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
================================================================================================*/

/* Define to prevent recursive inclusion*/
#ifndef _LIST_H
#define _LIST_H

#ifdef __cplusplus
extern"C"{
#endif

/** ADT Single Linked List
 * 
 * 
 * Operation
 * 
 * list_create();
 * list_destroy();
 * list_ins_next();
 * list_rmv_next();
 * list_size();
 * list_head();
 * list_tail();
 * list_is_head();
 * list_is_tail()
 * list_data();
 * list_next();
 * 
 * 
 * END ADT
 */

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct List_t* List;			//list
typedef struct ListNode_t* ListNode;	//node of list
typedef void*	ElmtType;				//element type


/** Initializes the linked list specified by list. This operation must
 * be called for a linked list before the list can be used with any other operation.
 * The destroy argument provides a way to free dynamically allocated data when
 * destroy is called. For example, if the list contains data dynamically allocated
 * using malloc, destroy should be set to free to free the data as the linked list is
 * destroyed. For structured data containing several dynamically allocated members,
 * destroy should be set to a user-defined function that calls free for each dynamically 
 * allocated member as well as for the structure itself.
 * @param list list user definition
 * @param destroy user defined free function
 * @return None
 * @complexity O(1)
 */
extern List list_create(void(*destroy)(ElmtType data));
/** Destroys the linked list specified by list. No other operations
 * are permitted after calling list_destroy unless list_create is called again. The 
 * destroy operation removes all nodes from a linked list and calls the function
 * passed as destroy to list_create once for each node as it is removed, provided
 * destroy was not set to NULL.
 * @param list list user definition
 * @return None
 * @complexity O(n), where n is the number of nodes in the linked list.
 */

extern void list_empty(List list);

extern void list_destroy(List list);
/** Inserts an node just after node in the linked list specified
 * by list.If node is NULL, the new node is inserted at the head of the list.
 * The new node contains a pointer to data, so the memory referenced by data
 * should remain valid as long as the node remains in the list. It is the 
 * responsibility of the caller to manage the storage associated with data.
 * @param list list user definition
 * @param node insert a new node after the node you assign, 
 * or NULL if you want insert the new node as the head of list
 * @param data user-defined data
 * @return 0:insert node successfully or -1:failure
 * @complexity O(1)
 */

extern int list_ins_next(List list, \
				  ListNode node, const ElmtType data);
/** Removes the node just after node from the linked list specified by list.
 * If node is NULL, the node at the head of the list is removed.
 * Upon return,data points to the data stored in the node that was removed. It is
 * the responsibility of the caller to manage the storage associated with the data.
 * @param list list user definition
 * @param node remove a old node after the node you assign, 
 * or NULL if you want remove the head of list
 * @param data user-defined data pointer's pointer to hold the
 * node's data pointer
 * @return 0:remove node successfully or -1:failure
 * @complexity O(1)
 */
extern int list_rmv_next(List list, \
				  ListNode node, ElmtType* data);

/** evaluates to the number of nodes in the linked list
 * specified by list.
 * @param list list user definition
 * @return size of the list
 * @complexity O(1)
 */
extern int list_size(const List list);
/** evaluates to the node at the head of the linked list
 * specified by list.
 * @param list list user definition
 * @return pointer to the head node of list
 * @complexity O(1)
 */
extern ListNode list_head(const List list);
/** evaluates to the node at the tail of the linked list
 * specified by list.
 * @param list list user definition
 * @return pointer to the tail node of list
 * @complexity O(1)
 */
extern ListNode list_tail(const List list);
/** determines whether the node specified as node
 * is at the head of a linked list.
 * @param list list user definition
 * @param node node user want to evaluate
 * @return 1 if the node is at the head of the list, or 0 otherwise.
 * @complexity O(1)
 */
extern int list_is_head(const List list, \
				 const ListNode node);
/** determines whether the node specified as node
 * is at the tail of a linked list.
 * @param list list user definition
 * @param node node user want to evaluate
 * @return 1 if the node is at the tail of the list, or 0 otherwise.
 * @complexity O(1)
 */
extern int list_is_tail(const ListNode node);

/** evaluates to the data stored in the node of a linked
 * list specified by node.
 * @param node node user want to evaluate
 * @return Data stored in the node.
 * @complexity O(1)
 */
extern ElmtType list_data(const ListNode node);
/** evaluates to the node of a linked list following the
 * node specified by node.
 * @param node node user want to evaluate
 * @return Element following the specified node.
 * @complexity O(1)
 */
extern ListNode list_next(const ListNode node);

extern void list_set_match(List list, \
						   int (*match)(const ElmtType key1, const ElmtType key2));
extern int list_match(const List list, \
					  const ElmtType key1, const ElmtType key2);

extern int list_space(void);

extern void list_debug(const List list);


#ifdef __cplusplus
}
#endif

#endif/* __LIST_H */
/******************* (C) COPYRIGHT 2013 Ted Lin *****END OF FILE****/