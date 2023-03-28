#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TOTAL_NODE  5

typedef struct _graph graph;

struct _graph {
    int total_nodes;
    bool **edges;//Bool value to indicate there is an edget between 2 nodes
};

graph *init_graph(int total_nodes);
void print_graph(graph *graph);
void add_edge(graph *graph, int from, int to);
void delete_edge(graph *graph, int from, int to);

int main(){
    graph *g;
    g = init_graph(TOTAL_NODE);
    print_graph(g);
}

/*
    Init the direct graph, i.e A[i,j] != A[j,i] (due to the direction)
    Return graph as pointer to store it in heap memory
*/
graph *init_graph(int total_nodes){
    graph *graph = (struct _graph*) malloc(sizeof(graph));
    graph->total_nodes = total_nodes;
    
    graph->edges = (bool**) malloc(total_nodes * sizeof(bool*));

	for (int i = 0; i < total_nodes; i++){
        graph->edges[i] = (bool*) malloc(total_nodes * sizeof(bool));
        memset(graph->edges[i], 0, sizeof(graph->edges[i]));
	}
	return graph;
}

void print_graph(graph *graph){
    for (int from = 0; from < graph->total_nodes; from++){
        for (int to = 0; to < graph->total_nodes; to++){
            if (graph->edges[from][to]){
                printf("%d -> %d\n", from, to);
            }
        }
    }
}

void add_edge(graph *graph, int from, int to){
    graph->edges[from][to] = 1;
}

void delete_edge(graph *graph, int from, int to){
    graph->edges[from][to] = 0;
}
