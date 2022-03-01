#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include "../readFile.h"
#include "../mainArgs.h"
#include <iostream>

using namespace std;

string line_file;
vector<vector<pair<int, int>>> adjList;
vector<int> bestDistance;
vector<bool> verticesVisited;
int v, e;

void showAllEdges() {
    for(int i = 0; i < v; i++) {
        for(int j = 0; j < adjList[i].size(); j++) {
            cout << i << " " << adjList[i][j].first << " " << adjList[i][j].second << endl;
        }
    }
}

void show(bool write_file, bool print_individual, int end) {
    int sum = 0;
    if(write_file){
        for(int i = 0; i < v; i++) {

            sum+=bestDistance[i];
        }
        if(print_individual){
            showAllEdges();
        }
        else{
            fileOut << "AGM: " <<sum << "\n"; 
            // cout << "Vertice: " << i+1 << " | Distance: " << bestDistance[i] << endl;
        }
    }
    else if(!write_file){
    
        for(int i = 0; i < v; i++) {

            sum+=bestDistance[i];
        }
        if(print_individual){
            showAllEdges();
        }
        else{
            cout << "AGM: " <<sum << "\n"; 
            // cout << "Vertice: " << i+1 << " | Distance: " << bestDistance[i] << endl;
        }
    }

    // for(int i = 0; i < v; i++) {
    //     cout << "Vertice: " << i << " | Distance: " << bestDistance[i] << endl;
    // }

    return;
}

void readEdges(int v1, int v2, int w) {
    v1--; v2--;
    adjList[v1].push_back(make_pair(v2, w));
    adjList[v2].push_back(make_pair(v1, w));
    return;
}

void prim(int root) {
    int currentVertice, currentDistance;
    pair<int, int> head;

    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    pq.push(make_pair(0, root)); 

    while(pq.size() > 0) {
        head = pq.top();
        currentVertice = head.second;
        currentDistance = head.first;        
        pq.pop();

        if(verticesVisited[currentVertice] == false) {
            verticesVisited[currentVertice] = true; 
            bestDistance[currentVertice] = currentDistance; 

            for(int i = 0; i < adjList[currentVertice].size(); i++) {
                pq.push(make_pair(adjList[currentVertice][i].second, adjList[currentVertice][i].first));
            }
        }
    }
    
    return;
}

int main(int argc, char **argv) {

    int root = 1, end = 0;
    bool flag_outFile = false, flag_print_individual = false, flag_write_in_file = false, flag_solution = false, flag_inFile = false;
    nameFileIn = " ";

    for(int i = 1; i < argc; i++){
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
                    verticesVisited.resize(v);
                    bestDistance.resize(v);
                    for(int i = 0; i < v; i++) {
                        bestDistance[i] = INF;
                        verticesVisited[i] = false;
                    }
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

    }

    if(nameFileIn == " " && flag_inFile == true ){
        error_001();
    }
    else{
        prim(root-1);
        inFile.close();
    }
    if(flag_outFile){
        show(true, flag_print_individual, end-1);
        cout << "| Arquivo <" << nameFileOut <<"> gerado com sucesso!";

    }
    if(flag_solution){
        show(false,flag_solution,end-1);
        showAllEdges();
    }
    fileOut.close();
     return 0;

}

