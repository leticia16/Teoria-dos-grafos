#include <bits/stdc++.h>
// #define INF 1000000
#include <string>
#include <fstream>
#include "../readFile.h"
#include "../mainArgs.h"
#include <iostream>

using namespace std;

string line_file;
vector<vector<pair<int, int>>> adjList;
vector<int> bestDistance;
int v, e;

void showAllEdges() {
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < adjList[i].size(); j++) {
            cout << i << " " << adjList[i][j].first << " " << adjList[i][j].second << endl;
        }
    }
}

void show(bool write_file, bool print_individual, int end) {

    if(write_file){
       if(print_individual){
             fileOut << "Vertice: " << end+1 << " | Distancia partindo da raiz: " << bestDistance[end] << endl;
           
       } 
       else{
           for(int i = 0; i < v; i++) {
                fileOut <<  "Vertice: " << i+1 << " | Distance from root: " << bestDistance[i] << endl;
           }
       }
    }

    else if(!write_file){
        if(print_individual){
                cout << "Vertice: " << end+1 << " | Distancia partindo da raiz: " << bestDistance[end] << endl;
            
        } 
        else{
            for(int i = 0; i < v; i++) {
                cout <<  "Vertice: " << i+1 << " | Distancia partindo da raiz: " << bestDistance[i] << endl;
            }
        }
}
    // showAllEdges();
    return;
}

void readEdges(int v1, int v2, int w) {
    
    v1--; v2--;
    adjList[v1].push_back({v2, w});

    return;
}

void bellmanFord() {
    int nextVertice, edgeDistance, currentDistance;

    for(int i = 0; i < v - 1; i++) {    
        for(int index = 0; index < adjList.size(); index++) {
            for(auto neighbor: adjList[index]) {
                nextVertice = neighbor.first;
                edgeDistance = neighbor.second;       
                currentDistance = bestDistance[index] + edgeDistance;

                if(currentDistance < bestDistance[nextVertice]) {
                    bestDistance[nextVertice] = currentDistance; // setting the best distance to this vertice
                } 
            }
        }
    }

    for(int index = 0; index < adjList.size(); index++) {
        for(auto neighbor: adjList[index]) {
            nextVertice = neighbor.first;
            edgeDistance = neighbor.second;       
            currentDistance = bestDistance[index] + edgeDistance;

            if(currentDistance < bestDistance[nextVertice]) {
                bestDistance[nextVertice] = -INF; // negative cycle
                cout << "Found a negative cycle" << endl;
            } 
        }
    }
    
    return;
}

int main(int argc, char **argv) {

    int root = 1, end = 0;
    bool flag_outFile = false, flag_print_individual = false, flag_write_in_file = false, flag_solution = false, flag_inFile = false;
    nameFileIn = " ";

    for(int i = 1; i < argc; i++){ //starting from i=1 to skip the file path that's archived in argv[0]
        
        string currArg = argv[i];
        
        if(currArg.compare("-h") == 0){
            showHelpOptions();
        }
        if(currArg.compare("-o") == 0){
            
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
            while (getline(inFile, line_file)){
                if(i==0){
                    read_v_e(line_file);
                    v = aux_v;
                    e = aux_e;
                    adjList.resize(v);
                    bestDistance.assign(v,INF);
                    bestDistance[0] = 0;
                    // bestDistance.resize(v);
                }
                else{
                    linesReader(line_file);
                    readEdges(numbers_line[0], numbers_line[1], numbers_line[2]);
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
            bestDistance[root] = 0;
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
        bellmanFord();
        inFile.close();
    }

    //Results
    if(flag_outFile){
        show(true, flag_print_individual, end-1);
        cout << "| Arquivo <" << nameFileOut <<"> gerado com sucesso!";
        fileOut.close();
    }
    else if(flag_solution){
        show(false,flag_print_individual,end-1);
        showAllEdges();
    }
    return 0;
}