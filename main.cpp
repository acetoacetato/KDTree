#include "KDTreeRange.hpp"
#include<iostream>
using namespace KDTreeRange;
int main(){
    float puntos[][15] = {
                            {7, 2, 6},
                            {5, 4, 2},
                            {9, 5, 3},
                            {2, 1, 3},
                            {1, 6, 8},
                            {8, 4, 2},
                            {9, 6, 7},
                            {6, 3, 1},
                            {2, 3, 3},
                            {3, 4, 5},
                            {4, 7, 9},
                            {9, 4, 1},
                            {8, 1, 5},
                            {8, 7, 6},
                            {9, 7, 8}
                        };

    

    KDTreeRange::Node* arbolito = KDTreeRange::insertar(puntos[0]);
    for(int i = 1 ; i<15 ; i++)
        arbolito = KDTreeRange::insertar(puntos[i], arbolito);
    
    std::cout << "Profundidad: " << arbolito->profundidad << std::endl;;
    Punto* pto = arbolito->buscar(puntos[9]);
    if(pto)
        std::cout << pto->point[0] << std::endl;
    else
        std::cout << "Not Found" << std::endl;
    

}