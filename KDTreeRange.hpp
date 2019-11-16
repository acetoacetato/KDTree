#ifndef __KDTreeRange__
#define __KDTreeRange__

#include <iostream>
#include <queue>

using namespace std;
namespace KDTreeRange{

    template<int k>
    class Punto{
        public:
            std::vector<float> point;

            //Retorna el valor de la n-esima dimensión dado un iterador.
            float getVal(int);
            //Compara los valores en una dimensión dada
            //      -1 si el pto recibido es menor
            //       0 si el pto recibido es igual
            //       1 si el pto recibido es mayor 
            int compareD(float[], int);
            Punto(float []);
            void imprimePunto();
    };


    template<int k>
    float Punto<k>::getVal(int dim){
        return point[dim];
    }

    template<int k>
    int Punto<k>::compareD(float punto[], int dimension){
        if(point[dimension] > punto[dimension])
            return -1;
        if(point[dimension] < punto[dimension])
            return 1;
        else
            return 0;
    }
    template<int k>
    Punto<k>::Punto(float punto[]){
        for(int i=0 ; i<k ; i++)
            point.push_back(punto[i]);
    }


    template<int k>
    void Punto<k>::imprimePunto(){
        bool aux = false;
        cout << "(";
        for(int i=0 ; i<k ; i++){
            if(aux)
                cout << ", ";
            cout << point[i];
            aux = true;
        }
        cout << ")" << endl;
    }

/////////////////////////////////////////////////////////////////////////////////


    template<int k>
    class Node{
        public:
            Punto<k> *punto;

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
            void actualizarProfundidad(Node<k>*);

            //Busca un punto en el árbol.
            Punto<k>* buscar(float []);

            //Compara el rango del nodo con un punto ingresado, en una dimensión ingresada.
            int compareR(float[], int);

            //Compara el punto del nodo con el punto ingresado, retorna true si son iguales, false en caso contrario.
            bool compare(float []);

            //Imprime el árbol completo, mostrando los rangos, el nodo padre y de que lado está con respecto a este.
            void printTree();

            //Elimina el punto, retornandolo en caso de existir.
            Node<k>* eliminar(float[]);

            //Actualiza los rangos desde el mismo nodo hasta el nodo recibido. Asumiendo que el nodo actual se elimina.
            void actualizarRangos(Node<k>*);


            private:
                //Imprime el arbol completo, mostrando en cada nodo su valor, su padre, si es izq o der, y los rangos de el nodo.
                void printTreeR(queue<Node*>);
                //Busca y retorna el nodo que contenga el punto ingresado por parámetro o null en caso contrario.
                Node<k>* buscarN(float []);

                


    };


    template<int k>
    Node<k>::Node(float punto_[]){

        punto = new Punto<k>(punto_);
        profundidad = 0;
        //Se reinician los nodos hijos
        left = nullptr;
        right = nullptr;
        padre = nullptr;
    }

    template<int k>
    void Node<k>::updateAllRange(float punto[]){
        for(int i=0 ; i < k ; i++){
            rango[i][0] = punto[i];
            rango[i][1] = punto[i];
        }
    }

    template<int k>
    void Node<k>::updateRange(int dim){
        rango[dim][0] = punto->point[dim];
        rango[dim][1] = punto->point[dim];
    }


