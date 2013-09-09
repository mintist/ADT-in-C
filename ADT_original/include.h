#ifndef _INCLUDE_H
#define _INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

/* 相对应模块的选择宏开关 */
#undef	TEST_CHTBL
#define TEST_BISTREE
#undef	TEST_BITREE
#undef  TEST_PQUEUE
#undef  TEST_HEAP
#undef  TEST_SET
#undef	TEST_QUEUE
#undef	TEST_STACK
#undef	TEST_CDLIST
#undef	TEST_DLIST
#undef	TEST_CLIST
#undef	TEST_LIST
#undef	TEST_SEARCH_SORT

/* Includes */

#include "comm.h"

#include "list.h"		//singly linked list-单链表
#include "dlist.h"		//doubly linked list-双向链表
#include "clist.h"		//circular linked list-循环链表
#include "cdlist.h"		//doubly circular linked list-双向循环链表	---->>>> 链表数组 & 广义表 & 游标 P84
#include "stack.h"		//stack-栈
#include "queue.h"		//queue-队列								---->>>> 多态 & 双向队列 & 循环队列 P97
#include "set.h"		//set-集合									---->>>> 维恩图 & 位矢量 & 多重集合 P117
#include "heap.h"		//max(min) heap-最大（最小）堆			---->>>> 斐波那契堆 & K叉堆 P205
#include "pqueue.h"		//priority queue-优先级队列

#include "bitree.h"		//binary tree-二叉树
#include "bistree.h"	//binary search tree-二叉搜索树（AVL树-平衡搜索树）	---->>>> K叉树 & 红黑树-平衡搜索树 & Trie树 & B树，B+树及B*树 P187
#include "chtbl.h"		//chained hash table-链式哈希表				---->>>> 开地址哈希表 & 直接寻址哈希表 & 通用散列 P145
#include "ohtbl.h"		//open address hash table-开地址哈希表
/*
#include "darray.h"		//dynamic array-动态数据
#include "xorlist.h"	//xor list-异或链表
#include "graph.h"		//graph-图
*/

#include "sort.h"
//selection sort-选择排序
//insertion sort-插入排序
//bubble sort	-冒泡排序
//shell sort	-希尔排序
//shaker sort	-双冒泡排序
//quick sort	-快速排序
//merge sort	-
//heap sort		-堆排序
//radix sort	-基排序
//tournament sort
//intro sort
//bucket sort	-桶排序
//

#include "search.h"

//linear search-线性查找
//binary search-二分查找
//fibonacci search-斐波那契查找
//interpolation search-插值查找

#ifdef __cplusplus
}
#endif

#endif