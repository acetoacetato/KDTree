#include <iostream>
const int k = 3;

using namespace std;
namespace KDTreeRange{


class Punto{
    public:
        float point [k];

        //Retorna el valor de la n-esima dimensión dado un iterador.
        float getVal(int);
        //Compara los valores en una dimensión dada
        //      -1 si el pto recibido es menor
        //       0 si el pto recibido es igual
        //       1 si el pto recibido es mayor 
        int compareD(float[], int);
        Punto(float []);
};

float Punto::getVal(int dim){
    return point[dim];
}


int Punto::compareD(float punto[], int dimension){
    if(point[dimension] > punto[dimension])
        return -1;
    if(point[dimension] < punto[dimension])
        return 1;
    else
        return 0;
}

Punto::Punto(float puntos[]){
    for(int i=0 ; i<k ; i++)
        point[i] = puntos[i];
}




class Node{
    public:
        Punto *punto;

        //RangoL/R se inicializan al ingresar un nodo en el arbol
        float rangoL[2];
        float rangoR[2];

        int profundidad;
        int dimension;

        //Nodos hijos y el que lo contiene, null si es raíz
        Node *left, *right, *padre;
        //Constructor
        Node(float []);

        void insertar(float []);
        void actualizarProfundidad(Node*);
        Punto* buscar(float []);
        int compareR(float);

};

Node::Node(float puntos[]){

    punto = new Punto(puntos);
    profundidad = 0;
    //Se reinician los nodos hijos
    left = nullptr;
    right = nullptr;
    padre = nullptr;
}

//FIXME: la inserción no está correcta, ni idea de porque
void Node::insertar(float puntos[]){
    cout << "Se inserta: " << puntos[0]  << ", " << puntos[1] << ", " << puntos[2] << endl;
    bool insertado = false;
    int dimension = 0;
    Node *actual = this;
    Node* aux = new Node(puntos);
    while(!insertado){
        cout << "Dimension " << dimension << " [" << actual->rangoL[0] << ", " << actual->rangoL[1] << "] || [" << actual->rangoR[0] << ", " << actual->rangoR[1] << "]"<<endl;
        Punto punto = *actual->punto;
        Node* r = actual->right;
        Node* l = actual->left;

        aux->rangoL[0] = puntos[dimension];
        aux->rangoL[1] = puntos[dimension];
        aux->rangoR[0] = puntos[dimension];
        aux->rangoR[1] = puntos[dimension];

        if(punto.compareD(puntos, dimension) == 0){
            //if(actual->rangoR[0] > puntos[dimension])
            //    actual->rangoR[0] = puntos[dimension];
//
            //if(actual ->rangoR[1] < puntos[dimension])
            //    actual->rangoR[1] = puntos[dimension];

            if(actual->right == nullptr){
                actual->right = aux;
                aux->padre = actual;
                //actual->rangoR[0] = puntos[dimension];
                //actual->rangoR[1] = puntos[dimension];
                cout << "Se inserta en : Der" << endl;
                actualizarProfundidad(aux);
                return;
            }
            actual = actual->right;
            dimension = (dimension + 1) % k;
            continue;
        }
        cout << "\t\t(" << punto.point[0] << ", " << punto.point[1] << ", " << punto.point[2] << ")" << endl;           
        switch(actual->compareR(puntos[dimension])){
            //se deja en el subarbol con menos profundidad
            case 0:
                if(r == nullptr){
                    actual->right = aux;
                    aux->padre = actual;
                    cout << "Se inserta en : Der" << endl;
                    aux->dimension = dimension;
                    actualizarProfundidad(aux);
                    return;
                }
                if(l == nullptr){
                    actual->left = aux;
                    aux->padre = actual;
                    cout << "Se inserta en : Izq" << endl;
                    aux->dimension = dimension;
                    actualizarProfundidad(aux);
                    return;
                }
                
                
                if(r->profundidad > l->profundidad){
                    cout << "Izq [" << actual->rangoL[0] << ", " << actual->rangoL[1]<< "]" << endl;
                    actual = actual->left;
                    
                }
                else{
                    cout << "Der [" << actual->rangoR[0] << ", " << actual->rangoR[1]<< "]" << endl;
                    actual = actual->right;
                }
                
                break;
            //se actualiza limites
            case 2:
                actual->rangoR[1] = puntos[dimension];
                
            //se va a derecha
            case 1:
                if(actual->right == nullptr){
                    actual->right = aux;
                    aux->padre = actual;
                    cout << "Se inserta en : Der" << endl;
                    aux->dimension = dimension;
                    actualizarProfundidad(aux);
                    return;
                }
                cout << "Der [" << actual->rangoR[0] << ", " << actual->rangoR[1]<< "]" << endl;
                actual = actual->right;
                break;
            //se actualiza limites
            case -2:
                actual->rangoL[0] = puntos[dimension];
                
            //se va a la izquierda
            case -1:
                if(actual->left == nullptr){
                    actual->left = aux;
                    aux->padre = actual;
                    aux->dimension = dimension;
                    cout << "Se inserta en : Izq" << endl;
                    actualizarProfundidad(aux);
                    return;
                }
                cout << "Izq [" << actual->rangoL[0] << ", " << actual->rangoL[1]<< "]" << endl;
                actual = actual->left;
                break;
        }

        dimension = (dimension + 1) % k;
    }

}


void Node::actualizarProfundidad(Node* nodo){
    int contador = 1;
    Punto* punto = nodo->punto;
    Node* aux = nodo->padre;
    Node* auxHijo = nodo;
    int dimActual;
    while(aux != nullptr/* && aux->profundidad < contador*/){
        if(aux->profundidad < contador){
            aux->profundidad = contador;
        }
        dimActual = aux->dimension;
        //se debe actualizar rango de derecha
        if(auxHijo == aux->right){
            if(aux->rangoR[0] > punto->point[dimActual]){
                aux->rangoR[0] = punto->point[dimActual];
            }

            if(aux->rangoR[1] < punto->point[dimActual]){
                aux->rangoR[1] = punto->point[dimActual];
            }
        }

        if(auxHijo == aux->left){
            if(aux->rangoL[0] > punto->point[dimActual]){
                aux->rangoL[0] = punto->point[dimActual];
            }

            if(aux->rangoL[1] < punto->point[dimActual]){
                aux->rangoL[1] = punto->point[dimActual];
            }
        }
        
        aux = aux->padre;
    }
}

//TODO: Busqueda por rango
Punto* Node::buscar(float punto[]){



    //int dimension = 0;
    //Node* actual = this;
    //Punto* auxPunto;
    //while(actual != nullptr){
    //    auxPunto = actual->punto;
    //    if(auxPunto->compareD(punto, dimension) == 1)
    //        return actual->punto;

    //    if(auxPunto->getVal(dimension) < punto[dimension])
    //        actual = actual->right;
    //    else
    //        actual = actual->left;
    //    
    //    dimension = (dimension + 1) % k;
    //}

    return nullptr;
}

int Node::compareR(float val){
    if(val < rangoL[0])
        return -2;
    if(val <= rangoL[1])
        return -1;
    if(val < rangoR[0])
        return 0;
    if(val <= rangoR[1])
        return 1;
    return 2;
}


Node* insertar(float puntos[], Node* kdtree = nullptr){
    if(kdtree == nullptr){
        Node* nodo = new Node(puntos);
        nodo->rangoL[0] = puntos[0];
        nodo->rangoL[1] = puntos[0];
        nodo->rangoR[0] = puntos[0];
        nodo->rangoR[1] = puntos[0];
        nodo->dimension = 0;
        return nodo;
    }
        
    kdtree->insertar(puntos);
    return kdtree;
}



}