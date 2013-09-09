#include "set.h"

/************************************************************************
The set_create operation initializes a set so that it can be used in other operations
. Since a set is a linked list, list_create is called to initialize it. The
match member is set to match by hand because this member is not used by
linked lists and is therefore not set by list_create.
The runtime complexity of set_create is the same as list_create, or O(1).
************************************************************************/
Set set_create(int (*match)(const ElmtType key1, const ElmtType key2), \
			  void (*destroy)(ElmtType data))
{
	Set set;
	set = list_create(destroy);
	list_set_match(set, match);

	return set;
}
/************************************************************************
The set_destroy operation destroys a set. Since a set is a linked
list and requires being destroyed in the same manner, set_destroy is defined to 
list_destroy.
The runtime complexity of set_destroy is the same as list_destroy,orO(n), where n
is the number of members in the set.
************************************************************************/
void set_destroy(Set set)
{
	list_destroy(set);
}
/************************************************************************
The set_insert operation inserts a member into a set. Since a
member must not occur more than once in a set,set_is_member is called to make
sure that the set does not already contain the new member. As long as the member
does not already exist in the set,list_ins_next is called to insert the member.
The runtime complexity of set_insert is O(n) because set_is_member runs in O(n)
time, and list_ins_next runs in O(1).
************************************************************************/
int set_insert(Set set, const ElmtType data)
{

	if (set_is_mbr(set, data))
		return 1;
	return list_ins_next(set, NULL, data);
}
/************************************************************************
The set_remove operation removes a member from a set by traversing it using 
list_next until match determines that the member to be removed has been found (see
Example 7-2). The pointer prev points just before the member to be removed
since this is required by list_rmv_next. The list_rvm_next operation sets data to
point to the data from the member removed.
The runtime complexity of set_remove is O(n), where n is the number of nodes 
in the set. This is because, in the worst case, the entire set must be traversed 
in order to find the member to be removed. This results in n times O(1),
the cost of the statements within the loop, for a running time of O(n) overall.
Once the member is found,list_rmv_next removes it in O(1) time.
************************************************************************/
int set_remove(Set set, ElmtType* data)
{
	ListNode node,prev;

	prev = NULL;				//to strore the right's previous node 
	for (node = list_head(set);node != NULL; node = list_next(node))
	{
		if (list_match(set, list_data(node), *data))
		{
			break;
		}
		prev = node;			//must outside of "if"
	}
	if (node == NULL)			//not in the set
	{
		return -1;
	}

	return list_rmv_next(set, prev, data);
}
/************************************************************************
The set_union operation builds a set,setu, which is the union of the sets set1
and set2(see Example 7-2). First, setu is initialized by calling set_create. Next, the
members of set1 are inserted into setu by calling list_ins_next repeatedly for
each member of set1. Finally, the members of set2 are inserted into setu in a
similar manner except that set_is_member is called before each insertion to ensure
that no members are duplicated in setu.
The runtime complexity of set_union is O(mn), where m is the size of set1 and n
is the size of set2. In the first loop, each member of set1 is traversed and
inserted into setu, which results in a running time of O(m). In the second loop,
each node of set2 is traversed, which results in n times the cost of the statements 
within this loop. This loop contains the O(m) operation set_is_member.
Therefore, the overall complexity of the loop is O(mn). Since the two loops are
executed one after another, the complexity of set_union is the more expensive of
the two, or O(mn).
************************************************************************/
int set_union(Set setu, \
			  const Set set1, const Set set2)
{
	ListNode node;

	for (node=list_head(set1);node!=NULL;node=list_next(node))
	{	/* insert set1's node into setu */
		if (list_ins_next(setu,NULL,list_data(node))==-1)
			return -1;
	}
	for (node=list_head(set2);node!=NULL;node=list_next(node))
	{	/* insert set2's node into setu if it isn't in setu */
		if (!set_is_mbr(setu, list_data(node)))
			if (list_ins_next(setu,NULL,list_data(node))==-1)
				return -1;
	}

	return 0;
}
int set_intersection(Set seti, \
					 const Set set1, const Set set2)
{
	ListNode node;

	for (node=list_head(set1);node!=NULL;node=list_next(node))
	{	/* insert set1's node which set2 contains into seti */
		if (set_is_mbr(set2, list_data(node)))
		{
			if (list_ins_next(seti,NULL,list_data(node))==-1)
				return -1;
		}
	}
	return 0;
}
int set_difference(Set setd, \
				   const Set set1, const Set set2)
{
	ListNode node;
	for (node=list_head(set1);node!=NULL;node=list_next(node))
	{	/* insert set1's node which set2 doesn't contain into setd */
		if ( !set_is_mbr(set2, list_data(node)))
		{
			if (list_ins_next(setd,NULL,list_data(node))==-1)
				return -1;
		}
	}
	return 0;
}
/************************************************************************
The set_is_member operation determines whether a particular member exists in a
set (see Example 7-2). This is accomplished by traversing the set using list_next
until either a member matching data is found or all members are traversed.
The runtime complexity of set_is_member is O(n), where n is the number of members
in the set. This is because, in the worst case, the entire set must be traversed
to find the member for which we are searching.
************************************************************************/
int set_is_mbr(const Set set, \
			   const ElmtType data)
{
	ListNode node;
	/* traverse the set with node */
	for (node=list_head(set);node!=NULL;node=list_next(node))
	{
		if ( list_match(set, list_data(node), data) )
			return 1;
	}
	return 0;
}
/************************************************************************
The set_is_subset operation determines whether one set, set1, is a subset of
another set,set2(see Example 7-2). Since a set that is a subset of another must
be the same size or smaller, we begin by comparing sizes. If this test fails, then
set1 is not a subset of set2. Otherwise, set1 is traversed using list_next until
either a member of set1 that is not in set2 is found or all members are traversed. 
If we find a member of set1 not in set2, then set1 is not a subset of
set2. If we end up traversing all members of set1, then set1is a subset of set2.
The runtime complexity of set_is_subset is O(mn), where m is the size of set1
and n is the size of set2. This is because for each member in set1, the O(n)
operation set_is_member is called to determine whether the member is in set2.
************************************************************************/
int set_is_subset(const Set set, \
				  const Set subset)
{
	ListNode subnode;
	if (set_size(set) < set_size(subset))
		return 0;
	/* traverse the subset's node */
	for (subnode = list_head(subset);subnode!=NULL;subnode=list_next(subnode))
	{
		if ( !set_is_mbr(set ,list_data(subnode)) )
			return 0;
	}
	return 1;
}
/************************************************************************
The set_is_equal operation determines whether one set,set1, is equal to another
set,set2(see Example 7-2). Since two sets that are equal must be the same size,
we begin by comparing sizes. If the two sets are not the same size, then they are
not equal. If the two sets are the same size, we need only return the result of
whether set1is a subset of set2. This is determined by calling set_is_subset.
The runtime complexity of set_is_equal is O(mn), where m is the size of set1and
n is the size of set2. This is because set_is_subset runs in O(mn) time.
************************************************************************/
int set_is_equal(const Set set1, \
				 const Set set2)
{
	if(set_size(set1) != set_size(set2))
		return 0;
	return set_is_subset(set1,set2);
}
/************************************************************************
This macro evaluates to the size of a set (see Example 7-1). It works by accessing
the size member of the Set structure.
The runtime complexity of set_size is O(1) because accessing a member of a structure 
is a simple task that runs in a constant amount of time.
************************************************************************/
__inline int set_size(const Set set)
{
	return list_size(set);
}

void set_debug(const Set set)
{
	ListNode elemt = NULL;

	if (list_size(set) > 0)
	{
		printf("head:");
		for (elemt = list_head(set);elemt != NULL;elemt=list_next(elemt))
		{
			printf("%d->", *(int*)list_data(elemt));
		}
		printf("NULL \n");
	}
}