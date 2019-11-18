#include "KDTreeRange.hpp"
#include "KDTree.hpp"
#include<iostream>
#include<chrono>

//Librerias de c
#include <stdlib.h>
#include <time.h>


using namespace KDTreeRange;

std::vector<float> generaPunto(int dim){
    
    float num;
    
    std::vector<float> numero;
    for(int i=0 ; i<dim ; i++){
        //Genera un numero aleatorio entre 1 y 10000
        num = rand() % 10000 + 1;
        numero.push_back(num);
    }
    return numero;
} 

int main(){
    srand(time(NULL));    
    int MAX_NUM = 110000;
    std::vector<float> numerillos[MAX_NUM];
    for(long int i=0 ; i<MAX_NUM ; i++){
        std::vector<float> numero = generaPunto(3);
        numerillos[i] = numero;
    }
    

    //Se inicializa el arbol con 3 dimensiones.
    KDTreeR<3>* arbolito = new KDTreeR<3>();
    auto numero = numerillos[0];
    //return 0;
    KDTree::Node<3>* arbolNormal = KDTree::insertar<3>(numerillos[0]);
    //Para que partan en igual de condiciones.
    arbolito->insertar(numerillos[0]);
    

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    for(long int i = 1 ; i<MAX_NUM ; i++)
        arbolito->insertar(numerillos[i]);

    // Record end time
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "tiempo nuevo: " << elapsed.count() << " s\n";
    ////////////////////
    start = std::chrono::high_resolution_clock::now();
    for(long int i = 1 ; i<MAX_NUM ; i++)
        arbolNormal->insertar(numerillos[i]);
    
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "tiempo antiguo: " << elapsed.count() << " s\n";

    //std::cout << "Profundidad: " << arbolito->profundidad() << std::endl;;
    

    //Pasa por todos los puntos insertados e imprime si hay alguno que no se encuentre.
    start = std::chrono::high_resolution_clock::now();
    for(int i=MAX_NUM-1 ; i>=0 ; i--){
        Punto<3>* pto = arbolito->buscar(numerillos[i]);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "tiempo busqueda nuevo: " << elapsed.count() << " s\n";

    start = std::chrono::high_resolution_clock::now();
    for(int i=MAX_NUM-1 ; i>=0 ; i--){
        arbolNormal->buscar(numerillos[i]);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "tiempo busqueda antiguo: " << elapsed.count() << " s\n";

    //cout << arbolito->profundidad() << endl;
    //arbolito->mostrarArbol();
    //arbolito->toJson();

    std::cout << "Profundidad del nuevo: " << arbolito->profundidad() << std::endl;;
    std::cout << "Profundidad del antiguo: " << arbolNormal->profundidad << std::endl;;


    return 0;
        
}


