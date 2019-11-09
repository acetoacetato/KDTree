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
   

    //Se inicializa el arbol con 3 dimensiones.
    KDTree<3>* arbolito = new KDTree<3>();
    //return 0;
    

    
    for(int i = 0 ; i<15 ; i++)
        arbolito->insertar(puntos[i]);
    
    std::cout << "Profundidad: " << arbolito->profundidad() << std::endl;;
    

    for(int i=14 ; i>=0 ; i--){
        cout << "Se busca: (" << puntos[i][0] << ", " << puntos[i][1] << ", " << puntos[i][2] << ")" << endl;
        Punto<3>* pto = arbolito->buscar(puntos[i]);

        if(pto)
            std::cout << "Encontrado!" << std::endl;
        else
            std::cout << "Not Found" << std::endl;
    }
    float testing[] = {3,3,3};
    Punto<3>* pto = arbolito->buscar(testing);
    
    std::cout << ((pto)? "Found":"Not Found") << std::endl;

    std::cout << "\nEl arbol: " << std::endl;;

    arbolito->mostrarArbol();

}