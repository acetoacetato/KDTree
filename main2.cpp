#include "KDTreeRange2.hpp"
#include "KDTreeRange.hpp"
#include "KDTree.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;
using namespace KDTreeRange2;
using namespace KDTreeRange;
const int dimensiones = 2;

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

    //Inicializando templates
    KDTree::nodo<3> nodito;
    KDTree::lex_compare<3> comparador;

    srand(time(NULL));
    std::ofstream file;
    std::ofstream output;
    KDTreeR2<dimensiones>* arbol = new KDTreeR2<dimensiones>();
    KDTree::Node<dimensiones>* raiz = nullptr;
    std::vector<float> punto;
    std::vector<std::vector<float>> numeros;
    int MAX_NUM = (argc > 1)? atoi(argv[1]):10;
    output.open("test.js", std::ios_base::app);
    file.open("thegame.txt", std::ios_base::app);
    file << "\n///////////////////////////////////////////" << endl;
    //numeros = {
    //        {0, 0},
    //        {1, 10},
    //        {-2, -100},
    //        {3, 1000},
    //        {-4, -10000 },
    //        {5, 100000},
    //        {-6, -1000000},
    //        {7, 10000000},
    //        {-8, -100000000},
    //        {9, 1000000000},
    //        {-10, -10000000000},
    //    };
    numeros = {
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4},
            {0, 5},
            {0, 6},
            {0, 7},
            {0, 8},
            {0, 9},
            {0, 10}
    };
//
    cout << "aca" << endl;
    for(int i=0 ; i<MAX_NUM ; i++){
        //punto = generaPunto(dimensiones);
        
        punto = numeros[i];
        file << "{" << punto[0] << ", " << punto[1] << "}," << endl;
        arbol->insertar(punto);
        raiz = KDTree::insertar<dimensiones>(punto, raiz);
        //arbol->toJson();
        //system("pause");
        //numeros.push_back(punto);
        
    }

    //arbol->actualizaDim();
    //arbol->mostrarArbol();
    
    KDTree::toJson<2>(raiz);
    //arbol->eliminar(numeros[0]);
    cout << numeros[0][0] << ", " << numeros[0][1] << endl;
    for(auto num : numeros){
        auto busqueda = arbol->buscar(num);
        if(busqueda == nullptr){
            cout << "1not found (" << num[0] << ", " << num[1] << ", " << num[2] << ")\n"; 
        }
    }

    //arbol->mostrarArbol();
    cout << arbol->profundidad() << endl;
    cout << endl;

    std::list<KDTree::Node<2>*> nNeibourghs = raiz->knn({0,3}, 4);
    for(auto nodo : nNeibourghs){
        cout << nodo->strPunto() << endl;
    }
    return 0;
}