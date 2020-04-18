#include <stdlib.h>
#include "graph.h"

TGraph *gr_init() {

	TGraph *g;

	g = (TGraph*)malloc(sizeof(TGraph));

	if (g != NULL) {
		g->nodes = NULL;
		g->node_count = 0;
		g->edges = 0;
		g->edge_count = 0;
	}

	return g;
}

TNode *gr_create_node(int val) {

	TNode* node;

	node = (TNode*)malloc(sizeof(TNode));

	if (node != NULL) {
		node->val = val;
	}

	return node;
}


int gr_add_node(TGraph* g, TNode* n) {

	int old_count;
	int old_nodes;

	old_count = g->node_count;
	old_nodes = g->nodes;

	g->node_count++;

	g->nodes = (TNode*)realloc(g->nodes, g->node_count * sizeof(TNode));

	if (g->nodes != NULL) {

		g->nodes[old_count] = n;

		return 1;
	}
	else {
		g->nodes = old_nodes;

		return 0;
	}
}

TNode *gr_find_node(TGraph* g, TNode* val) {
	for (int i = 0; i < g->node_count; i++) {
		if (g->nodes[i] == val) return &g->nodes[i];
	}

	return NULL;
}

int gr_remove_node(TGraph* g, TNode* n) {

	if (gr_find_node(g, n) != NULL) {

		int i = 0;
		int old_count;
		TNode** old_nodes;

		old_count = g->node_count;
		old_nodes = g->nodes;

		g->nodes = (TNode*)malloc(sizeof(TNode) * old_count - 1);

		if (g->nodes != NULL) {

			TNode** nodes = g->nodes;

			for (; i < old_count; i++) {
				if (old_nodes[i] == n) {
					for (; i < old_count; i++) {
						nodes[i] = old_nodes[i + 1];
					}

					break;
				}
				else {
					nodes[i] = old_nodes[i];
				}
			}

			g->node_count--;

			if (g->edge_count != 0) {
				for (i = 0; i < g->edge_count; i++) {
					if (g->edges[i].from == n) {
						gr_remove_edge(g, n, g->edges[i].to);
						i--;
					}
					else if (g->edges[i].to == n) {
						gr_remove_edge(g, g->edges[i].from, n);
						i--;
					}
				}
			}

			return 1;

		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void nodes_traverse(TGraph* g, TFunc f) {
	for (int i = 0; i < g->node_count; i++) {
		f("%d\n", g->nodes[i]->val);
	}
}

int gr_add_edge(TGraph* g, TNode* from, TNode* to) {

	if (gr_find_edge(g, from, to) == 1) {

		int old_count = g->edge_count;
		TEdge *old_edges = g->edges;

		g->edges = (TEdge*)malloc(sizeof(TEdge) * old_count + 1);

		if (g->edges != NULL) {

			for (int i = 0; i < old_count; i++) {
				g->edges[i].from = old_edges[i].from;
				g->edges[i].to = old_edges[i].to;
			}

			g->edges[old_count].from = from;
			g->edges[old_count].to = to;

			g->edge_count++;

			return 1;
		}
		else {
			g->edges = old_edges;

			return 0;
		}
	}
	else {
		return 0;
	}
}

int gr_find_edge(TGraph* g, TNode* from, TNode* to) {

	int i = 0;
	int res = 0;

	for (; i < g->node_count; i++) {
		if (g->nodes[i] == from) {
			res++;
			break;
		}
	}

	for (i = 0; i < g->node_count; i++) {
		if (g->nodes[i] == to) {
			res++;
			break;
		}
	}

	if (res == 2) {
		return 1;
	}
	else {
		return 0;
	}
}

int gr_remove_edge(TGraph* g, TNode* from, TNode* to) {

	int old_count;
	TEdge* old_edges;

	old_count = g->edge_count;
	old_edges = g->edges;

	g->edges = (TEdge*)malloc(sizeof(TEdge*) * old_count - 1);

	if (g->edges != NULL) {

		TEdge* edges = g->edges;

		for (int i = 0; i < old_count; i++) {
			if (old_edges[i].from == from && old_edges[i].to == to) {
				for (; i < old_count; i++) {
					edges[i].from = old_edges[i + 1].from;
					edges[i].to = old_edges[i + 1].to;
				}

				break;
			}
			else {
				edges[i].from = old_edges[i].from;
				edges[i].to = old_edges[i].to;
			}
		}

		g->edge_count--;

		return 1;
	}
	else {
		return 0;
	}
}

void edges_traverse(TGraph* g, TFunc f) {

	int j = 1;

	for (int i = 0; i < g->edge_count; i++) {
		f("%d:", j);
		f(" %d", g->edges[i].from->val);
		f(" %d\n", g->edges[i].to->val);
		j++;
	}
}