#ifndef _GRAPH_H
#define _GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes */
#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "set.h"

typedef struct Graph_t Graph;
typedef struct AdjList_t AdjList;

void grapg_create(Graph* graph, int (*match)(const void* key1, \
				const void* key2), void (*destroy)(void* data));
void graph_destroy(Graph* graph);
int graph_ins_vertex(Graph* graph, const void* data);
int graph_ins_edge(Graph* graph, const void* data1, const void* data2);
int graph_rmv_vertex(Graph* graph, void** data);
int graph_rmv_edge(Graph* graph, const void* data1, void** data2);
int graph_adjlist(const Graph* graph, const void* data, AdjList **adjlist);
int graph_is_adjacent(const Graph* graph, const void* data1, const void* data2);
List graph_adjlists(const Graph* graph);
int graph_vcount(const Graph* graph);
int graph_ecount(const Graph* graph);


#ifdef __cplusplus
}
#endif

#endif