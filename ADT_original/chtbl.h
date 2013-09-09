#ifndef _CHTBL_H
#define _CHTBL_H

#ifdef __cplusplus
}
#endif

/* includes */
#include "comm.h"

#include "list.h"


typedef struct CHTbl_t* CHTbl;
/*
Return Value 0 if initializing the hash table is successful, or 每1 otherwise.
Description Initializes the chained hash table specified by htbl. This operation 
must be called for a chained hash table before the hash table can be used
with any other operation. The number of buckets allocated in the hash table is
specified by buckets. The function pointer h specifies a user-defined hash function
for hashing keys. The function pointer match specifies a user-defined function to 
determine whether two keys match. It should return 1 if key1is equal to
key2, and 0 otherwise. The destroy argument provides a way to free dynamically 
allocated data when chtbl_destroy is called. For example, if the hash table
contains data dynamically allocated using malloc, destroy should be set to free to
free the data as the hash table is destroyed. For structured data containing several
dynamically allocated members,destroy should be set to a user-defined function
that calls free for each dynamically allocated member as well as for the structure
itself. For a hash table containing data that should not be freed, destroy should
be set to NULL.
Complexity O(m), where m is the number of buckets in the hash table.
*/
CHTbl chtbl_create(int buckets, int (*h)(const ElmtType key), \
				 int (*match)(const ElmtType key1, const ElmtType key2), \
				 void (*destroy)(ElmtType data));
/*
Return Value None.
Description Destroys the chained hash table specified byhtbl. No other
operations are permitted after callingchtbl_destroyunlesschtbl_createis called again.
Thechtbl_destroyoperation removes all nodes from a hash table and calls the
function passed as destroyto chtbl_createonce for each node as it is removed,
provideddestroywas not set to NULL.
Complexity O(m), wheremis the number of buckets in the hash table.
*/
void chtbl_destroy(CHTbl htbl);
/*
Return Value 0 if inserting the node is successful, 1 if the node is already
in the hash table, or 每1 otherwise.
Description Inserts an node into the chained hash table specified by htbl.
The new node contains a pointer todata, so the memory referenced by data
should remain valid as long as the node remains in the hash table. It is the
responsibility of the caller to manage the storage associated withdata.
Complexity O(1)
*/
int chtbl_insert(CHTbl htbl,const ElmtType data);
/*
Return Value 0 if removing the node is successful, or 每1 otherwise.
Description Removes the node matchingdatafrom the chained hash table
specified byhtbl. Upon return, datapoints to the data stored in the node that
was removed. It is the responsibility of the caller to manage the storage associated
with the data.
Complexity O(1)
*/
int chtbl_remove(CHTbl htbl, ElmtType* data);
/*
Return Value 0 if the node is found in the hash table, or 每1 otherwise.
Description Determines whether an node matchesdatain the chained
hash table specified byhtbl. If a match is found, datapoints to the matching
data in the hash table upon return.
Complexity O(1)
*/
int chtbl_lookup(const CHTbl htbl, ElmtType* data);
/*
Return Value Number of nodes in the hash table.
Description Macro that evaluates to the number of nodes in the chained
hash table specified by htbl.
Complexity O(1)
*/
int chtbl_size(const CHTbl htbl);

void chtbl_debug(const CHTbl table);

#ifdef __cplusplus
}
#endif


#endif