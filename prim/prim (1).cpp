// Prim - Arvore Geradora Minima (AGM) - C++
// Leticia Medeiros, Luiz Guimarães e Marcos Ivan
#include <bits/stdc++.h>
#include <string.h>
using namespace std;

#define size 1 //definir size como a qtde de vertices do grafo

//Funcao para achar o vertice com menor peso dentre os que ainda nao estao na AGM
int minKey(int key[], bool agmSet[])
{
	//Inicializa o minimo
	int min = INT_MAX, min_index;
	for (int v = 0; v < size; v++)
		if (agmSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

//Imprimir a arvore geradora minima
void printAGM(int parent[], int graph[size][size])
{
	cout<<"Edge \tWeight\n";
	for (int i = 1; i < size; i++)
		cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
}

//Algoritmo de Prim com matriz de adjacencia
void prim(int grafo[size][size])
{
	//Array para armazenar o caminho da arvore geradora minima
	int pais[size];
	//Menor arestas no corte
	int key[size];
	//Vertices inclusos na AGT
	bool agmSet[size];

	for (int i = 0; i < size; i++)
		key[i] = INT_MAX, agmSet[i] = false;

	//Sempre incluir o primeiro vértice
	//Chave como 0
	key[0] = 0;
	pais[0] = -1; //Primeiro no eh raiz da arvore

	//V vertices na AGM
	for (int count = 0; count < size - 1; count++)
	{
		//Vertice com menor valor
		int u = minKey(key, agmSet);

		//Adiciona a AGM
		agmSet[u] = true;

		//Atualiza os valores, considerando apenas os que não estão ainda
		for (int v = 0; v < size; v++)
			if (grafo[u][v] && agmSet[v] == false && grafo[u][v] < key[v])
				pais[v] = u, key[v] = grafo[u][v];
	}

	// imprime a arvore geradora minima
	printAGM(pais, grafo);
}

int main(int argc, char** argv){
    //chamada da função eh com matriz de adj de inteiro
    //int grafo[][];
    for(int i = 0; i<argc; i++){
        if(strcmp(argv[i],"-h")==0){
            //mostrar o help
            help();
        }
        if(strcmp(argv[i],"-o")==0){
            //redirecionar a saída para o arquivo
        }
        if(strcmp(argv[i],"-f")==0){
            //indica o arquivo que contém o grafo de entrada
        }
        if(strcmp(argv[i],"-s")==0){
            //mostra a solução (em ordem crescente)
        }
        if(strcmp(argv[i],"-i")==0){
            //vértice inicial
            int firstVertex = int(argv[i+1]);
        }
        if(strcmp(argv[i],"-l")==0){
            //vértice final
            int lastVertex = int(argv[i+1]);
        }
    }
    return 0;
}
