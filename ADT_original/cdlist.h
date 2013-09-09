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
#ifndef _CDLIST_H
#define _CDLIST_H

#ifdef __cplusplus
extern"C"{
#endif

/** ADT Circular Doubly Linked List
 * 
 * 
 * Operation
 * 
 * cdlist_create();
 * cdlist_destroy();
 * cdlist_ins_next();
 * cdlist_ins_prev();
 * cdlist_rmv();
 * cdlist_size();
 * cdlist_head();
 * cdlist_is_head();
 * cdlist_data();
 * cdlist_prev();
 * cdlist_next();
 * 
 * 
 * END ADT
 */

/* Includes */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct CDList_t* CDList;
typedef struct CDListNode_t* CDListNode;

extern CDList		cdlist_create(void (*destroy)(void* data));
extern void			cdlist_destroy(CDList list);
extern int			cdlist_ins_prev(CDList list, \
						CDListNode node, const void* data);
extern int			cdlist_ins_next(CDList list, \
						CDListNode node, const void* data);
extern int			cdlist_rmv(CDList list, \
						CDListNode node, void** data);

extern int			cdlist_size(const CDList list);
extern CDListNode	cdlist_head(const CDList list);
extern int			cdlist_is_head(const CDList list,\
						const CDListNode node);
extern int			cdlist_is_mbr(const CDList list, \
						const CDListNode node);

extern void*		cdlist_data(const CDListNode node);
extern CDListNode	cdlist_next(const CDListNode node);
extern CDListNode	cdlist_prev(const CDListNode node);

extern void		cdlist_debug(const CDList list);

#ifdef __cplusplus
}
#endif

#endif/* __CDLIST_H */
/******************* (C) COPYRIGHT 2013 Ted Lin *****END OF FILE****/