    template<int k>
    void Node<k>::insertar(float punto[]){
        bool insertado = false;
        int dimension = 0;
        Node *actual = this;
        Node* aux = new Node(punto);
        while(!insertado){

            //Auxiliar que apunta al punto del nodo.
            Punto<k> punto_ = *actual->punto;


            //Se compara el rango del árbol con el punto a ingresar.
            int res = actual->compareR(punto, dimension);
            switch(res){
                
                //Se va hacia el sub-árbol de la izquierda
                case -1: 
                    actual = actual ->left;
                    break;

                //Se va hacia el sub-árbol de la derecha
                case 1:
                    actual = actual->right;
                    break;

                //se inserta de acuerdo al valor del nodo y a la profundidad de arboles hijos
                //FIXME: esto se ve más complejo de lo que debería, funciona pero hay que reducir el code.
                case 0:
                    
                    //si ambos están vacíos, se compara con el valor del nodo actual
                    if(actual->right == nullptr && actual->left == nullptr){

                        //si el punto a insertar, en la dimensión, es mayor que el punto actual en la dimensión,
                        //  Se le inserta en la derecha
                        if(punto_.compareD(punto, dimension) == 1){
                            actual->right = aux;
                            aux->padre = actual;
                            actualizarProfundidad(aux);
                            aux->updateAllRange(punto);
                            return;

                        //si el punto a insertar, en la dimensión, es menor que el punto actual en la dimensión,
                        //  Se le inserta en la derecha
                        }else{
                            actual->left = aux;
                            aux->padre = actual;
                            aux->updateAllRange(punto);
                            actualizarProfundidad(aux);
                            return;
                        }
                    }

                    //En caso de que el valor del punto a insertar y el del punto actual sea el mismo en la dimensión
                    //Se le inserta en el nodo de menor profundidad.

                    //Si el nodo derecho es nulo, es el de menor profundidad
                    if(actual->right == nullptr){
                        actual->right = aux;
                        aux->padre = actual;
                        aux->updateAllRange(punto);
                        actualizarProfundidad(aux);
                        return; 
                    }

                    //Sino, es el izquierdo
                    if(actual->left == nullptr){
                        actual->left = aux;
                        aux->padre = actual;
                        aux->updateAllRange(punto);
                        actualizarProfundidad(aux);
                        return;
                    }

    
                    //En caso de que ninguno sea nulo, se comparan las profundidades 
                    //  y se va hacia el sub arbol menos profundo.

                    //Si ambos tienen la misma profundidad, se comparan los puntos en la dimensión.
                    if(actual->right->profundidad == actual->left->profundidad){

                        //si es menor al punto, se va a la izq
                        //En cualquier otro caso, a la derecha
                        if(punto_.compareD(punto, dimension) == -1){
                            actual = actual->left;
                        }else{
                            actual = actual->right;
                        }

                        dimension = (dimension + 1) % k;
                        continue;
                    }

                    //Si la derecha es menos profunda, se va para allá
                    //  En caso contrario se va a la izquierda
                    if(actual->right->profundidad < actual->left->profundidad){
                        actual = actual->right;
                    }else{
                        actual = actual->left;
                    }

                    break;

            }

            dimension = (dimension + 1) % k;
        }

    }


    template<int k>
    void Node<k>::actualizarProfundidad(Node* nodo){
        //La base es dimensión 1 para todos los nodos.
        int contador = 1;
        //El punto del nodo con el que se va a actualizar la profundidad.
        Punto<k>* punto = nodo->punto;
        Node<k>* aux = nodo->padre;

        while(aux != nullptr){
            //Se actualiza la profundidad de cada nodo, hacia arriba.
            aux->profundidad = contador;
            
            //se actualizan los rangos.
            for(int i=0 ; i<k ; i++){

                //Se actualiza el rango inferior.
                if(aux->rango[i][0] > punto->point[i]){
                    aux->rango[i][0] = punto->point[i];

                //Se actualiza el rango superior.
                }else{
                    if(aux->rango[i][1] < punto->point[i]){
                        aux->rango[i][1] = punto->point[i];
                    }
                }
            }

            aux = aux->padre;
            contador++;
        }
    }

    template<int k>
    Punto<k>* Node<k>::buscar(float punto[]){
        //cout << "Se busca: (" << punto[0] << ", " << punto[1] << ", " << punto[2] << ")" << endl;
        int dimension = 0;
        Node* actual = this;
        Punto<k>* auxPunto;

        while(actual != nullptr){
            auxPunto = actual->punto;
            
            //Si es el mismo, retornarlo
            if(actual->compare(punto))
                return actual->punto;
            //Si está fuera del rango del arbol, ya no existe
            if(actual->rango[dimension][1] < punto[dimension] || actual->rango[dimension][0] > punto[dimension])
                return nullptr;

            //sino, se ve en que rango puede estar
            if(actual->right != nullptr && actual->right->rango[dimension][1] >= punto[dimension] && actual->right->rango[dimension][0] <= punto[dimension]){
                actual = actual->right;
            }      
            else
            {
                //En caso de que no haya un nodo derecho, se va al izquierdo, 
                //  en la sgte iteración se comprueba si efectivamente puede estar ahí el punto a buscar.
                actual = actual->left;
            }
            dimension = (dimension + 1) % k;
        }


        return nullptr;
    }

    template<int k>
    int Node<k>::compareR(float val[], int dimension){
        
        if(left != nullptr && (left->rango[dimension][1] >= val[dimension])){
            return -1;
        }
        if(right != nullptr && (right->rango[dimension][0] <= val[dimension])){
            return 1;
        }

        return 0;
    }

