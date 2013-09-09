
#include "sort.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef enum bool_t{FLASE, TRUE}bool;

#define sort_swap(a, b) do {	\
	char c[DATA_SIZE];				\
	memcpy((void*)&(c), (void*)&(b), DATA_SIZE);	\
	memcpy((void*)&(b), (void*)&(a), DATA_SIZE);	\
	memcpy((void*)&(a), (void*)&(c), DATA_SIZE);	\
} while (0)


int slt_sort(void* data, int size, int esize, \
			 int (*compare)(const void* key1, const void* key2))
{
	int i_loop, o_loop;
	int min;
	char* a = data;

	for (o_loop = 0;o_loop < size;o_loop++)
	{// outer loop
		min = o_loop;
		for (i_loop = o_loop+1;i_loop < size;i_loop++)
		{//inner loop
			if (compare(a+min*esize, a+i_loop*esize) > 0)
				min = i_loop;
		}

		if (o_loop != min)
		{
			sort_swap(a[o_loop*esize],a[min*esize]);
		}
	}
	return 0;
}

int bubl_sort(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2))
{
	int i_loop, o_loop;
	char* a=data;
	bool flag=TRUE;//如果最后一段是有序的，flag将起作用

	for (o_loop=0;o_loop<size && flag;o_loop++)
	{
		flag = FLASE;
		for (i_loop = 0;i_loop<size-o_loop-1;i_loop++)
		{
			if (compare(a+i_loop*esize,a+(i_loop+1)*esize) > 0)
			{
				sort_swap(a[i_loop*esize],a[(i_loop+1)*esize]);
				flag = TRUE;
			}
		}
	}
	return 0;
}
int shaker_sort(void* data, int size, int esize, \
				int (*compare)(const void* key1, const void* key2))
{
	int i;
	int left=0,right=size-1;
	int shift=0;//如果中间一段是有序的，shift将起作用
	char* a = data;

	while(left < right)
	{
		for (i=left;i<right;i++)
		{//將最大值往右排
			if (compare(a+i*esize,a+(i+1)*esize) > 0)
			{
				sort_swap(a[i*esize], a[(i+1)*esize]);
				shift = i;
			}
		}
		right = shift;

		for (i=right;i>left;i--)
		{//将最小值往左排
			if (compare(a+i*esize, a+(i-1)*esize) < 0)
			{
				sort_swap(a[i*esize], a[(i-1)*esize]);
				shift = i;
			}
		}
		left = shift;
	}

	return 0;
}

int ins_sort(void* data, int size, int esize, \
					int (*compare)(const void* key1, const void* key2))
{
	int i_loop,o_loop;
	void* tmp ;
	char* a = data;
		
	assert(NULL != (tmp = (void* )malloc(esize)));

	for (o_loop = 1;o_loop < size;o_loop++)
	{// total n-1 outer loops
		memcpy(tmp,a+o_loop*esize,esize);
		for (i_loop = o_loop;i_loop > 0 && compare(a+(i_loop-1)*esize, tmp) > 0;i_loop--)
		{//往后面挪一位
			memcpy(a+(i_loop)*esize, a+(i_loop-1)*esize, esize);
		}
		//直到不挪占后面那个坑
		memcpy(a+i_loop*esize, tmp, esize);
	}
	
	free(tmp);
	return 0;
}

int shell_sort(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2))
{
	int o_loop,i_loop;
	int gap;
	void* tmp;
	char* a = data;

	assert(NULL != (tmp = (void* )malloc(esize)));
	for (gap = size/2 ; gap > 0 ; gap = gap/2)
	{//original shell gap
	 //Hibbard shell gap : 1,3,7,...,2^k-1
	 //Sedgewick shell gap : 4^k-3*2^k+1
		for (o_loop=gap;o_loop<size;o_loop++)
		{//insertion sort
			memcpy(tmp, a+o_loop*esize, esize);
			for (i_loop=o_loop;i_loop>=gap && \
				compare(a+(i_loop-gap)*esize, tmp) > 0;i_loop -= gap)
			{
				memcpy(a+i_loop*esize, a+(i_loop-gap)*esize,esize);
			}
			memcpy(a+i_loop*esize,tmp,esize);
		}
	}
	free(tmp);
	return 0;
}

