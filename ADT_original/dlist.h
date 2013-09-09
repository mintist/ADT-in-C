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
#ifndef _DLIST_H
#define _DLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/** ADT Doubly Linked List
 * 
 * 
 * Operation
 * 
 * dlist_create();
 * dlist_destroy();
 * dlist_ins_next();
 * dlist_ins_prev()
 * dlist_rmv;
 * dlist_size();
 * dlist_head();
 * dlist_tail();
 * dlist_is_head();
 * dlist_is_tail()
 * dlist_data();
 * dlist_next();
 * dlist_prev();
 * 
 * END ADT
 */

/* Includes */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct DList_t* DList;
typedef struct DListNode_t* DListNode;


extern DList	dlist_create(void (*destroy)(void* data));
extern void		dlist_destroy(DList list);

extern int		dlist_ins_prev(DList list, \
						DListNode node, const void* data);
extern int		dlist_ins_next(DList list, \
				   DListNode node, const void* data);
extern int		dlist_rmv(DList list, \
					DListNode node, void** data);

extern int		dlist_size(const DList list);
extern DListNode dlist_head(const DList list);
extern DListNode dlist_tail(const DList list);
extern int		dlist_is_head(const DList list, \
				  const DListNode node);
extern int		dlist_is_tail(const DListNode node);

extern void*	dlist_data(const DListNode node);
extern DListNode dlist_next(const DListNode node);
extern DListNode dlist_prev(const DListNode node);

extern void dlist_debug(const DList list);

#ifdef __cplusplus
}
#endif

#endif/* __DLIST_H */
/******************* (C) COPYRIGHT 2013 Ted Lin *****END OF FILE****/