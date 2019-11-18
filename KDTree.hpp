#include <iostream>
#include<vector>
using namespace std;
namespace KDTree{

template<int k>
class Punto{
    public:
        std::vector<float> point;

        //Retorna el valor de la n-esima dimensión dado un iterador.
        float getVal(int);
        bool compare(std::vector<float>);
        Punto(std::vector<float>);
};

template<int k>
float Punto<k>::getVal(int dim){
    return point[dim];
}

template<int k>
bool Punto<k>::compare(std::vector<float> punto){
    for(int i=0 ; i<k ; i++){
        if(this->point[i] != punto[i])
            return false;
    }
    return true;
}

template<int k>
Punto<k>::Punto(std::vector<float> puntos){
    for(int i=0 ; i<k ; i++)
        point.push_back(puntos[i]);
}



template<int k>
class Node{
    public:
        Punto<k> *punto;
        Node<k> *left, *right, *padre;
        int profundidad;
        //Constructor
        Node(std::vector<float>);

        void actualizarProfundidad();
        void insertar(std::vector<float>);
        Punto<k>* buscar(std::vector<float>);
};

template<int k>
Node<k>::Node(std::vector<float> puntos){

    punto = new Punto<k>(puntos);
    profundidad = 0;
    //Se reinician los nodos hijos
    left = nullptr;
    right = nullptr;
    padre = nullptr;

}

template<int k>
void Node<k>::actualizarProfundidad(){
    int profundidad = 1;
    Node<k>* actual = this;
    while(actual != nullptr){
        if(actual->profundidad < profundidad)
            actual->profundidad = profundidad;

        profundidad++;
        actual = actual->padre;
    }
}

template<int k>
void Node<k>::insertar(std::vector<float> puntos){
    bool insertado = false;
    int dimension = 0;
    Node<k> *actual = this;
    Node<k>* aux = new Node(puntos);
    while(!insertado){
        Punto<k> punto = *actual->punto;
        if( punto.getVal(dimension) < puntos[dimension]){
            

            //se inserta en la derecha
            if(actual->right == nullptr){
                actual->right = aux;
                aux->padre = actual;
                aux->actualizarProfundidad();
                return;
            }
            actual = actual->right;
        } else{

            if(actual->left == nullptr){
                actual->left = aux;
                aux->left =nullptr;
                aux->padre = actual;
                aux->actualizarProfundidad();
                return;
            }

            actual = actual->left;
        }
            
        
        //Se cicla sobre las dimensiones
        dimension = (dimension + 1) % k;
    }

}

template<int k>
Punto<k>* Node<k>::buscar(std::vector<float> punto){
    int dimension = 0;
    Node<k>* actual = this;
    Punto<k>* auxPunto;
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
Node<k>* insertar(std::vector<float> puntos, Node<k>* kdtree = nullptr){
    if(kdtree == nullptr)
        return new Node<k>(puntos);
    kdtree->insertar(puntos);
    return kdtree;
}

}

