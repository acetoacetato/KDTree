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

        //Rango de cada dimension, con k el numero de dimensiones
        float rango[k][2];

        int profundidad;
        int dimension;

        //Nodos hijos y el que lo contiene, null si es raíz
        Node *left, *right, *padre;
        //Constructor
        Node(float []);

        void updateAllRange(float[]);
        void updateRange(int);
        void insertar(float []);
        void actualizarProfundidad(Node*);
        Punto* buscar(float []);
        int compareR(float[], int);
        bool compare(float []);


};

Node::Node(float puntos[]){

    punto = new Punto(puntos);
    profundidad = 0;
    //Se reinician los nodos hijos
    left = nullptr;
    right = nullptr;
    padre = nullptr;
}

void Node::updateAllRange(float punto[]){
    for(int i=0 ; i < k ; i++){
        rango[i][0] = punto[i];
        rango[i][1] = punto[i];
    }
}

void Node::updateRange(int dim){
    rango[dim][0] = punto->point[dim];
    rango[dim][1] = punto->point[dim];
}



//FIXME: la inserción no está correcta desde el (9,6,7)
void Node::insertar(float puntos[]){
    cout << "Se inserta: " << puntos[0]  << ", " << puntos[1] << ", " << puntos[2] << endl;
    bool insertado = false;
    int dimension = 0;
    Node *actual = this;
    Node* aux = new Node(puntos);
    while(!insertado){
        Punto punto = *actual->punto;
        Node* r = actual->right;
        Node* l = actual->left;
        if(actual->rango[dimension][0] > puntos[dimension]){
            aux->rango[dimension][0] = puntos[dimension];
        }else{
            if(actual->rango[dimension][1] < puntos[dimension]){
            actual->rango[dimension][1] = puntos[dimension];
        }
        }
        int res = actual->compareR(puntos, dimension);
        cout << "\tDimension: " << dimension << endl;
        cout << "\tRango: [" << actual->rango[dimension][0] << ", " << actual->rango[dimension][1] << "]" << endl;
        
        cout << "\tRango_L: [" << ((actual->left)? actual->left->rango[dimension][0]:-99) << ", " << ((actual->left)? actual->left->rango[dimension][1]:-99) << "]" << endl;
        cout << "\tRango_R: [" << ((actual->right)? actual->right->rango[dimension][0]:-99) << ", " << ((actual->right)? actual->right->rango[dimension][1]:-99) << "]" << endl;
        
        

        
        cout << "\tResultado = " << res << endl;
        switch(res){
            
            case -1:
                //se inserta en la izquierda
                actual = actual ->left;
                cout << "izq"<< endl;
                break;
            case 1:
                //se inserta en la derecha
                actual = actual->right;
                cout << "der"<< endl;
                break;
            case 0:
                //se inserta de acuerdo al valor del nodo actual
                if(actual->right == nullptr && actual->left == nullptr){
                    if(punto.compareD(puntos, dimension) == 1){
                        actual->right = aux;
                        aux->padre = actual;
                        actualizarProfundidad(aux);
                        aux->updateAllRange(puntos);
                        cout << "Se inserta en der"<< endl;
                        return;
                    }else{
                        actual->left = aux;
                        aux->padre = actual;
                        aux->updateAllRange(puntos);
                        actualizarProfundidad(aux);
                        cout << "Se inserta en izq"<< endl;
                        return;
                    }
                }
                //se inserta en el lado con menos profundidad
                if(actual->right == nullptr){
                    actual->right = aux;
                    aux->padre = actual;
                    aux->updateAllRange(puntos);
                    actualizarProfundidad(aux);
                    cout << "Se inserta en der"<< endl;
                    return; 
                }

                if(actual->left == nullptr){
                    actual->left = aux;
                    aux->padre = actual;
                    aux->updateAllRange(puntos);
                    actualizarProfundidad(aux);
                    cout << "Se inserta en izq"<< endl;
                    return;
                }
                //FIXME: aca se debe ir al sub arbol de menor profundidad o a la izq o derecha
                //if(punto.compareD(puntos, dimension) == 1){
                //    actual = actual->right;
                //    cout << "Der"<< endl;
                //}
//
                //if(punto.compareD(puntos, dimension) == -1){
                //    actual = actual->left;
                //    cout << "izq"<< endl;
                //}
                cout << "----ProfundidadL: " << actual->left->profundidad << endl; 
                cout << "----ProfundidadR: " << actual->right->profundidad << endl; 
                //se compara la dimension de cada lado
                //if(actual->right->profundidad == actual->left->profundidad){
                    if(punto.compareD(puntos, dimension) == 1){
                        actual = actual->right;
                        cout << "Der"<< endl;
                    }else{

                        if(punto.compareD(puntos, dimension) == -1){
                            actual = actual->left;
                            cout << "izq"<< endl;
                        }else{
                            actual = actual->right;
                            cout << "Derr" << endl;
                        }
                    }

                
                    dimension = (dimension + 1) % k;
                    continue;
                //}

                if(actual->right->profundidad < actual->left->profundidad){
                    actual = actual->right;
                    cout << "der"<< endl;
                }else{
                    actual = actual->left;
                    cout << "1izq"<< endl;
                }

                break;

        }

        dimension = (dimension + 1) % k;
    }

}


