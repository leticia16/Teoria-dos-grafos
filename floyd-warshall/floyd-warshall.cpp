// Floyd-Warshall Algorithm in C++
// Letícia Medeiros, Luiz Guimarães e Marcos Ivan

#include <iostream>
using namespace std;

#define INF 999 //importante para o algoritmo definir um inteiro grande como peso da aresta,
                //para que os cálculos saiam da maneira esperada

void printMatrix(int matrix[][size]);

void floydWarshall(int graph[][size]) {
  int matrix[size][size], i, j, k;

  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      matrix[i][j] = graph[i][j];

  //Adicionando os vértices
  for (k = 0; k < size; k++) {
    for (i = 0; i < size; i++) {
      for (j = 0; j < size; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j])
          matrix[i][j] = matrix[i][k] + matrix[k][j];
      }
    }
  }
  printMatrix(matrix);
}

void printMatrix(int matrix[][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (matrix[i][j] == INF)
        printf("%4s", "INF");
      else
        printf("%4d", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int graph[size][size];
  floydWarshall(graph);
}