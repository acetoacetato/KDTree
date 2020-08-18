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
const int dimensiones = 3;

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
    int MAX_NUM = (argc > 1)? atoi(argv[1]):1000;
    output.open("test.js", std::ios_base::app);
    file.open("thegame.txt", std::ios_base::app);
    file << "\n///////////////////////////////////////////" << endl;
    
    //numeros = {
    //            {9615, 3673, 8302},
    //            {2825, 118, 353},
    //            {2187, 3721, 6768},
    //            {8826, 2381, 443},
    //            {4221, 1873, 2028},
    //            {5031, 4668, 6717},
    //            {8480, 8584, 6201},
    //            {1910, 128, 2930},
    //            {7447, 4999, 9645},
    //            {952, 8991, 9523},
    //        };
    cout << "aca\n\n\n\n\n\n\n\n\n\naca" << endl;
    for(int i=0 ; i<MAX_NUM ; i++){
        punto = generaPunto(dimensiones);
        
        //punto = numeros[i];
        file << "{" << punto[0] << ", " << punto[1] << ", " << punto[2] << "}," << endl;
        arbol->insertar(punto);
        raiz = KDTree::insertar<dimensiones>(punto, raiz);
        //arbol->toJson();
        //system("pause");
        numeros.push_back(punto);
        
    }

    //arbol->actualizaDim();
    //arbol->mostrarArbol();
    
    //arbol->eliminar(numeros[0]);
    arbol->toJson();
    cout << numeros[0][0] << ", " << numeros[0][1] << endl;
    for(auto num : numeros){
        auto busqueda = arbol->buscar(num);
        if(busqueda == -1){
            cout << "1not found (" << num[0] << ", " << num[1] << ", " << num[2] << ")\n"; 
        }
    }

    //arbol->mostrarArbol();
    //cout << arbol->profundidad() << endl;
    //cout << endl;
//
    //std::list<KDTree::Node<2>*> nNeibourghs = raiz->knn({0,3}, 4);
    //for(auto nodo : nNeibourghs){
    //    cout << nodo->strPunto() << endl;
    //}
    return 0;
}