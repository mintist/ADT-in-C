#ifndef _SET_H
#define _SET_H

/** ADT Set by List
 * 
 * 
 * Operation
 * 
 * set_create();
 * set_destroy();
 * set_insert();
 * set_remove();
 * set_union();
 * set_intersection();
 * set_difference();
 * set_is_mbr();
 * set_is_subset();
 * set_is_equal()
 * set_size();
 * 
 * 
 * END ADT
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

typedef List Set;


/*
Return	Value None.

Description	Initializes the set specified by set. This operation must be called
for a set before the set can be used with any other operation. The match argument 
is a function used by various set operations to determine if two members
match. It should return 1 if key1 is equal to key2, and 0 otherwise. The destroy
argument provides a way to free dynamically allocated data when set_destroy is
called. For example, if the set contains data dynamically allocated using malloc,
destroy should be set to free to free the data as the set is destroyed. For
structured data containing several dynamically allocated members, destroy should be
set to a user-defined function that calls free for each dynamically allocated 
member as well as for the structure itself. For a set containing data that should not be
freed, destroy should be set to NULL.

Complexity	O(1)
*/
extern Set set_create(int (*match)(const ElmtType key1, const ElmtType key2), \
			  void (*destroy)(ElmtType data));

/*
Return Value None.
Description Destroys the set specified by set. No other operations are permitted 
after calling set_destroy unlessset_create is called again. The set_destroy operation 
removes all members from a set and calls the function passed as destroy to
set_create once for each member as it is removed, provided destroy was not set to
NULL.
Complexity O(n), where n is the number of members in the set.
*/
extern void set_destroy(Set set);
/*
Return Value 0 if inserting the member is successful, 1 if the member is already
in the set, or 每1 otherwise.
Description Inserts a member into the set specified by set. The new member
contains a pointer to data, so the memory referenced by data should remain
valid as long as the member remains in the set. It is the responsibility of the caller
to manage the storage associated with data.
Complexity O(n), where n is the number of members in the set.
*/
extern int set_insert(Set set, const ElmtType data);
/*
Return Value 0 if removing the member is successful, or 每1 otherwise.
Description Removes the member matching data from the set specified by
set. Upon return, data points to the data stored in the member that was
removed. It is the responsibility of the caller to manage the storage associated with
the data.
Complexity O(n), where n is the number of members in the set.
*/
extern int set_remove(Set set, ElmtType* data);
/*
Return Value 0 if computing the union is successful, or 每1 otherwise.
Description Builds a set that is the union of set1 and set2. Upon return,
setu contains the union. Because setu points to data in set1 and set2, the data
in set1 ands et2 must remain valid until setu is destroyed with set_destroy.
Complexity O(mn), where m and n are the number of members inset1and
set2, respectively.
*/
extern int set_union(Set setu, \
			  const Set set1, const Set set2);
/*
Return Value 0 if computing the intersection is successful, or 每1 otherwise.
Description Builds a set that is the intersection ofset1and set2. Upon
return, seti contains the intersection. Because seti points to data inset1, the
data in set1 must remain valid until seti is destroyed with set_destroy.
Complexity O(mn), where m and n are the number of members in set1 and
set2, respectively.
*/
extern int set_intersection(Set seti, \
					 const Set set1, const Set set2);
/*
Return Value 0 if computing the difference is successful, or 每1 otherwise.
Description Builds a set that is the difference of set1 and set2. Upon return,
setd contains the difference. Because setd points to data in set1, the data in
set1 must remain valid until setd is destroyed with set_destroy.
Complexity O(mn), where m and n are the number of members in set1 and
set2, respectively.
*/
extern int set_difference(Set setd, \
				   const Set set1, const Set set2);
/*
Return Value 1 if the member is found, or 0 otherwise.
Description Determines whether the data specified by data matches that of a
member in the set specified by set.
Complexity O(n), where n is the number of members in the set.
*/
extern int set_is_mbr(const Set set, \
			   const ElmtType data);
/*
Return Value 1 if the set is a subset, or 0 otherwise.
Description Determines whether the set specified byset1is a subset of the
set specified by subset.
Complexity O(mn), where m and n are the number of members in set1 and
subset, respectively.
*/
extern int set_is_subset(const Set set, \
				  const Set subset);
/*
Return Value 1 if the two sets are equal, or 0 otherwise.
Description Determines whether the set specified by set1 is equal to the set
specified by set2.
Complexity O(mn), where m and n are the number of members in set1 and
set2, respectively.
*/
extern int set_is_equal(const Set set1, \
				 const Set set2);
/*
Return Value Number of members in the set.
Description Inline Function that evaluates to the number of members in the set specified by set.
Complexity O(1)
*/
extern int set_size(const Set set);


void set_debug(const Set set);

#ifdef __cplusplus
}
#endif

#endif
