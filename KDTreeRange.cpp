#include "KDTreeRange.hpp"

namespace KDTreeRange{
    
    
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

    Punto::Punto(float punto[]){
        for(int i=0 ; i<k ; i++)
            point[i] = punto[i];
    }





    Node::Node(float punto_[]){

        punto = new Punto(punto_);
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



    void Node::insertar(float punto[]){
        bool insertado = false;
        int dimension = 0;
        Node *actual = this;
        Node* aux = new Node(punto);
        while(!insertado){

            //Auxiliar que apunta al punto del nodo.
            Punto punto_ = *actual->punto;


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
                            cout << "Se inserta en der"<< endl;
                            return;

                        //si el punto a insertar, en la dimensión, es menor que el punto actual en la dimensión,
                        //  Se le inserta en la derecha
                        }else{
                            actual->left = aux;
                            aux->padre = actual;
                            aux->updateAllRange(punto);
                            actualizarProfundidad(aux);
                            cout << "Se inserta en izq"<< endl;
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
                        cout << "Se inserta en der"<< endl;
                        return; 
                    }

                    //Sino, es el izquierdo
                    if(actual->left == nullptr){
                        actual->left = aux;
                        aux->padre = actual;
                        aux->updateAllRange(punto);
                        actualizarProfundidad(aux);
                        cout << "Se inserta en izq"<< endl;
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



    void Node::actualizarProfundidad(Node* nodo){
        //La base es dimensión 1 para todos los nodos.
        int contador = 1;
        //El punto del nodo con el que se va a actualizar la profundidad.
        Punto* punto = nodo->punto;
        Node* aux = nodo->padre;

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

    Punto* Node::buscar(float punto[]){

        int dimension = 0;
        Node* actual = this;
        Punto* auxPunto;

        while(actual != nullptr){
            auxPunto = actual->punto;
            
            //Si es el mismo, retornarlo
            if(actual->compare(punto))
                return actual->punto;
            
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

    int Node::compareR(float val[], int dimension){
        
        if(left != nullptr && (left->rango[dimension][1] >= val[dimension])){
            return -1;
        }
        if(right != nullptr && (right->rango[dimension][0] <= val[dimension])){
            return 1;
        }

        return 0;
    }

    bool Node::compare(float val[]){
        for(int i=0 ; i<k ; i++){
            if(punto->point[i] != val[i]){
                return false;
            }
                
        }
        return true;
    }

    void Node::printTree(){
        queue <KDTreeRange::Node*> q;
        q.push(this);
        
        printTreeR(q);
    }

    void Node::printTreeR(queue<Node*> queue){
        Node* nodo = queue.front();
        if(nodo == nullptr){
            return;
        }

        Punto* punto = nodo->punto;
        
        queue.pop();
        queue.push(nodo->left);
        queue.push(nodo->right);
        
        
        cout << "(" << punto->point[0] << ", " << punto->point[1] << ", " << punto->point[2] << ")" << endl;
        if(nodo->padre){
            bool derecha = (nodo == nodo->padre->right);
            Punto* puntoPadre = nodo->padre->punto;
            cout << "Padre: " << puntoPadre->point[0] << ", " << puntoPadre->point[1] << ", " << puntoPadre->point[2] << ") (" << ((derecha)? "derecha":"izquierda") << ")" << endl;

        }
        for(int i=0 ; i<k ; i++){
            cout << "[" << nodo->rango[i][0] << ", " << nodo->rango[i][1] << "]" << endl;
        }
        cout << endl << endl;

        printTreeR(queue);
    }


    Node* insertar(float punto[], Node* kdtree){
    if(kdtree == nullptr){
        
        Node* nodo = new Node(punto);
        nodo->updateAllRange(punto);
        nodo->dimension = 0;
        return nodo;
    }
        
    kdtree->insertar(punto);
    return kdtree;
}
}