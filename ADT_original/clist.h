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
#ifndef _CLIST_H
#define _CLIST_H

/** ADT Circular Linked List
 * 
 * 
 * Operation
 * 
 * clist_create();
 * clist_destroy();
 * clist_ins_next();
 * clist_rmv_next();
 * clist_size();
 * clist_head();
 * clist_is_head();
 * clist_data();
 * clist_next();
 * 
 * 
 * END ADT
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct CList_t* CList;
typedef struct CListNode_t* CListNode;

extern CList	clist_create(void (*destroy)(void* data));
extern void		clist_destroy(CList list);
extern int		clist_ins_next(CList list, \
				   CListNode node, const void* data);
extern int		clist_rmv_next(CList list, \
				   CListNode node, void** data);

extern int		clist_size(const CList list);
extern CListNode clist_head(const CList list);
extern int		clist_is_head(const CList list,\
				  const CListNode node);

extern void*	clist_data(const CListNode node);
extern CListNode clist_next(const CListNode node);

extern void clist_debug(const CList list);

#ifdef __cplusplus
}
#endif

#endif/* __CLIST_H */
/******************* (C) COPYRIGHT 2013 Ted Lin *****END OF FILE****/