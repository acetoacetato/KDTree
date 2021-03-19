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

void original(string, string,int);
void nuevo(string, string, int);

void nuevo2(string, string, int);

int main(int argc,const char* argv[]){

    int vecinos = 1;
 
    if(strcmp(argv[1], "nuevo") == 0){
        cout << "Se inicia el nuevo";
        string uno, dos;
        uno = argv[2];
        dos = argv[3];
        nuevo(uno, dos, vecinos);

        nuevo2(uno, dos, vecinos);
    }  
    else if(strcmp(argv[1], "antiguo") == 0){
        string uno, dos;
        uno = argv[2];
        dos = argv[3];
        original(uno, dos, vecinos);
    }
        
    return 0;
}


void original(string uno, string dos, int v){
    cout << "inicia original" << endl;
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    std::vector<std::vector<float>*>* eliminar = csv::cargaNumeros("elim.csv");
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
    for(int i=0;i<500000; i++){
        auto punto = (*eliminar)[i];
        raiz->eliminar(*punto);
    }
    auto ultimoPunto = (*numeros)[(int)(MAX_NUM)-1]; 
    auto start = std::chrono::high_resolution_clock::now();
    
    int nodos = KDTree::knn(*ultimoPunto,v,raiz);
    //raiz->knn(*ultimoPunto,5); 

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
    

void nuevo(string uno, string dos,int v){
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    std::vector<std::vector<float>*>* eliminar = csv::cargaNumeros("elim.csv");
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
        //puntos.push_back(*punto);
    }
    for(int i=0;i<500000; i++){
        auto punto = (*eliminar)[i];
        arbolito->eliminar(*punto);
    }
    auto ultimoPunto = (*numeros)[(int)(MAX_NUM)-1];
    auto start = std::chrono::high_resolution_clock::now();
    int nodos = arbolito->vecinosMasCercano(*ultimoPunto,v,false);
    auto finish = std::chrono::high_resolution_clock::now();

    arbolito->toJson();
    /*
    ofstream resultados;

    resultados.open("resultadosFB.txt");

    reff=*ultimoPunto;
    puntos.sort(closer_than);
    cout << "---------------------------------------------" << endl;

    cout << "Fuerza bruta" << endl;
    int i=0;
    for(auto p : puntos){
            i++; if(i>50) break;
            for(int j = 0; j < DIM; j++){
                resultados << p[j] << " ";
            }
            resultados << "distancia = " <<  distance(p,reff) << " \n";
       }
    resultados.close();
    */
    
    
   
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    salida << milisegundos << ";" << nodos << ";\n";

    
}   


void nuevo2(string uno, string dos,int v){
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    std::vector<std::vector<float>*>* eliminar = csv::cargaNumeros("elim.csv");
    std::ofstream salida;
    char inicial[] = "";
    if(uno == "insertados"){
        cout << "insertados" << endl;
        
        salida.open("SalidaNuevo" + dos + ".csv", std::ios::app);
    } else{
        salida.open("SalidaNuevoN" + dos + ".csv", std::ios::app);
    }
    KDTreeRange2::KDTreeR2<DIM>* arbolito = new KDTreeRange2::KDTreeR2<DIM>();

    list<std::vector<float>> puntos;

    for(int i=0 ; i<((int)(MAX_NUM)-1) ; i++){
        auto punto = (*numeros)[i];
        arbolito->insertar(*punto);
        //puntos.push_back(*punto);
    }
    for(int i=0;i<500000; i++){
        auto punto = (*eliminar)[i];
        arbolito->eliminar(*punto);
    }
    auto ultimoPunto = (*numeros)[(int)(MAX_NUM)-1];
    auto start = std::chrono::high_resolution_clock::now();
    int nodos = arbolito->vecinosMasCercano(*ultimoPunto,v,true);
    auto finish = std::chrono::high_resolution_clock::now();

    arbolito->toJson();
    /*
    ofstream resultados;

    resultados.open("resultadosFB.txt");

    reff=*ultimoPunto;
    puntos.sort(closer_than);
    cout << "---------------------------------------------" << endl;

    cout << "Fuerza bruta" << endl;
    int i=0;
    for(auto p : puntos){
            i++; if(i>50) break;
            for(int j = 0; j < DIM; j++){
                resultados << p[j] << " ";
            }
            resultados << "distancia = " <<  distance(p,reff) << " \n";
       }
    resultados.close();
    */
    
    
   
    auto elapsed = finish - start;
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(finish - start).count();

    salida << milisegundos << ";" << nodos << ";\n";

    
}   