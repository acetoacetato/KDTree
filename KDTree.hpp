#include <iostream>
const int k = 3;

using namespace std;
namespace KDTree{


class Punto{
    public:
        float point [k];

        //Retorna el valor de la n-esima dimensión dado un iterador.
        float getVal(int);
        bool compare(float []);
        Punto(float []);
};

float Punto::getVal(int dim){
    return point[dim];
}

bool Punto::compare(float punto[]){
    for(int i=0 ; i<k ; i++){
        if(this->point[i] != punto[i])
            return false;
    }
    return true;
}

Punto::Punto(float puntos[]){
    for(int i=0 ; i<k ; i++)
        point[i] = puntos[i];
}




class Node{
    public:
        Punto *punto;
        Node *left, *right;
        //Constructor
        Node(float []);

        void insertar(float []);
        Punto* buscar(float []);
};

Node::Node(float puntos[]){

    punto = new Punto(puntos);
    //Se reinician los nodos hijos
    left = nullptr;
    right = nullptr;

}

void Node::insertar(float puntos[]){
    cout << "Se inserta" << puntos[0]  << ", " << puntos[1] << ", " << puntos[2] << endl;
    bool insertado = false;
    int dimension = 0;
    Node *actual = this;
    Node* aux = new Node(puntos);
    while(!insertado){
        cout << "Dimension " << dimension << endl;
        Punto punto = *actual->punto;
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

Punto* Node::buscar(float punto[]){
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


Node* insertar(float puntos[], Node* kdtree = nullptr){
    if(kdtree == nullptr)
        return new Node(puntos);
    kdtree->insertar(puntos);
    return kdtree;
}

}