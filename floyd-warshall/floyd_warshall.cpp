#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include "../readFile.h"
#include "../mainArgs.h"
#include <iostream>

using namespace std;

string line_file;

int v, e;
vector<vector<int>> adjMatrix;


void show(bool write_file) {
    if(write_file){
        for(int i = 0; i < v; i++) {
		for(int j = 0; j < v; j++) {
			fileOut << "Distancia de " << i << " para " << j << " is ";
            if(adjMatrix[i][j] != INF) {
                fileOut << adjMatrix[i][j] << endl;   
            }
            else {
                fileOut << "INF" << endl;   
            }
		}
	}
    }
    else if(! write_file){
    
        for(int i = 0; i < v; i++) {
            for(int j = 0; j < v; j++) {
                cout << "Distancia de " << i << " para " << j << " is ";
                if(adjMatrix[i][j] != INF) {
                    cout << adjMatrix[i][j] << endl;   
                }
                else {
                    cout << "INF" << endl;   
                }
            }
        }

    }
}

void initializeMatrix() {
    adjMatrix.resize(v);
	for(int i = 0; i < v; i++) {
        adjMatrix[i].resize(v);
		for(int j = 0; j < v; j++) {
            (i == j) ? adjMatrix[i][j] = 0 : adjMatrix[i][j] = INF;
		}
	}
}

void readEdges(int v1, int v2, int w) {
    v1--, v2--;
    adjMatrix[v1][v2] = w;
}

void floydWarshall() {
	for(int k = 0; k < v; k++) {
		for(int i = 0; i < v; i++) {
			for(int j = 0; j < v; j++) {
				if(adjMatrix[k][j] != INF && adjMatrix[j][k] != INF && adjMatrix[i][k] != INF && adjMatrix[k][i] != INF) {
					adjMatrix[i][j] = min(adjMatrix[i][j], 0);
				}
				else if(adjMatrix[k][j] != INF && adjMatrix[j][k] != INF) {
					adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + 0);
				}
				else if(adjMatrix[i][k] != INF && adjMatrix[k][i] != INF) {
					adjMatrix[i][j] = min(adjMatrix[i][j], 0 + adjMatrix[k][j]);
				}
				else {
					adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
				}
			}
		}
	}	
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
                        initializeMatrix();
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
            
            cout << "Essa opcao nao esta disponivel para esse algoritmo \n";
        }
        if(currArg.compare("-l") == 0){
            
            cout << "Essa opcao nao esta disponivel para esse algoritmo \n";
        }
    }

    if(nameFileIn == " " && flag_inFile == true ){
        error_001();
    }
    else{
        floydWarshall();
        inFile.close();
    }

    if(flag_outFile){
        show(true);
        cout << "| Arquivo <" << nameFileOut <<"> gerado com sucesso!";
        fileOut.close();
    }
    else if(flag_solution){
        show(false);
        
    }

    // cin >> v >> e;
    // initializeMatrix();
    // readEdges();
    // floydWarshall();
    
    
	return 0;
}