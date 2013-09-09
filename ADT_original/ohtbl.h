#ifndef _OHTBL_H
#define _OHTBL_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes */
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct OHTbl_t OHTbl;

/*
Return Value 0 if initializing the hash table is successful, or 每1 otherwise.
Description Initializes the open-addressed hash table specified by htbl. This
operation must be called for an open-addressed hash table before the hash table
can be used with any other operation. The number of positions to be allocated in
the hash table is specified by positions. The function pointers h1andh2specify
user-defined auxiliary hash functions for double hashing. The function pointer
matchspecifies a user-defined function to determine if two keys match. It should
perform in a manner similar to that described forchtbl_create. The destroyargument provides a way to free dynamically allocated data whenohtbl_destroy is
called. It works in a manner similar to that described for chtbl_destroy. For an
open-addressed hash table containing data that should not be freed,destroy
should be set to NULL.
Complexity O(m), wheremis the number of positions in the hash table.
*/
void ohtbl_create(OHTbl** htbl, int position, \
				int (*h1)(const void* data), int (*h2)(const void* data), \
				int (*match)(const void* key1, const void* key2), void (*destroy)(void* data));
/*
Return Value None.
Description Destroys the open-addressed hash table specified byhtbl.No
other operations are permitted after callingohtbl_destroyunlessohtbl_createis called
again. The ohtbl_destroyoperation removes all nodes from a hash table and
calls the function passed asdestroyto ohtbl_createonce for each node as it is
removed, provideddestroywas not set to NULL.
Complexity O(m), wheremis the number of positions in the hash table.
*/
void ohtbl_destroy(OHTbl** htbl);
/*
Return Value 0 if inserting the node is successful, 1 if the node is already
in the hash table, or 每1 otherwise.
Description Inserts an node into the open-addressed hash table specified
byhtbl. The new node contains a pointer to data, so the memory referenced
bydatashould remain valid as long as the node remains in the hash table. It is
the responsibility of the caller to manage the storage associated with data.
Complexity O(1)
*/
int ohtbl_insert(OHTbl* htbl, const void* data);
/*
Return Value 0 if removing the node is successful, or 每1 otherwise.
Description Removes the node matchingdatafrom the open-addressed
hash table specified byhtbl. Upon return, datapoints to the data stored in the
node that was removed. It is the responsibility of the caller to manage the storage associated with the data.
Complexity O(1)
*/
int ohtbl_remove(OHTbl* htbl, void** data);
/*
Return Value 0 if the node is found in the hash table, or 每1 otherwise.
Description Determines whether an node matchesdata in the openaddressed 
hash table specified byhtbl. If a match is found, upon return data
points to the matching data in the hash table.
Complexity O(1)
*/
int ohtbl_lookup(const OHTbl* htbl, void** data);
/*
Return Value Number of nodes in the hash table.
Description Macro that evaluates to the number of nodes in the 
open addressed hash table specified by htbl.
Complexity O(1)
*/
int ohtbl_size(const OHTbl* htbl);

#ifdef __cplusplus
}
#endif


#endif