#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "../readFile.h"
#include "../mainArgs.h"

typedef pair<int, int> ii;

string line_file;
int nVertices, nEdges;

vector<vector<ii>> adj;
vector<int> dist;
vector<bool> visited;

void read(int v1, int v2, int w){
    v1--; v2--;
    
    adj[v1].push_back({v2, w});
    adj[v2].push_back({v1, w});
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

//   bool flag_outFile = false, flag_print_individual = false, flag_write_in_file = false, flag_solution = false, flag_inFile = false;
  int root = 1, end = 0;
//   string nameFileOut, nameFileIn;
  nameFileIn = " ";
  for(int i=1; i < argc; i++){ //starting from i=1 to skip the file path that's archived in argv[0]
        
       
        string currArg = argv[i];
        
        if(currArg.compare("-h") == 0){
            //Help Options
            showHelpOptions();
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
                        adj.resize(nVertices);
                        visited.resize(nVertices);
                        dist.resize(nVertices);

                    }
                    else{
                        linesReader(line_file);
                        read(numbers_line[0], numbers_line[1], numbers_line[2]);
                    }
                    i++;
                }
            } 
            else{ 
                cout<< "Não foi possível abrir o arquivo.";
            }
            i++;
            flag_inFile = true;
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
    if(nameFileIn == " " && flag_inFile == true ){
        error_001();
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

return 0;
}
