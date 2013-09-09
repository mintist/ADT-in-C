#include "graph.h"

typedef struct AdjList_t{
	void*		*vertex;
	Set*		adjacent;
}AdjList;


typedef struct Graph_t{
	int			vcount;
	int			ecount;

	int			(*match)(const void* key1, \
						const void* key2);
	void		(*destroy)(void* data);

	List		adjlists;
}Graph;

typedef enum VetexColor_t{white, gray, black}VetexColor;




