#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <string>
ofstream fileOut;

typedef pair<int, int> ii;

// read the inFile
const int INF = 1e9;
ifstream inFile;
string line_file;
vector <int> numbers_line;
int aux_v, aux_e;



int nVertices, nEdges;

vector<vector<ii>> adj;
vector<int> dist;
vector<bool> visited;


//read the in File
int concatNumber(int prev, int next){
    string a = to_string(prev);
    string b = to_string(next);
    string number = a + b;
    int num = stoi(number);
    return num;
}

void linesReader (string line){
    int j = 0, k = 0, prev = INF, curr = INF;
    numbers_line.resize(3);
    numbers_line.assign(3, 0);
    line = line + " "; 
   
    for(int i = 0; i < line.length(); i++){
       
        if((int) line[i] == 32){
            
            if(curr == INF){ // caso o número seja de apenas 1 dígito
                numbers_line[j] = prev;
                j++; k = 0; prev = INF; curr = INF;
                
            }
            //não sendo: 
            else{
            numbers_line[j] = concatNumber(prev, curr); //encontrou um número > 9
            j++; k=0; prev = INF, curr = INF;
            
            }
            
        }
        else if(k == 0){

            if((int) line[i] == 45  && j==2){ // encontou um peso negativo.

                if((int) line[i+2] != 32){ // peso negativo de 2 casas
                    prev = ((int)line[i+1]-48);
                    curr = ((int)line[i+2]-48);
                    numbers_line[j] = - concatNumber(prev, curr);
                    j++; k=0; prev = INF, curr = INF;
                    i+=3;
                    

                }
                else if((int) line[i+2] == 32){ // peso negativo de 1 casa
                   
                    prev = -((int)line[i+1] - 48);
                    // cout << "PESO NEGATIVO 1 CASA: " << prev << "| line[ " << i+1 << " ] = " << (int) line[i+1] << "| (" << (int) line[i+1]-48 << ")\n";
                    numbers_line[j] = prev;
                    j++; k=0; curr = INF;
                    i++;
                }
            }
            else{
                prev = (int) line[i] - 48;
                k++;
            }
            
            
        }
        else if(k==1){
            curr = (int) line[i] - 48; // nesse caso não existe número negativo
            
        }
    } 
    return;
}

void read_v_e( string line){
    int space, i = -1;
    int curr = 0, prev = 0;

    aux_v = (int) line[0]-48;
    aux_e = (int) line[2]-48;
    return;
}




void read(int v1, int v2, int w){
    v1--; v2--;
    
    adj[v1].push_back({v2, w});
    adj[v2].push_back({v1, w});

    // for(int i = 0; i < nEdges; i++){
    //     // cout << "i = " << i << "\n";
    //     // cin >> v1 >> v2 >> w;
    //     v1--; v2--;
    //     adj[v1].push_back({v2, w});
    //     adj[v2].push_back({v1, w});


    // }
    return;
}

void dijkstra(int root){

       for(int i=0; i < nVertices; i++){ 
        dist[i] = INF; // assign dist vector with INF value
        visited[i] = false; // assign visited vector with false value
   }
    dist[root] = 0;    


    int currVertice, currDistance;
    
    //creating a min-heap priority queue to the smallest element get the highest priority.
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({0,root}); //root {edge Weight, vertice} 

    while(!pq.empty()){
        currVertice = pq.top().second;
        pq.pop();

        if(visited[currVertice]) continue;
        visited[currVertice] = true;
        for(auto e: adj[currVertice]){
            int v = e.first; int w = e.second;
            if(dist[v] > dist[currVertice] + w){
                dist[v] = dist[currVertice] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return;
}

void show(bool write_file, bool print_individual, int end){

        if(write_file){
            if(print_individual){
                fileOut << "Menor distancia: " << dist[end];
            }
            else{
                fileOut << "Menor distancia:  \n"; 
                for(int i = 0; i < nVertices; i++){
                    fileOut << i+1 << " : " << dist[i] << '\n';
                }
            }
        }
        else if(!write_file){
             if(print_individual){
                 cout << "Menor distancia: " << dist[end];
            }
            else{
                cout << "Menor distancia:  \n"; 
                for(int i = 0; i < nVertices; i++){
                    cout << i+1 << " : " << dist[i] << '\n';
                }
            }
        }

    return;
}

int main(int argc, char **argv){

  bool flag_outFile = false, flag_print_individual = false, flag_write_in_file = false, flag_solution = false;
  int root = 1, end = 0;
  string nameFileOut, nameFileIn;
  nameFileIn = " ";
  for(int i=1; i < argc; i++){ //starting from i=1 to skip the file path that's archived in argv[0]
        
       
        string currArg = argv[i];
        
        if(currArg.compare("-h") == 0){

            //Help Options
            cout << "-h : mostra o help\n";
            cout << "-o <arquivo> : redireciona a saida para o 'arquivo' \n";
            cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada \n";
            cout << "-s : mostra a solucao (em ordem crescente)\n";
            cout << "-i : vertice inicial (dependendo do algoritmo)\n";
            cout << "-l : vertice final (dependendo do algoritmo)\n";
        }

        if (currArg.compare("-o") == 0){
            
            nameFileOut = argv[i+1];
            fileOut.open(nameFileOut);
            flag_outFile = true;
            i++;
        }

        if(currArg.compare("-f") == 0){
             nameFileIn = argv[i+1]; 
            inFile.open(nameFileIn);
           
            if(inFile.is_open()){
                int i = 0;
                while (getline(inFile, line_file))
                {
                    
                    if(i==0){ //reading number of vertices and edges
                        read_v_e(line_file);
                        nVertices = aux_v;
                        nEdges = aux_e;
                        //debug
                        // cout << "( " << nVertices << ", " << nEdges << " )\n";
                        adj.resize(nVertices);
                        visited.resize(nVertices);
                        dist.resize(nVertices);

                    }
                    else{
                        linesReader(line_file);
                        read(numbers_line[0], numbers_line[1], numbers_line[2]);
                        //debug
                        // cout << "( " << numbers_line[0] << ") "<< "";  
                        // cout << "( " << numbers_line[1] << ") "<< "";  
                        // cout << "( " << numbers_line[2] << ") "<< "\n";  
                    }
                    i++;
                }
            } 
            else{ 
                cout<< "Não foi possível abrir o arquivo.";
            }
            i++;
        }

        if(currArg.compare("-s") == 0){
            flag_solution = true;
        }
        if(currArg.compare("-i") == 0){
            
            string aux;
            aux =  argv[i+1];
            root = stoi(aux);
            i++;
        }
        if(currArg.compare("-l") == 0){
            
            flag_print_individual = true;
            string aux;
            aux =  argv[i+1];
            end = stoi(aux);
            i++;
        }
    }
    if(nameFileIn == " "){
        cout << "| ERRO 001 (arquivo de entrada faltante): \n";
        cout << "| Voce precisa indicar o arquivo de entrada no qual esta contido o grafo a ser executado! \n| Por favor, execute novamente com o comando -f <arquivo> para que o algoritmo possa ser executado corretamente.\n| Ou acesse a central de ajuda com o comando -h\n";
    }
    else{
        dijkstra(root-1);
        inFile.close();
        
    }

    if(flag_outFile){
        show(true, flag_print_individual, end-1);
        cout << "| Arquivo <" << nameFileOut <<"> gerado com sucesso!";
        fileOut.close();
    }else if(flag_solution){
        show(false,flag_print_individual,end-1);
    }
    else{
        show(false, flag_print_individual, end-1);
    }

return 0;
}



