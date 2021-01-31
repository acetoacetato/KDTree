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
    for(int i=0 ; i<((int)(MAX_NUM)-1) ; i++){
        auto punto = (*numeros)[i];
        //arbolito->insertar(*punto);
        raiz = KDTree::insertar<DIM>(*punto, raiz);
    }
    auto ultimoPunto = (*numeros)[(int)(MAX_NUM)-1];
    auto start = std::chrono::high_resolution_clock::now();
    
    int nodos = raiz->knn(*ultimoPunto,1);

    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    auto milisegundosI = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    //salida << milisegundos << endl;
    salida << milisegundosI << ";"  << nodos << ";\n";
    



    
    
}

vector<float> reff;

double distance(vector<float>& v1, vector<float>&v2){
      double dist= 0.0;
      double calc;
      for(int i=0;i<v1.size();i++){
        calc = v1[i]-v2[i];
        dist = dist + calc * calc;
      }
      return sqrt(dist);
}

bool closer_than(vector<float>& lhs, vector<float>&  rhs) {
            return distance(lhs,reff) < distance(rhs,reff);
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
    KDTreeRange2::KDTreeR2<DIM>* arbolito = new KDTreeRange2::KDTreeR2<DIM>();

    list<std::vector<float>> puntos;

    for(int i=0 ; i<((int)(MAX_NUM)-1) ; i++){
        auto punto = (*numeros)[i];
        arbolito->insertar(*punto);
        puntos.push_back(*punto);
    }
    auto ultimoPunto = (*numeros)[(int)(MAX_NUM)-1];
    auto start = std::chrono::high_resolution_clock::now();
    int nodos = arbolito->vecinosMasCercano(*ultimoPunto,5);

    reff=*ultimoPunto;
    puntos.sort(closer_than);

    cout << "Fuerza bruta" << endl;
    int i=0;
    for(auto p : puntos){
            i++; if(i>5) break;
            for(int j = 0; j < DIM; j++){
                cout << p[j] << " ";
            }
            cout << "distancia = " <<  distance(p,reff) << " \n";
       }
    
    
    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    salida << milisegundos << ";" << nodos << ";\n";

    
}   