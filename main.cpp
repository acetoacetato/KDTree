#include "KDTreeRange.hpp"
#include "KDTree.hpp"
#include<iostream>
#include<chrono>
#include <string>

//Librerias de c
#include <stdlib.h>
#include <time.h>


using namespace KDTreeRange;
using namespace std;

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




int main(int argc, char** argv){
    srand(time(NULL));    
    int MAX_NUM = (argc > 1)? atoi(argv[1]):1000;

    cout << MAX_NUM << endl;
    std::vector<float> numerillo = generaPunto(3);
    std::vector<std::vector<float>> numeros;
    numeros.push_back(numerillo);
    
    std::ofstream fileAntiguo, fileNuevo;
    fileAntiguo.open("Antiguo.txt", std::ios_base::app);
    fileNuevo.open("Nuevo.txt", std::ios_base::app);

    fileAntiguo << "Cantidad: " << MAX_NUM << endl;
    fileNuevo << "Cantidad: " << MAX_NUM << endl;

    //Se inicializa el arbol con 3 dimensiones.
    KDTreeR<3>* arbolito = new KDTreeR<3>();
    //return 0;
    KDTree::Node<3>* arbolNormal = KDTree::insertar<3>(numerillo);
    //Para que partan en igual de condiciones.
    arbolito->insertar(numerillo);
    
    
    

    for(long int i = 1 ; i<MAX_NUM ; i++){
        numerillo = generaPunto(3);
        numeros.push_back(numerillo);
        arbolito->insertar(numerillo);
        arbolNormal->insertar(numerillo);
    }
        
        
    cout << "Termina de insertar, ahora comienza a buscar" << endl;


    

    //Pasa por todos los puntos insertados e imprime si hay alguno que no se encuentre.
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=MAX_NUM-1 ; i>=0 ; i--){
        Punto<3>* pto = arbolito->buscar(numeros[i]);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;

    fileNuevo << "\ttiempo búsqueda: " << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << endl;

    start = std::chrono::high_resolution_clock::now();
    for(int i=MAX_NUM-1 ; i>=0 ; i--){
        arbolNormal->buscar(numeros[i]);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = start - finish;
    fileAntiguo << "\ttiempo búsqueda: " << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << endl;

    //cout << arbolito->profundidad() << endl;
    //arbolito->mostrarArbol();
    //arbolito->toJson();

    std::cout << "Profundidad del nuevo: " << arbolito->profundidad() << std::endl;;
    std::cout << "Profundidad del antiguo: " << arbolNormal->profundidad << std::endl;;
    cout << "aaa"<< endl;
    
    int numerote = rand() % MAX_NUM;
    cout << "aaa"<< endl;
    list<Node<3>*> l = arbolito->puntosNoDominados(numeros[numerote]);

    cout << "aaa"<< endl;
    Punto<3>* p = arbolito->buscar(numeros[numerote]);

    //cout << "No nominados por ";
    //p->imprimePunto();
    //cout << endl;
    //for(auto nodo : l){
    //    cout << nodo->strPunto() << endl;
    //}

    arbolito->toJson();

    return 0;
        
}


