#include <stdio.h>
#include "graph.h"

void print(char type[10], int value) {
	printf(type, value);
}

int main(int argc, char** argv) {

	int res;

	TGraph *graph;

	TNode *node,*node2,*node3;

	graph = gr_init();

	node = gr_create_node(1);
	res = gr_add_node(graph, node);

	node2 = gr_create_node(2);
	res = gr_add_node(graph, node2);

	node3 = gr_create_node(3);
	res = gr_add_node(graph, node3);

	nodes_traverse(graph, print);

	res = gr_add_edge(graph, node, node2);
	res = gr_add_edge(graph, node2, node3);

	res = gr_remove_edge(graph, node2, node3);

	res = gr_add_edge(graph, node, node3);

	gr_remove_node(graph, node);
	gr_remove_node(graph, node2);
	gr_remove_node(graph, node3);

	edges_traverse(graph, print);

	return 0;
}
