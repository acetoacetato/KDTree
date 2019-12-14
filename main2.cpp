#include "KDTreeRange2.hpp"
#include "KDTreeRange.hpp"
#include <iostream>
#include <vector>
#include <string>

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

    std::ofstream file;
    KDTreeR2<dimensiones>* arbol = new KDTreeR2<dimensiones>();
    std::vector<float> punto;
    std::vector<std::vector<float>> numeros;
    int MAX_NUM = (argc > 1)? atoi(argv[1]):100;
    
    file.open("thegame.txt", std::ios_base::app);
    file << "\n///////////////////////////////////////////" << endl;
    MAX_NUM = 100;



    for(int i=0 ; i<MAX_NUM ; i++){
        punto = generaPunto(dimensiones);
        file << "{" << punto[0] << ", " << punto[1] << "}," << endl;
        numeros.push_back(punto);
        arbol->insertar(punto);
    }


    //arbol->mostrarArbol();
    //arbol->toJson();
    arbol->eliminar(numeros[0]);
    cout << numeros[0][0] << ", " << numeros[0][1] << endl;
    for(auto num : numeros){
        auto busqueda = arbol->buscar(num);
        if(busqueda == nullptr){
            cout << "1not found (" << num[0] << ", " << num[1] << ", " << num[2] << ")\n"; 
        }
    }

    //arbol->mostrarArbol();
    cout << arbol->profundidad() << endl;
  
    
    

    return 0;
}                                                