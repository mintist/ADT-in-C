#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* 节点所存储的数据类型：void* */
typedef void* ElmtType;

/* 返回值表明函数调用状态 */
typedef enum RET_STATE_T
{
	NO_MEM = -1,
	SUCESS = 0,
	NO_RESULT = 1
}ret_state_t;

/* 两个通用交换宏，啥子类型都可以 */
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