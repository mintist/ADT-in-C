#include "search.h"
#include <limits.h>
#include <stdio.h>

int linear_search(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2))
{
	int i;
	char* a = sorted;
	static int times;
	for (i = 0;i < size ;i++)
	{
		times++;
		if(compare(target, a+i*esize)==0)
		{
			printf("linear_search_times = %d\n", times);
			return i;
		}
	}
	return -1;
}

int binary_search(void* sorted, void* target, int size, int esize, \
				  int (*compare)(const void* key1, const void* key2))
{//increment
	int left = 0, right = size-1, middle;
	char* a = sorted;

	static int times;

	while(left <= right)
	{
		times++;
		middle = (left+right)/2;
		switch(compare(target, a+middle*esize))
		{
			case -1:
				right = middle - 1;
				break;
			case 1:
				left = middle + 1;
				break;
			case 0:
				printf("binary_search_times = %d\n", times);
				return middle;
		}
	}

	return -1;
}

/*
  Fibonaccian search for locating the index of "key" in an array "pData" of size "n"
  that is sorted in ascending order. See http://doi.acm.org/10.1145/367487.367496

  Algorithm description
  -----------------------------------------------------------------------------
  Let Fk represent the k-th Fibonacci number where Fk+2=Fk+1 + Fk for k>=0 and
  F0 = 0, F1 = 1. To test whether an item is in a list of n = Fm ordered numbers,
  proceed as follows:
  a) Set k = m.
  b) If k = 0, finish - no match.
  c) Test item against entry in position Fk-1.
  d) If match, finish.
  e) If item is less than entry Fk-1, discard entries from positions Fk-1 + 1 to n.
     Set k = k - 1 and go to b).
  f) If item is greater than entry Fk-1, discard entries from positions 1 to Fk-1.
     Renumber remaining entries from 1 to Fk-2, set k = k - 2 and go to b)

  If Fm>n then the original array is augmented with Fm-n numbers larger
  than key and the above algorithm is applied.
 */
int fibonacci_search(void* sorted, void* target, int size, int esize, \
					 int (*compare)(const void* key1, const void* key2))
{
    register int k, idx, offs;
    static int prevn = -1, prevk = -1;
	char* a = sorted;
	static int times;
    /*  Precomputed Fibonacci numbers F0 up to F46. This implementation assumes that the size n
     *  of the input array fits in 4 bytes. Note that F46=1836311903 is the largest Fibonacci
     *  number that is less or equal to the 4-byte INT_MAX (=2147483647). The next Fibonacci
     *  number, i.e. F47, is 2971215073 and is larger than INT_MAX, implying that it does not
     *  fit in a 4 byte integer. Note also that the last array node is INT_MAX rather than
     *  F47. This ensures correct operation for n>F46.
     */
    const static int Fib[47 + 1] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765,
                                    10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578,
                                    5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296,
                                    433494437, 701408733, 1134903170, 1836311903, INT_MAX
                                   };

    /* find the smallest fibonacci number that is greater or equal to n. Store this
     * number to avoid recomputing it in the case of repetitive searches with identical n.
     */
    if(size != prevn)
    {
        register int f0, f1, t;
        for(f0 = 0, f1 = 1, k = 1; f1 < size; t = f1, f1 += f0, f0 = t, ++k);

        prevk = k;
        prevn = size;
    }
    else
        k = prevk;

    /* If the sought value is larger than the largest Fibonacci number less than n,
     * care must be taken top ensure that we do not attempt to read beyond the end
     * of the array. If we do need to do this, we pretend that the array is padded
     * with nodes larger than the sought value.
     */
    for(offs = 0; k > 0;  )
    {
        idx = offs + Fib[--k];

        /* note that at this point k  has already been decremented once */
        if(idx >= size || compare(target, a+idx*esize) < 0) // index out of bounds or key in 1st part
        {
			times++;
            continue;
        }
        else if (compare(target, a+idx*esize) > 0)
        {
			times++;
            // key in 2nd part
            offs = idx;
            --k;
        }
        else // key==pData[idx], found
		{
			printf("fibonacci_search_times = %d\n", times);
            return idx;
		}
    }

    return -1; // not found
}


int interpolation_search(void* sorted, void* target, int size, int esize, \
						 int (*compare)(const void* key1, const void* key2))
{//increment
	int left = 0, right = size-1, middle;
	char* a = sorted;

	static int times;

	while(left <= right)
	{
		times++;
		middle = left + (right - left)*(*(int*)target - *(int*)(a+left*esize))/(*(int*)(a+right*esize)-*(int*)(a+left*esize));
		switch(compare(target, a+middle*esize))
		{
		case -1:
			right = middle - 1;
			break;
		case 1:
			left = middle + 1;
			break;
		case 0:
			printf("interpolation_search_times = %d\n", times);
			return middle;
		}
	}
	return -1;
}