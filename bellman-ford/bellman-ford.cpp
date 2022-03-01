//Bellman Ford Algorithm in C++
//Letícia Medeiros, Luiz Guimarães e Marcos Ivan
#include <bits/stdc++.h>

#define INT_MAX 999

struct Edge {
	int src, dest, weight;
};

struct Graph {
	int V, E;
	struct Edge* edge;
};

struct Graph* createGraph(int V, int E){
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

void printArr(int dist[], int n){
	printf("Vertex Distance from Source\n");
	for (int i = 1; i < n+1; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(struct Graph* graph, int src){
	int V = graph->V;
	int E = graph->E;
	int dist[V];

	//inicializar as dist como infinito
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;
	//relaxar as arestas
	for (int i = 1; i <= V - 1; i++){
		for (int j = 0; j < E; j++){
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX
				&& dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}
	//checar ciclo negativo
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;

		if (dist[u] != INT_MAX
			&& dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return;//se ciclo negativo, return
		}
	}
	printArr(dist, V);
	return;
}

void read(Graph* graph, int e, int i){
    if(e==i)
        return;
    else{
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        //printf("%d %d %d\n", v1, v2, w);
        graph->edge[i].src = v1;
        graph->edge[i].dest = v2;
        graph->edge[i].weight = w;
        //printf("%d %d %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
  read(graph, e, i+1);
}

int main(){
    int v, e;
    scanf("%d %d", &v, &e);
    Graph* graph = createGraph(v, e);
    read(graph, e, 0);
	BellmanFord(graph, 1);
	return 0;
}
