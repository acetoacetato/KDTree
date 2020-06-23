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

//Librerías propias
#include "KDTreeRange.hpp"
#include "KDTree.hpp"
#include "vars.hpp"
#include "csvRow.hpp"


using namespace std;

int main(int argc, char* argv[]){

    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    KDTree::Node<DIM>* raiz = nullptr;
    std::ofstream salida;
    salida.open("salida.txt", std::ios::app);
    //KDTreeRange::KDTreeR<3>* arbolito = new KDTreeRange::KDTreeR<3>();
    
    for(int i=0 ; i<MAX_NUM ; i++){
        auto punto = (*numeros)[i];
        //arbolito->insertar(*punto);
        raiz = KDTree::insertar<DIM>(*punto, raiz);
    }
    auto start = std::chrono::high_resolution_clock::now();

    for(int i=0 ; i<MAX_NUM ; i++){
        auto punto = (*numeros)[i];
        raiz->buscar(*punto);
        //arbolito->buscar(*punto);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    //cout << "\ttiempo insercion: " << milisegundos << endl;
    //salida << milisegundos << endl;

    salida << raiz->profundidad << endl;

    return 0;
}