    template<int k>
    bool Node<k>::compare(float val[]){
        for(int i=0 ; i<k ; i++){
            if(punto->point[i] != val[i]){
                return false;
            }
                
        }
        return true;
    }


    template<int k>
    Node<k>* Node<k>::buscarN(float punto[]){

        int dimension = 0;
        Node* actual = this;
        Punto<k>* auxPunto;

        while(actual != nullptr){
            auxPunto = actual->punto;
            
            //Si es el mismo, retornarlo
            if(actual->compare(punto))
                return actual;
            
            //Si está fuera del rango del arbol, ya no existe
            if(actual->rango[dimension][1] < punto[dimension] || actual->rango[dimension][0] > punto[dimension])
                return nullptr;
            
            //sino, se ve en que rango puede estar
            if(actual->right->rango[dimension][1] >= punto[dimension] && actual->right->rango[dimension][0] <= punto[dimension]){
                actual = actual->right;
            }      
            else
            {
                actual = actual->left;
            }
            
            dimension = (dimension + 1) % k;
        }


        return nullptr;
    }


    template<int k>
    void Node<k>::printTree(){
        queue <Node<k>*> q;
        q.push(this);
        
        printTreeR(q);
    }

    template<int k>
    Node<k>* Node<k>::eliminar(float punto[]){
        //Buscar el nodo a eliminar
        Node<k>* nodo = buscarN(punto);
        Node<k>* nodoAux = nodo;
        if(nodo == nullptr)
            return nullptr;
        
        //Se parte del nodo y se va hacia abajo, hasta llegar al nodo más profundo.

        while(nodoAux->left != nullptr || nodoAux->right != nullptr){
            Node<k>* nodoL = nodoAux->left;
            Node<k>* nodoR = nodoAux->right;

            //Se va hacia el nodo que no sea nulo

            if(nodoL == nullptr){
                nodoAux = nodoR;
                continue;
            }

            if(nodoR == nullptr){
                nodoAux = nodoL;
                continue;
            }

            //Si ninguno de los 2 es nulo, se va hacia el de menor profundidad o al izquierdo por defecto.
            if(nodoL->profundidad < nodoR->profundidad){
                nodoAux = nodoAux->right;
                continue;
            }else{
                nodoAux = nodoAux->left;
                continue;
            }
        }   

        //Si el nodo más profundo (nodoAux) es igual al nodo a eliminar, se elimina y el arbol queda vacío
        if(nodoAux == nodo){
            if(nodo->padre != nullptr){
                cout << "436" << endl;
                nodoAux->actualizarRangos(nodo->padre);
                cout << "438" << endl;
                if(nodo->padre->left == nodo)
                    nodo->padre->left = nullptr;
                else
                    nodo->padre->right = nullptr;
            }
            return nodo;
        }

        //Sino, se reemplaza y se va subiendo y actualizando los rangos.
        nodoAux->actualizarRangos(nodo);
        nodo->punto = nodoAux->punto;
        if(nodoAux->padre->left == nodoAux){
            nodoAux->padre->left = nullptr;
            return nodoAux;
        } 
        
        if(nodoAux->padre->right == nodoAux){
            nodoAux->padre->right = nullptr;
            return nodoAux;
        }

        return nullptr;

    }

