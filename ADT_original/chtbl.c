#include "chtbl.h"

typedef struct CHTbl_t{
	int size;
	int buckets;
	
	int (*h)(const ElmtType key);
	int (*match)(const ElmtType key1, const ElmtType key2);
	void (*destroy)(ElmtType data);

	List *table;
}*CHTbl;

/*
The chtbl_create operation initializes a chained hash table so that it can be used in
other operations (see Example 8-3). Initializing a chained hash table is a simple
operation in which we allocate space for the buckets; initialize each bucket by
calling list_create; encapsulate the h, match, and destroy functions; and set the
size member to 0.
The runtime complexity of chtbl_create is O(m), where m is the number of buckets
in the table. This is because the O(1) operation list_create must be called once for
each of them buckets. All other parts of the operation run in a constant amount of
time.
*/
CHTbl chtbl_create(int buckets, int (*h)(const ElmtType key), \
				int (*match)(const ElmtType key1, const ElmtType key2), \
				void (*destroy)(ElmtType data))
{
	int i;
	CHTbl htbl;
	assert(NULL != (htbl = (CHTbl )malloc(sizeof(struct CHTbl_t))));
	assert(NULL != (htbl->table = (List *)malloc(buckets*sizeof(List))));
	
	htbl->size = 0;
	htbl->buckets = buckets;
	htbl->h = h;

	htbl->match = match;
	htbl->destroy = destroy;
	for (i=0; i < htbl->buckets;i++)
	{
		htbl->table[i] = list_create(destroy);
	}

	return htbl;
}

/*
The chtbl_destroy operation destroys a chained hash table (see Example 8-3). 
Primarily this means removing the nodes from each bucket and freeing the 
memory chtbl_create allocated for the table. The function passed as destroy to chtbl_create
is called once for each node as it is removed, provided destroy was not set to
NULL. The runtime complexity of chtbl_destroy is O(m), where m is the number of buckets 
in the table. This is because list_destroy is called once for each bucket. In each
bucket, we expect to remove a number of nodes equal to the load factor of the
hash table, which is treated as a small constant.
*/
void chtbl_destroy(CHTbl htbl)
{
	int i;
	assert(NULL != htbl);

	for (i=0;i < htbl->buckets;i++)
	{
		list_destroy(htbl->table[i]);
	}
	free(htbl->table);
	free(htbl);
}
/*
The chtbl_insert operation inserts an node into a chained hash table (see
Example 8-3). Since a key is not allowed to be inserted into the hash table more
than once, chtbl_lookupis called to make sure that the table does not already 
contain the new node. If no node with the same key already exists in the hash
table, we hash the key for the new node and insert it into the bucket at the
position in the hash table that corresponds to the hash coding. If this is successful,
we increment the table size.
Assuming we approximate uniform hashing well, the runtime complexity of chtbl_insert
is O(1), since chtbl_lookup, hashing a key, and inserting an node at the
head of a linked list all run in a constant amount of time.
*/
int chtbl_insert(CHTbl htbl, const ElmtType data)
{
	ElmtType tmp;
	int bucket;
	assert(NULL != htbl);

	tmp = (ElmtType )data;
	if(chtbl_lookup(htbl, &tmp) == 0)
		return 1;
	//Division Method
	//bucket = htbl->h(data) % htbl->buckets;
	//Multiplication Method
	bucket = (int)(htbl->buckets*( (htbl->h(data)*0.618) -(int)(htbl->h(data)*0.618) ));
	if(list_ins_next(htbl->table[bucket], NULL,data)==0)
	{
		htbl->size++;
		return 0;
	}
	else
		return -1;
}
/*
The chtbl_remove operation removes an node from a chained hash table (see
Example 8-3). To remove the node, we hash its key, search the appropriate
bucket for an node with a key that matches, and call list_rem_next to remove it.
The pointer prev maintains a pointer to the node before the one to be
removed since list_rem_next requires this. Recall that list_rem_next sets data to
point to the data removed from the table. If a matching key is not found in the
bucket, the node is not in the table. If removing the node is successful, we
decrease the table size by 1.
Assuming we approximate uniform hashing well, the runtime complexity of chtbl_
remove is O(1). This is because we expect to search a number of nodes equal
to the load factor of the hash table, which is treated as a small constant.
*/
int chtbl_remove(CHTbl htbl, ElmtType* data)
{
	int bucket;
	ElmtType tmp;

	ListNode	node,
				prev;
	assert(NULL != htbl);
	
	tmp = *data;
	//Division Method
	//bucket = htbl->h(*data) % htbl->buckets;
	//Multiplication Method
	bucket = (int)(htbl->buckets*( (htbl->h(*data)*0.618) -(int)(htbl->h(*data)*0.618) ));
	if(chtbl_lookup(htbl, data) == -1)
		return -1;
	
	prev = NULL;
	for (node = list_head(htbl->table[bucket]); \
		node != NULL ; node = list_next(node))
	{
		if(htbl->match(*data,list_data(node)))
		{
			if (list_rmv_next(htbl->table[bucket], prev, data)==0)
			{
				htbl->size--;
				return 0;
			}
			else
				return -1;
		}
		prev = node;
	}
	
	/* not found in chained hash table */
	return -1;
}
/*
The chtbl_lookup operation searches for an node in a chained hash table and
returns a pointer to it (see Example 8-3). This operation works much like chtbl_
remove, except that once the node is found, it is not removed from the table.
Assuming we approximate uniform hashing well, the runtime complexity of chtbl_
lookup is O(1). This is because we expect to search a number of nodes equal to
the load factor of the hash table, which is treated as a small constant.
*/
int chtbl_lookup(const CHTbl htbl, ElmtType* data)
{
	int bucket;
	ListNode node;
	assert(NULL != htbl);

	//Division Method
	//bucket = htbl->h(*data) % htbl->buckets;
	//Multiplication Method
	bucket = (int)(htbl->buckets*( (htbl->h(*data)*0.618) -(int)(htbl->h(*data)*0.618) ));

	for (node = list_head(htbl->table[bucket]);node != NULL;node = list_next(node))
	{
		if(htbl->match(*data,list_data(node)))
		{
			*data = list_data(node);
			return 0;
		}
	}
	return -1;
}
/*
This macro evaluates to the number of nodes in a chained hash table (see
Example 8-2). It works by accessing the size member of the CHTbl structure.
The runtime complexity of chtbl_size is O(1) because accessing a member of a
structure is a simple task that runs in a constant amount of time.
*/
int chtbl_size(const CHTbl htbl)
{
	return htbl->size;
}

void chtbl_debug(const CHTbl table)
{
	int i;

	if (table->size > 0)
	{
		for (i=0;i<table->buckets;i++)
		{
			printf("table->table[%d] : ",i);
			list_debug(table->table[i]);
			printf("\n");
		}
	}
}