#include<iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv){

 string nameFileOut;
  for(int i=1; i < argc; i++){ //starting from i=1 to skip the file path that's archived in argv[0]
        
       
        string currArg = argv[i];

        //Debug
        cout << "iteração [ " << i << " ] = " << argv[i] << "| "<< currArg << "\n";
        
        if(currArg.compare("-h") == 0){

            //debug
            cout << "ENTRANDO EM -h| [ " << argv[i] << " ] = "<<"We have a -h argument\n";

            //Help Options
            cout << "-h : mostra o help\n";
            cout << "-o <arquivo> : redireciona a saida para o 'arquivo' \n";
            cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada \n";
            cout << "-s : mostra a solucao (em ordem crescente)\n";
            cout << "-i : vertice inicial (dependendo do algoritmo)\n";
            cout << "-l : vertice final (dependendo do algoritmo)\n";
        }

        if (currArg.compare("-o") == 0){
            cout << "-> [ "<< argv[i] << " ] = "<<"We have a -o argument\n";
            nameFileOut = argv[i+1];
            cout << "Name File out: " << nameFileOut << "\n";
            i++;
        }

    }

    return 0;
}