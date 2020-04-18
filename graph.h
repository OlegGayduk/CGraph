#ifndef __GRAPH__
#define __GRAPH__

typedef struct TNode {
	int val;
} TNode;

typedef struct TEdge {
	TNode *from, *to;
} TEdge;

typedef struct TGraph {
	TNode **nodes;
	int node_count;
	TEdge *edges;
	int edge_count;
} TGraph;

typedef void *TFunc(int);

TGraph *gr_init();

TNode *gr_create_node(int val);

int gr_add_node(TGraph* g, TNode* n);

TNode *gr_find_node(TGraph* g, TNode* val);

int gr_remove_node(TGraph* g, TNode* n);

void nodes_traverse(TGraph* g, TFunc f);

int gr_add_edge(TGraph* g, TNode* from, TNode* to);

int gr_remove_edge(TGraph* g, TNode* from, TNode* to);

void edges_traverse(TGraph* g, TFunc f);

#endif
