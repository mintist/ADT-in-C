#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* �ڵ����洢���������ͣ�void* */
typedef void* ElmtType;

/* ����ֵ������������״̬ */
typedef enum RET_STATE_T
{
	NO_MEM = -1,
	SUCESS = 0,
	NO_RESULT = 1
}ret_state_t;

/* ����ͨ�ý����꣬ɶ�����Ͷ����� */
/* General-purpose swap macro */
#define gen_swap(a, b) do {\
	char c[sizeof(a)]; \
	memcpy((void *)&c, (void *)&a, sizeof(c)); \
	memcpy((void *)&a, (void *)&b, sizeof(a)); \
	memcpy((void *)&b, (void *)&c, sizeof(b)); \
	} while (0)

#define gen_swap_n(a, b, n) do {\
	char c[n]; \
	memcpy((void *)&c, (void *)&a, n); \
	memcpy((void *)&a, (void *)&b, n); \
	memcpy((void *)&b, (void *)&c, n); \
	} while (0)

#endif