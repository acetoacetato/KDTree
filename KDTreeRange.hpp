#ifndef __KDTreeRange__
#define __KDTreeRange__

#include <iostream>
#include <queue>


//TODO: transformar todo a template.
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

        //Convierte todos los rangos del nodo en el punto.
        void updateAllRange(float[]);

        //Actualiza el rango de una dimensión respecto al punto propio del nodo.
        void updateRange(int);

        //Inserta un punto en el árbol.
        void insertar(float []);

        //Actualiza la profundidad y los rangos de los nodos que contienen el nodo ingresado.
        void actualizarProfundidad(Node*);

        //Busca un punto en el árbol.
        Punto* buscar(float []);

        //Compara el rango del nodo con un punto ingresado, en una dimensión ingresada.
        int compareR(float[], int);

        //Compara el punto del nodo con el punto ingresado, retorna true si son iguales, false en caso contrario.
        bool compare(float []);

        //Imprime el árbol completo, mostrando los rangos, el nodo padre y de que lado está con respecto a este.
        void printTree();
        private:
            void printTreeR(queue<Node*>);


};

    Node* insertar(float [], Node* kdtree = nullptr);



}

#endif