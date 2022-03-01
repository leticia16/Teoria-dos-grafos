#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <string>
using namespace std;
const int INF = 1e9;

ofstream fileOut;
ifstream inFile;
string line;

vector <int> numbers_line;
int aux_v, aux_e;

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


#endif