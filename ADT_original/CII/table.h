/* $Id: H:/drh/idioms/book/RCS/table.doc,v 1.13 1997/10/27 23:10:11 drh Exp $ */
#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#define T Table_T
typedef struct T * T_P;
extern T_P    Table_new (int hint,
	int cmp(const void *x, const void *y),
	unsigned hash(const void *key));
extern void Table_free(T_P *table);
extern int   Table_length(T_P table);
extern void *Table_put   (T_P table, const void *key,
	void *value);
extern void *Table_get   (T_P table, const void *key);
extern void *Table_remove(T_P table, const void *key);
extern void   Table_map    (T_P table,
	void apply(const void *key, void **value, void *cl),
	void *cl);
extern void **Table_toArray(T_P table, void *end);
#undef T_P
#endif