    template<int k>
    void Node<k>::actualizarRangos(Node<k>* final){
        
        //punto->imprimePunto();
        //cout << endl;
        int profundidad = 1;
        Node<k>* hijo = this;
        Node<k>* otroHijo = this;
        
        Node<k>* aux = this;
        //Se asume que es un nodo no raiz
        bool esHijoDerecho = (aux->padre->right == this);
        //TODO: esto se debe hacer hasta el nodo padre o hasta el nodo raiz, si se sigue haciendo efectivo el cambio más arriba.
        //  Hasta ahora lo hace hasta el nodo raiz, sacrificando eficiencia.
        do{
            hijo = aux;
            aux = aux->padre;

            if(aux == nullptr){
                return;
            }

            aux->profundidad = profundidad;

            

            if(esHijoDerecho){
                otroHijo = aux->left;
            }else{
                otroHijo = aux->right;
            }
            //Se actualiza el rango maximo y minimo de cada dimension
            for(int i=0 ; i<k ; i++){

                //Se actualiza el rango minimo de cada dimensión.
                //  Si valor minimo no es el mismo que el valor del punto ni el minimo del rango del otro hijo,
                //  se actualiza al menor de estos 2.

                //Si el rango del eliminado es igual que el valor del punto, se deja igual
                if(hijo->rango[i][0] != aux->punto->point[i]){

                    //En caso contrario, se comprueba si existe un hijo en el otro nodo
                    //  en caso contrario, se reemplaza el rango por el punto.
                    if(otroHijo == nullptr){
                        aux->rango[i][0] = aux->punto->point[i];
                    } else{
                        //Si existe, entonces se comprueba si el rango eliminado 
                        //  es distinto al rango del otro hijo
                        if(hijo->rango[i][0] != otroHijo->rango[i][0]){

                            //En ese caso, se reemplaza con el de menor rango
                            aux->rango[i][0] = (aux->punto->point[i] < otroHijo->rango[i][0])? aux->punto->point[i]:otroHijo->rango[i][0];
                        }
                        
                        
                    }
                    
                }


                //Se actualiza el rango máximo de cada dimensión.
                //  Si valor máximo no es el mismo que el valor del punto ni el máximo del rango del otro hijo,
                //  se actualiza al mayor de estos 2.

                //Se usa la misma lógica, pero con el mayor
                if(hijo->rango[i][1] != aux->punto->point[i]){
                    if(otroHijo == nullptr){
                        aux->rango[i][1] = aux->punto->point[i];
                    }else{
                        if(hijo->rango[i][1] != otroHijo->rango[i][1]){
                            aux->rango[i][1] = (aux->punto->point[i] > otroHijo->rango[i][1])? aux->punto->point[i]:otroHijo->rango[i][1];
                        }
                    }      
                }
            }

            //Se actualiza si es el hijo derecho y se sube al padre.
            if(aux->padre != nullptr){
                esHijoDerecho = (aux->padre->right == this);
            }
            profundidad++;
        }while(true);


    }

    template<int k>
    void Node<k>::printTreeR(queue<Node<k>*> queue){
        Node<k>* nodo = queue.front();
        if(nodo == nullptr){
            return;
        }

        Punto<k>* punto = nodo->punto;
        
        queue.pop();
        queue.push(nodo->left);
        queue.push(nodo->right);
        
        bool aux = false;

        //Se muestra el punto
        punto->imprimePunto();

        if(nodo->padre){
            bool derecha = (nodo == nodo->padre->right);
            Punto<k>* puntoPadre = nodo->padre->punto;
            
            aux = false;
            cout << "Padre: ";
            puntoPadre->imprimePunto();

        }
        for(int i=0 ; i<k ; i++){
            cout << "[" << nodo->rango[i][0] << ", " << nodo->rango[i][1] << "]" << endl;
        }
        cout << endl << endl;

        printTreeR(queue);
    }


/////////////////////////////////////////////////////////////////////////////////////////////////////


    template <int k>
    class KDTree{
        private:
            Node<k>* raiz;
        public:        
            KDTree();
            int profundidad();
            Node<k>* insertar(float []);
            void mostrarArbol();
            Punto<k>* buscar(float[]);
            Punto<k>* eliminar(float[]);

    };

    template<int k>
    KDTree<k>::KDTree(){
        float a[k] = { 0 };
        Node<k>* n = new Node<k>(a);
        raiz = nullptr;
    }

    template<int k>
    int KDTree<k>::profundidad(){
        if(raiz == nullptr)
            return 0;
        return raiz->profundidad;
    }

    template<int k>
    Node<k>* KDTree<k>::insertar(float punto[]){
        if(raiz == nullptr){
            Node<k>* nodo = new Node<k>(punto);
            nodo->updateAllRange(punto);
            nodo->dimension = 0;
            raiz = nodo;
            return nodo;
        }
            
        raiz->insertar(punto);
        return raiz;
    }

    template<int k>
    void KDTree<k>::mostrarArbol(){
        raiz->printTree();
        return;
    }

    template<int k>
    Punto<k>* KDTree<k>::buscar(float punto[]){
        return raiz->buscar(punto);
    }

    template<int k>
    Punto<k>* KDTree<k>::eliminar(float punto[]){
        if(raiz == nullptr)
            return nullptr;
        Node<k>* nodo = raiz->eliminar(punto);
        if(nodo == raiz){
            raiz = nullptr;
        }
        return nodo->punto;
    }
}

#endif