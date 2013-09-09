#ifndef _INCLUDE_H
#define _INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ���Ӧģ���ѡ��꿪�� */
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

#include "list.h"		//singly linked list-������
#include "dlist.h"		//doubly linked list-˫������
#include "clist.h"		//circular linked list-ѭ������
#include "cdlist.h"		//doubly circular linked list-˫��ѭ������	---->>>> �������� & ����� & �α� P84
#include "stack.h"		//stack-ջ
#include "queue.h"		//queue-����								---->>>> ��̬ & ˫����� & ѭ������ P97
#include "set.h"		//set-����									---->>>> ά��ͼ & λʸ�� & ���ؼ��� P117
#include "heap.h"		//max(min) heap-�����С����			---->>>> 쳲������� & K��� P205
#include "pqueue.h"		//priority queue-���ȼ�����

#include "bitree.h"		//binary tree-������
#include "bistree.h"	//binary search tree-������������AVL��-ƽ����������	---->>>> K���� & �����-ƽ�������� & Trie�� & B����B+����B*�� P187
#include "chtbl.h"		//chained hash table-��ʽ��ϣ��				---->>>> ����ַ��ϣ�� & ֱ��Ѱַ��ϣ�� & ͨ��ɢ�� P145
#include "ohtbl.h"		//open address hash table-����ַ��ϣ��
/*
#include "darray.h"		//dynamic array-��̬����
#include "xorlist.h"	//xor list-�������
#include "graph.h"		//graph-ͼ
*/

#include "sort.h"
//selection sort-ѡ������
//insertion sort-��������
//bubble sort	-ð������
//shell sort	-ϣ������
//shaker sort	-˫ð������
//quick sort	-��������
//merge sort	-
//heap sort		-������
//radix sort	-������
//tournament sort
//intro sort
//bucket sort	-Ͱ����
//

#include "search.h"

//linear search-���Բ���
//binary search-���ֲ���
//fibonacci search-쳲���������
//interpolation search-��ֵ����

#ifdef __cplusplus
}
#endif

#endif