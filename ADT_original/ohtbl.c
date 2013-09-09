#include "ohtbl.h"

typedef struct OHTbl_t{
	int position;
	void* vacated;

	int (*h1)(const void* data);
	int (*h2)(const void* data);
	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);

	int size;
	void** table;
}OHTbl;

/*
Theohtbl_createoperation initializes an open-addressed hash table so that it can be
used in other operations (see Example 8-7). Initializing an open-addressed hash
table is a simple operation in which we allocate space for the table; initialize the
pointer in each position to NULL; encapsulate theh1, h2, matchand destroy
functions; initialize vacatedto its sentinel address; and set the sizemember to 0.
The runtime complexity ofohtbl_createis O(m), where mis the number of positions in the 
table. This is because the data pointer in each of the m positions must
be initialized to NULL, and all other parts of the operation run in a constant
amount of time.
*/
void ohtbl_create(OHTbl** htbl, int position, \
				int (*h1)(const void* data), int (*h2)(const void* data), \
				int (*match)(const void* key1, const void* key2), void (*destroy)(void* data))
{
	
}

/*
The ohtbl_destroy operation destroys an open-addressed hash table (see
Example 8-7). Primarily this means freeing the memoryohtbl_createallocated for the
table. The function passed as destroy to ohtbl_createis called once for each
node as it is removed, provide ddestroy was not set to NULL.
The runtime complexity of ohtbl_destroy is O(m), where m is the number of positions 
in the hash table. This is because we must traverse all positions in the hash
table to determine which are occupied. If destroy is NULL, ohtbl_destroyruns in
O(1) time.
*/
void ohtbl_destroy(OHTbl** htbl)
{

}
/*
Theohtbl_insertoperation inserts an node into an open-addressed hash table
(see Example 8-7). Since an open-addressed hash table has a fixed size, we first
ensure that there is room for the new node to be inserted. Also, since a key is
not allowed to be inserted into the hash table more than once, we callohtbl_
lookup to make sure the table does not already contain the new node.
Once these conditions are met, we use double hashing to probe the table for an
unoccupied position. A position in the table is unoccupied if it points either to
NULL or the address invacated, a special member of the hash table data structure 
that indicates that a position has had an node removed from it. Once we
find an unoccupied position in the table, we set the pointer at that position to
point to the data we wish to insert. After this, we increment the table size.
Assuming we approximate uniform hashing well and the load factor of the hash
table is relatively small, the runtime complexity of ohtbl_insert is O(1). This is
because in order to find an unoccupied position at which to insert the node, we
expect to probe 1/(1 ¨C¦Á) positions, a number treated as a small constant, where ¦Á
is the load factor of the hash table.
*/
int ohtbl_insert(OHTbl* htbl, const void* data)
{
	return 0;
}
/*
Theohtbl_remove operation removes an node from an open-addressed hash
table (see Example 8-7). To remove the node, we use double hashing as in
ohtbl_insert to locate the position at which the node resides. We continue
searching until we locate the node or NULL is found. If we find the node, we
setdatato the data being removed and decrease the table size by 1. Also, we set
the position in the table to the vacatedmember of the hash table data structure.
Assuming we approximate uniform hashing well, the runtime complexity ofohtbl_
removeis O(1). This is because we expect to probe 1/(1 ¨C¦Á) positions, a number
treated as a small constant, where ¦Áis the largest load factor of the hash table
since callingohtbl_create. The reason that the performance of this operation depends
on the largest load factor and thus does not improve as nodes are removed is
that we must still probe past vacated positions. The use of the vacatedmember
only improves the performance ofohtbl_insert.
*/
int ohtbl_remove(OHTbl* htbl, const void** data)
{
	return 0;
}
/*
Theohtbl_lookupoperation searches for an node in an open-addressed hash
table and returns a pointer to it (see Example 8-7). This operation works similarly
to ohtbl_remove, except that the node is not removed from the table.
Assuming we approximate uniform hashing well, the runtime complexity ofohtbl_
lookup is the same as ohtbl_remove,orO(1). This is because we expect to probe
1/(1 ¨C¦Á) positions, a number treated as a small constant, where ¦Áis the largest
load factor of the hash table since calling ohtbl_create. The reason that performance
depends on the largest load factor since callingohtbl_createis the same as described
for ohtbl_remove.
*/
int ohtbl_lookup(const OHTbl* htbl, void** data)
{
	return 0;
}

/*
This macro evaluates to the number of nodes in an open-addressed hash table
(see Example 8-6). It works by accessing the size member of the OHTbl structure.
The runtime complexity of ohtbl_sizeis O(1) because accessing a member of a
structure is a simple task that runs in a constant amount of time.
*/
int ohtbl_size(const OHTbl* htbl)
{
	return htbl->size;
}