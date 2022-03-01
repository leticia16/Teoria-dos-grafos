#ifndef MAINARGS_H
#define MAINARGS_H

#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <string>


 bool flag_outFile = false, flag_print_individual = false, flag_write_in_file = false, flag_solution = false, flag_inFile = false;
// int root = 1;
// int end = 0;
string nameFileOut, nameFileIn;


void error_001(){
    cout << "| ERRO 001 (arquivo de entrada faltante): \n";
    cout << "| Voce precisa indicar o arquivo de entrada no qual esta contido o grafo a ser executado! \n| Por favor, execute novamente com o comando -f <arquivo> para que o algoritmo possa ser executado corretamente.\n| Ou acesse a central de ajuda com o comando -h\n";
    return;
}

void showHelpOptions(){

    cout << "-h : mostra o help\n";
    cout << "-o <arquivo> : redireciona a saida para o 'arquivo' \n";
    cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada \n";
    cout << "-s : mostra a solucao (em ordem crescente)\n";
    cout << "-i : vertice inicial (dependendo do algoritmo)\n";
    cout << "-l : vertice final (dependendo do algoritmo)\n";

    return;
}

#endif 