void Node::actualizarProfundidad(Node* nodo){
    //cout << "actualiza" << nodo->punto->point[0] << nodo->punto->point[1] << nodo->punto->point[2] << endl;
    int contador = 1;
    Punto* punto = nodo->punto;
    Node* aux = nodo->padre;
    int dimActual;
    while(aux != nullptr/* && aux->profundidad < contador*/){
        aux->profundidad = contador;
        
        //se actualizan los rangos
        for(int i=0 ; i<k ; i++){
            if(aux->rango[dimension][0] > punto->point[dimension]){
            aux->rango[dimension][0] = punto->point[dimension];
            }else{
                if(aux->rango[dimension][1] < punto->point[dimension]){
                    aux->rango[dimension][1] = punto->point[dimension];
                }
            }
        }

        aux = aux->padre;
        contador++;
    }
}

//TODO: Busqueda por rango
Punto* Node::buscar(float punto[]){

    cout << "Se busca (" << punto[0] << ", " << punto[1] << ", " << punto[2] << ")" << endl;
    int dimension = 0;
    Node* actual = this;
    Punto* auxPunto;

    while(actual != nullptr){
        auxPunto = actual->punto;
        cout << "\tDimension " << dimension << endl;
        cout << "\tpunto actual (" << auxPunto->point[0] << ", " << auxPunto->point[1] << ", " << auxPunto->point[2] << ")" << endl;
        cout << "\tRango actual [" << actual->rango[dimension][0] << ", " << actual->rango[dimension][1] << "]\n";

        cout << "\t\tRango izq [" << actual->left->rango[dimension][0] << ", " << actual->left->rango[dimension][1] << "]\n";
        cout << "\t\tRango der [" << actual->right->rango[dimension][0] << ", " << actual->right->rango[dimension][1] << "]\n";
        //Si es el mismo, retornarlo
        if(actual->compare(punto))
            return actual->punto;
        
        //Si está fuera del rango del arbol, se muere
        if(actual->rango[dimension][1] < punto[dimension] || actual->rango[dimension][0] > punto[dimension])
            return nullptr;
        
        //sino, se ve en que rango puede estar
        if(actual->right->rango[dimension][1] < punto[dimension] && actual->right->rango[dimension][0] < punto[dimension]){
            cout << "pa la derecha" << endl;
            actual = actual->right;
        }      
        else
        {
            cout << "pa la izquierda" << endl;
            actual = actual->left;
        }
        
        dimension = (dimension + 1) % k;
    }

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

int Node::compareR(float val[], int dimension){
    
    if(left != nullptr && (left->rango[dimension][1] > val[dimension])){
        return -1;
    }
    if(right != nullptr && (right->rango[dimension][0] < val[dimension])){
        return 1;
    }

    return 0;
}

bool Node::compare(float val[]){
    for(int i=0 ; i<k ; i++){
        if(punto->point[i] != val[i])
            return false;
    }
    return true;
}


Node* insertar(float puntos[], Node* kdtree = nullptr){
    if(kdtree == nullptr){
        
        Node* nodo = new Node(puntos);
        nodo->updateAllRange(puntos);
        nodo->dimension = 0;
        cout << "rango " << nodo->rango[0] << "," << nodo->rango[1] << endl;
        return nodo;
    }
        
    kdtree->insertar(puntos);
    return kdtree;
}



}