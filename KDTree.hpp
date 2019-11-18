#include <iostream>

using namespace std;
namespace KDTree{

template<int k>
class Punto{
    public:
        float point [k];

        //Retorna el valor de la n-esima dimensión dado un iterador.
        float getVal(int);
        bool compare(float []);
        Punto(float []);
};

template<int k>
float Punto<k>::getVal(int dim){
    return point[dim];
}

template<int k>
bool Punto<k>::compare(float punto[]){
    for(int i=0 ; i<k ; i++){
        if(this->point[i] != punto[i])
            return false;
    }
    return true;
}

template<int k>
Punto<k>::Punto(float puntos[]){
    for(int i=0 ; i<k ; i++)
        point[i] = puntos[i];
}



template<int k>
class Node{
    public:
        Punto<k> *punto;
        Node<k> *left, *right;
        //Constructor
        Node(float []);

        void insertar(float []);
        Punto<k>* buscar(float []);
};

template<int k>
Node<k>::Node(float puntos[]){

    punto = new Punto<k>(puntos);
    //Se reinician los nodos hijos
    left = nullptr;
    right = nullptr;

}

template<int k>
void Node<k>::insertar(float puntos[]){
    cout << "Se inserta" << puntos[0]  << ", " << puntos[1] << ", " << puntos[2] << endl;
    bool insertado = false;
    int dimension = 0;
    Node<k> *actual = this;
    Node<k>* aux = new Node(puntos);
    while(!insertado){
        cout << "Dimension " << dimension << endl;
        Punto<k> punto = *actual->punto;
        if( punto.getVal(dimension) < puntos[dimension]){
            
            cout << "derecha" << endl;

            //se inserta en la derecha
            if(actual->right == nullptr){
                actual->right = aux;
                return;
            }
            actual = actual->right;
        } else{
            
            
            cout << "izquierda" << endl;
            if(actual->left == nullptr){
                actual->left = aux;
                aux->left =nullptr;

                return;
            }

            actual = actual->left;
        }
            
        
        //Se cicla sobre las dimensiones
        dimension = (dimension + 1) % k;
    }

}

template<int k>
Punto<k>* Node<k>::buscar(float punto[]){
    int dimension = 0;
    Node* actual = this;
    Punto* auxPunto;
    while(actual != nullptr){
        auxPunto = actual->punto;
        if(auxPunto->compare(punto))
            return actual->punto;

        if(auxPunto->getVal(dimension) < punto[dimension])
            actual = actual->right;
        else
            actual = actual->left;
        
        dimension = (dimension + 1) % k;
    }

    return nullptr;
}

template<int k>
Node<k>* insertar(float puntos[], Node<k>* kdtree = nullptr){
    if(kdtree == nullptr)
        return new Node<k>(puntos);
    kdtree->insertar(puntos);
    return kdtree;
}

}