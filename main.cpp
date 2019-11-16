#include "KDTreeRange.hpp"
#include "numeros.hpp"
#include<iostream>



using namespace KDTreeRange;

void read_record();
int main(){
   

    //Se inicializa el arbol con 3 dimensiones.
    KDTree<3>* arbolito = new KDTree<3>();
    //return 0;
    

    
    for(int i = 0 ; i<MAX_NUM ; i++)
        arbolito->insertar(numeros[i]);
    
    std::cout << "Profundidad: " << arbolito->profundidad() << std::endl;;
    

    //Pasa por todos los puntos insertados e imprime si hay alguno que no se encuentre.
    for(int i=MAX_NUM-1 ; i>=0 ; i--){
        Punto<3>* pto = arbolito->buscar(numeros[i]);

        if(!pto)
            std::cout << "Not Found (" << (numeros[i][0]) << ", " << (numeros[i][1]) << ", " << (numeros[i][2]) << ")" << std::endl;
    }

    cout << arbolito->profundidad() << endl;

    //return 0;
    cout << "Se prueba buscar algo que no existe" << endl << "\t";
    float testing[] = {3,3,3};
    Punto<3>* pto = arbolito->buscar(testing);
    
    std::cout << ((pto)? "\tFound":"\tNot Found") << std::endl;

    std::cout << "\nEl arbol: " << std::endl;;

    arbolito->mostrarArbol();

    cout << "Ahora se procede a eliminar el punto " << numeros[3][0] << ", "<< numeros[3][1] << ", " << numeros[3][2] << endl;
    arbolito->eliminar(numeros[3]);
    cout << "Supuestamente se elimino" << endl;

    cout << "Ahora se procede a buscar el punto" << numeros[3][0] << ", "<< numeros[3][1] << ", " << numeros[3][2] << endl;
    pto = arbolito->buscar(numeros[3]);
    std::cout << ((pto)? "Found":"Not Found") << std::endl;

    cout << "Ahora se procede a buscar el punto" << numeros[7][0] << ", "<< numeros[7][1] << ", " << numeros[7][2] << endl;
    pto = arbolito->buscar(numeros[7]);
    std::cout << ((pto)? "Found":"Not Found") << std::endl;

    arbolito->mostrarArbol();

   
    arbolito = nullptr;

    return 0;
        
}


