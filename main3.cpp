//Librerías de c
//#include <stdlib.h>
//#include <time.h>
//#include <stdio.h>
//#include <unistd.h>
//Librerías de c++
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include<algorithm>
#include<chrono>
#include<cstring>
//Librerías propias
#include "KDTreeRange2.hpp"
#include "KDTree.hpp"
#include "vars.hpp"
#include "csvRow.hpp"


using namespace std;

void original(string, string);
void nuevo(string, string);

int main(int argc,const char* argv[]){
 
    if(strcmp(argv[1], "nuevo") == 0){
        cout << "Se inicia el nuevo";
        string uno, dos;
        uno = argv[2];
        dos = argv[3];
        nuevo(uno, dos);
    }  
    else if(strcmp(argv[1], "antiguo") == 0){
        string uno, dos;
        uno = argv[2];
        dos = argv[3];
        original(uno, dos);
    }
        
    return 0;
}


void original(string uno, string dos){
    cout << "inicia original" << endl;
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    KDTree::Node<DIM>* raiz = nullptr;
    std::ofstream salida;

    if(uno == "insertados"){
        cout << "insertados" << endl;
        
        salida.open("SalidaOriginalI" + dos + ".csv", std::ios::app);
    } else{
        salida.open("SalidaOriginalNI" + dos + ".csv", std::ios::app);
    }
    //KDTreeRange2::KDTreeR2<3>* arbolito = new KDTreeRange2::KDTreeR2<3>();
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0 ; i<((int)(MAX_NUM)) ; i++){
        auto punto = (*numeros)[i];
        //arbolito->insertar(*punto);
        raiz = KDTree::insertar<DIM>(*punto, raiz);
    }
    
    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    //salida << milisegundos << endl;
    salida << milisegundos << ";"  << raiz->profundidad << ";";
    



    int inicio, final;
    if(dos == "insertados"){
        inicio = 0;
        final = MAX_NUM/2;
    } else{
        inicio = MAX_NUM/2;
        final = MAX_NUM;
    }

    int prom = 0;
    int min = 1000000;
    int max = -10;
    for(int i=0 ; i<MAX_NUM ; i++){
        auto punto = (*numeros)[i];
        int recorridos = raiz->buscar(*punto);
        prom += recorridos;
        if(max < recorridos){
            max = recorridos;
        }
        if(min > recorridos){
            min = recorridos;
        }
        //arbolito->buscar(*punto);
    }

    salida << prom/MAX_NUM << ";" << max << ";" << endl;
    
}

void nuevo(string uno, string dos){
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    std::ofstream salida;
    char inicial[] = "";
    if(uno == "insertados"){
        cout << "insertados" << endl;
        
        salida.open("SalidaNuevoI" + dos + ".csv", std::ios::app);
    } else{
        salida.open("SalidaNuevoNI" + dos + ".csv", std::ios::app);
    }
    KDTreeRange2::KDTreeR2<3>* arbolito = new KDTreeRange2::KDTreeR2<3>();
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0 ; i<((int)(MAX_NUM)) ; i++){
        auto punto = (*numeros)[i];
        arbolito->insertar(*punto);
    }
    
    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    salida << milisegundos << ";" << arbolito->profundidad() + 1 << ";";




    int prom =0;
    int min = 1000000;
    int max = -10;
    for(int i=0 ; i<MAX_NUM ; i++){
        auto punto = (*numeros)[i];
        int cantidad = arbolito->buscar(*punto);
        prom+= cantidad;
        if(max < cantidad){
            max = cantidad;
        }
        if(min > cantidad){
            min = cantidad;
        }
    }

    
    //salida << prom/MAX_NUM << endl;
    salida << prom/MAX_NUM << ";" << max << ";" << endl;
    
}   