static int quik_sort1_run(void* data, int left, int right, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2))
{//以data[left]，为pivot，left相当于最左边第一个元素
	int i,j;
	char* a = data;

	if (left < right)
	{
		i=left;
		j=right+1;
		while(TRUE)
		{
			// 向右找小於Pivot的數值的位置
			while(i+1 < size && compare(a+(++i)*esize, a+left*esize) < 0);
			 // 向左找大於Pivot的數值的位置
			while(j-1 > -1 && compare(a+(--j)*esize, a+left*esize) > 0);

			// 若i,j的位置交叉
			//     代表範圍內，Pivot右邊已無比Pivot小的數值
			//     代表範圍內，Pivot左邊已無比Pivot大的數值    
			if(i >= j) 
				break;
			 // 將比Pivot大的數值換到右邊，比Pivot小的數值換到左邊
			sort_swap(a[i*esize],a[j*esize]);
		}
		sort_swap(a[left*esize],a[j*esize]);//将pivot移到中间
		quik_sort1_run(data,left,j-1,size,esize,compare);//对左子串进行快速排序
		quik_sort1_run(data,j+1,right,size,esize,compare);//对右子串进行快速排序
	}

	return 0;
}

int quik_sort1(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2))
{
	return quik_sort1_run(data, 0, size-1, size, esize,compare);
}



static int partition(void* data, int left, int right, int esize, \
					 int (*compare)(const void* key1, const void* key2))
{
	int i,j;
	char* a = data;
	i = left-1;
	/**
	 * 将比pivot小的数值右移，比pivot大的数值左移
	 * 最后回传pivot的位置
	 */
	for (j = left; j < right;j++)
	{
		if (compare(a+j*esize, a+right*esize) < 0)
		{//data[right]为pivot
			i++;//计数有几个比pivot小的数值
			sort_swap(a[i*esize], a[j*esize]);
		}
	}
	//将pivot移到中间
	sort_swap(a[(i+1)*esize],a[right*esize]);
	return i+1;
}

static int quik_sort2_run(void* data, int left, int right, int size, int esize, \
						  int (*compare)(const void* key1, const void* key2))
{//固定最后一个数为基准值(Pivot)
	int pivotLocation;
	if (left < right)
	{
		pivotLocation = partition(data, left, right, esize ,compare);
		quik_sort2_run(data, left, pivotLocation-1, size, esize, compare);
		quik_sort2_run(data, pivotLocation+1, right, size, esize, compare);
	}
	return 0;
}

int quik_sort2(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2))
{
	return quik_sort2_run(data, 0, size-1, size, esize, compare);
}

int merge_sort(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2))
{//iterative
	int i, leftMin, leftMax, rightMin, rightMax, next;
	char* tmp = (char* )malloc(size*esize);
	char *a = (char* )data;
	
	for (i = 1;i < size;i *= 2)
	{
		for (leftMin = 0; leftMin < size-i;leftMin = rightMax)
		{
			rightMin = leftMax = leftMin+i;
			rightMax = leftMax+i;
			if(rightMax > size)
				rightMax = size;
			next = 0;
			while(leftMin < leftMax && rightMin < rightMax)
				memcpy(tmp+(next++)*esize,
				(compare(a+leftMin*esize, a+rightMin*esize)
				? a+(rightMin++)*esize
				: a+(leftMin++)*esize), esize);
			while(leftMin < leftMax)
				memcpy(a+(--rightMin)*esize,a+(--leftMax)*esize, esize);
			while(next > 0)
				memcpy(a+(--rightMin)*esize,tmp+(--next)*esize, esize);
		}
	}
	free(tmp);
	return 0;
}

static void heapify(void* data, int root, int size, int esize, \
				   int (*compare)(const void* key1, const void* key2))
{//令root的左、右子树都符合heap，仅root不符合heap，将树调整为max heap
	char* a = data;
	int leftchild = root*2+1;		//root的左子树
	int rightchild = root*2+2;		//root的右子树
	int maxNode = root;

	//找出root，leftchild，rightchild中最大的者(maxNode)
	if(leftchild < size && compare(a+leftchild*esize, a+root*esize) > 0)
		maxNode = leftchild;
	if(rightchild < size && compare(a+rightchild*esize, a+maxNode*esize) > 0)
		maxNode = rightchild;
	//如果最大值不是root，则swap及heapify
	if (maxNode != root)
	{
		sort_swap(a[root*esize],a[maxNode*esize]);
		heapify(data,maxNode,size,esize,compare);
	}
}

int heap_sort(void* data, int size, int esize, \
			  int (*compare)(const void* key1, const void* key2))
{
	int i;
	char *a = data;
	//将数列转换成Max Heap
	for (i=size/2; i >= 0; i--)
	{
		heapify(data,i,size,esize,compare);
	}
	//排序
	for (i=size-1;i>0;i--)
	{
		sort_swap(*a, a[i*esize]);
		heapify(data,0,i,esize,compare);
	}
	return 0;
}

int radix_sort(void* data, int size, int esize, \
			   int (*compare)(const void* key1, const void* key2))
{

	return 0;
}