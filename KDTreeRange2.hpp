#ifndef __KDTreeRange2__
#define __KDTreeRange2__

#include <iostream>
#include <queue>
#include <list>
#include <fstream>
#include<array>
#include <set>

#include <math.h>


using namespace std;
namespace KDTreeRange2{


    




    template<int k>
    class Punto{
        public:
            std::vector<float> point;

            //Retorna el valor de la n-esima dimensión dado un iterador.
            float getVal(int);

            std::vector<float> get();
            void set(std::vector<float>);
            //Compara los valores en una dimensión dada
            //      -1 si el pto recibido es menor
            //       0 si el pto recibido es igual
            //       1 si el pto recibido es mayor 
            int compareD(std::vector<float>&, int);
            Punto(std::vector<float>);
            void imprimePunto();
            string strPunto();
    };


    template<int k>
    float Punto<k>::getVal(int dim){
        return point[dim];
    }

    template<int k>
    std::vector<float> Punto<k>::get(){
        std::vector<float> aux;
        for(auto num : point){
            aux.push_back(num);
        }
        return aux;
    }

    template<int k>
    void Punto<k>::set(std::vector<float> punto){
        point.clear();
        for(auto num : punto){
            point.push_back(num);
        }
    }

    template<int k>
    int Punto<k>::compareD(std::vector<float>& punto, int dimension){
        if(point[dimension] > punto[dimension])
            return -1;
        if(point[dimension] < punto[dimension])
            return 1;
        else
            return 0;
    }
    template<int k>
    Punto<k>::Punto(std::vector<float> punto){
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

    template<int k>
    string Punto<k>::strPunto(){
        bool aux = false;
        string str = "(";
        for(int i=0 ; i<k ; i++){
            if(aux){
                str += ", ";
            }
            str += to_string(point[i]);
            aux = true;
        }
        str += ")";


        return str;
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
            Node(std::vector<float>);
            
            //Destructor
            ~Node();

            //Convierte todos los rangos del nodo en el punto.
            void updateAllRange(std::vector<float>&);

            //Actualiza el rango de una dimensión respecto al punto propio del nodo.
            void updateRange(int);

            //Inserta un punto en el árbol.
            void insertar(std::vector<float>);


            //Actualiza la profundidad y los rangos de los nodos que contienen el nodo ingresado.
            void actualizarProfundidad(Node<k>*);

            //Busca un punto en el árbol.
            /*Punto<k>* */ int buscar(std::vector<float>);
            Node<k>* buscarLazy(std::vector<float>);


            //Compara el punto del nodo con el punto ingresado, retorna true si son iguales, false en caso contrario.
            bool compare(std::vector<float>&);



            //Compara las cajas de los sub-árboles para saber donde debe ir el punto recibido.
            //      Retorna -1 si debe ir en el sub-árbol de la izquierda.
            //      Retorna 1 si debe ir en el sub-árbol de la derecha.
            //      Retorna 0 el punto se encuentra en el medio de ambas.
            int comparaCajitas(std::vector<float>&);

            //Imprime el árbol completo, mostrando los rangos, el nodo padre y de que lado está con respecto a este.
            void printTree();

            //Imprime los rangos del nodo.
            void printRange();

            //Elimina el punto, retornandolo en caso de existir.
            Node<k>* eliminar(std::vector<float>);

            //Actualiza los rangos desde el mismo nodo hasta el nodo recibido. Asumiendo que el nodo actual se elimina.
            void actualizarRangos(Node<k>*);

            //Imprime el arbol completo en formato json a un archivo recibido
            void imprime(Node<k>*, ofstream& file);

            //Retorna un string que contiene el punto en todas sus dimensiones
            string strPunto();

            //Retorna un string que contiene el punto del nodo padre en todas sus dimensiones
            //  retorna -1 si no tiene padre.
            string strPadre();

            //Retorna un string que tiene, en formato json, todos los rangos que tiene el punto.
            string strRangos();

            //Retorna true si tiene al menos un hijo, false en caso contrario.
            bool children();
            
            //Retorna true si el punto no esta dominado con respecto al punto ingresado ( si en alguna de las dimensiones el punto actual es menor al ingresado )
            bool noDominado(std::vector<float>);

            //Retorna true si el punto no esta dominado con respecto al punto ingresado ( si en alguna de las dimensiones el punto actual es menor al ingresado )
            bool rangoNoDominado(std::vector<float>);

            //Retorna la dimensión en la que el punto no está contenido en los rangos del nodo
            //  Si no está contenido en ninguna de ellas, retorna -1.
            int esDisjunto(std::vector<float>&);

            //Retorna true si el punto ingresado está completamente contenido en el
            //  sub árbol, false en caso contrario.
            bool contenido(std::vector<float>&, int dim = -1);
            
            // Retorna la dimensión por la cual se disjuntan los hijos
            int dimDisjunta();
            
            
            //Retorna true si el punto se encuentra en una caja representada por el punto menor y el punto mayor
            bool insideBox(std::vector<float> , std::vector<float>);
            
            //Retorna true si el rango del subarbol contiene alguna seccion en la caja
            bool rangeInsideBox(std::vector<float> , std::vector<float>);
            
            //Retorna true si el rango se encuentra completo en la caja
            bool rangeFullInsideBox(std::vector<float> , std::vector<float>);
            
            //Retorna la distancia Euclidiana desde el punto de referencia al punto del nodo
            float distancePoint(std::vector<float>) const;
            
            //Retorna la distancia Euclidiana desde el punto de referencia al rango del nodo
            float distanceRange(std::vector<float>);

            //FIXME: averiguar que hacia
            float distanceDisj(std::vector<float>);



            private:
                //Imprime el arbol completo, mostrando en cada nodo su valor, su padre, si es izq o der, y los rangos de el nodo.
                void printTreeR(queue<Node*>);
                //Busca y retorna el nodo que contenga el punto ingresado por parámetro o null en caso contrario.
                Node<k>* buscarN(std::vector<float>);

                


    };


    template<int k>
    Node<k>::Node(std::vector<float> punto_){

        punto = new Punto<k>(punto_);
        profundidad = 0;
        dimension = -1;
        //Se reinician los nodos hijos
        left = nullptr;
        right = nullptr;
        padre = nullptr;
    }
    
    template<int k>
    Node<k>::~Node(){
      if(left!=nullptr)left->~Node();
      if(right!=nullptr)right->~Node();
      delete[] punto;
    }

    template<int k>
    void Node<k>::updateAllRange(std::vector<float>& punto){
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
    void Node<k>::insertar(std::vector<float> punto){
        bool insertado = false;
        int dimension = 0;
        Node *actual = this;
        Node* aux = new Node(punto);

        while(!insertado){

            //Auxiliar que apunta al punto del nodo.
            Punto<k> punto_ = *actual->punto;
            bool cambia = false;
            //Si es nodo hoja, se usa la regla del KD-Tree normal
            if(actual->left == nullptr && actual->right == nullptr){
                //si el punto a insertar, en la dimensión, es mayor que el punto actual en la dimensión,
                        //  Se le inserta en la derecha
                        if(punto_.compareD(punto, dimension) == 1){
                            actual->right = aux;
                            aux->padre = actual;
                            actualizarProfundidad(aux);
                            aux->updateAllRange(punto);
                            aux->dimension = -1;
                            actual->dimension = dimension;
                            return;

                        //si el punto a insertar, en la dimensión, es menor que el punto actual en la dimensión,
                        //  Se le inserta en la izquierda
                        }else{
                            actual->left = aux;
                            aux->padre = actual;
                            aux->updateAllRange(punto);
                            actualizarProfundidad(aux);
                            aux->dimension = -1;
                            actual->dimension = dimension;
                            return;
                        }
            }


            //Si uno de los nodos es nulo, 
            //  entonces se verifica si tiene al menos un rango disjunto con ese hijo
            if(actual->left == nullptr || actual->right == nullptr){
                Node<k>* comparador = (actual->left == nullptr)? actual->right:actual->left;

                int res = comparador->esDisjunto(punto);
                //Si no es disjunto en ninguna dimensión, se inserta en ese sub árbol.
                if(comparador->contenido(punto)){
                    actual = comparador;
                    aux->dimension = -1;
                    dimension = (dimension + 1) % k;
                    continue;
                }



                // Acá se llega con res != -1, así que hay alguna dimensión disjunta
                if(actual->left == nullptr){


                    //Si el punto es mayor que la caja en la dimensión disjunta,
                    //  se intercambian los hijos.
                    if(actual->right->rango[res][1] < punto[res]){
                        
                        actual->left = actual->right;
                        actual->right = aux;
                    } else{
                        actual->left = aux;
                    }
                    
                    actual->dimension = res;
                }else{

                    //Si el punto es menor que la caja en la dimensión disjunta,
                    //  se intercambian los hijos.
                    if(actual->left->rango[res][0] > punto[res]){
                        actual->right = actual->left;
                        actual->left = aux;
                    } else{
                        actual->right = aux;
                    }
                    actual->dimension = res;
                }
                aux->padre = actual;
                aux->updateAllRange(punto);
                aux->dimension = -1;
                actualizarProfundidad(aux);
                return;
                
            }



            //Si el nodo tiene los 2 hijos, se ve si el punto a insertar está
            //  contenido en una de las cajitas (en toda dimensión o con la regla de las dimensiones).

            int resp = actual->comparaCajitas(punto);
            switch(resp){
                //Está entre las 2 cajas.
                case 0: 
                    //Se elige la caja por defecto, osea la derecha.
                    actual = actual->right;                
                    break;
                //Está contenida en la derecha o excede el rango de la derecha.
                case 1:
                    //actual->dimension = resp[1];
                    actual = actual->right;
                    break;
                //Está contenida en la izauierda o el rango de la izquierda excede el valor del punto.
                case -1:
                    //actual->dimension = resp[1];
                    actual = actual->left;
                    break;
            }



            
        }

    }
   

    template<int k>
    void Node<k>::actualizarProfundidad(Node* nodo){
        //La base es profundidad 1 para todos los nodos.
        int contador = 1;
        
        //El punto del nodo con el que se va a actualizar la profundidad.
        Punto<k>* punto = nodo->punto;
        Node<k>* aux = nodo->padre;

        while(aux != nullptr){
            //Se actualiza la profundidad de cada nodo, hacia arriba.
            // Solo en caso de que sea necesario, es decir, en caso de que su profundidad sea menor
            if(aux->profundidad < contador)
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
            //cout << "Disjunto de " << aux->strPunto() << endl;
            aux = aux->padre;
            contador++;
        }
    }

    template<int k>
    /*Punto<k>* */int Node<k>::buscar(std::vector<float> punto){
        //cout << "\n\n" << endl;
        Node* actual = this;
        Punto<k>* auxPunto;
        int visitados = 1;
        //cout << "Se busca: " << punto[0] << ", " << punto[1] << ", " << punto[2] << endl;
        while(actual != nullptr){
            auxPunto = actual->punto;
            //cout << auxPunto->strPunto() << endl;
            //Si es el mismo, retornarlo
            if(actual->compare(punto)){

                return visitados;// actual->punto;
            }
                
            //Si tiene un hijo, se compara la caja nomas

            //Si tiene 2 hijos, se compara la dim disjunta de un hijo de manera normal,
            //  sino, se va al otro hijo

            if(!actual->left || !actual->right){
                if(actual->dimension == -1){
                    cout << "aaaa" << endl;
                }
                if(actual->right && actual->right->contenido(punto, actual->dimension)){
                    actual = actual->right;
                    visitados++;
                    continue;
                } else if(actual->left && actual->left->contenido(punto, actual->dimension)){
                    actual = actual->left;
                    visitados++;
                    continue;

                }else{
                    return -1;
                    //return nullptr;
                }   
            }
            //Si llega hasta acá significa que tiene 2 hijos.
            //Se compara la dim disjunta de un hijo de manera normal,
            //  sino, se va al otro hijo

            ///if(actual->right->rango[actual->dimension][0] > punto[actual->dimension]){
            ///    actual = actual->left;
            ///} else{
            ///    actual= actual->right;
            ///}
            ///////Si está contenido completamente en la caja de la derecha, se sigue por allá.
           

            if(actual->right && actual->right->contenido(punto, actual->dimension)){
                actual = actual->right;
                visitados++;
                //cout << "der"<<endl;
                continue;
            }


            
            //Si está contenido completamente en la caja de la izquierda, se sigue por allá.
            if(actual->left && actual->left->contenido(punto, actual->dimension)){
                actual = actual->left;
                //cout << "izq"<<endl;
                visitados++;
                continue;
            }

            return -1;//nullptr;
        }


        return -1;//nullptr;
    }

    template<int k>
    /*Punto<k>* */Node<k>* Node<k>::buscarLazy(std::vector<float> punto){
        Node* actual = this;
        Punto<k>* auxPunto;
        int visitados = 1;

        while(actual != nullptr){
            auxPunto = actual->punto;

            if(actual->compare(punto)){
                return actual;// actual->punto;
            }
                
            //Si tiene un hijo, se compara la caja nomas

            //Si tiene 2 hijos, se compara la dim disjunta de un hijo de manera normal,
            //  sino, se va al otro hijo
           

            if(actual->right && actual->right->rango[actual->dimension][0] <= punto[actual->dimension]){
                //cout << "false" << endl;
                actual = actual->right;
                visitados++;
                continue;

            } else {
                actual = actual->left;
                visitados++;
                continue;
            }

        }


        return nullptr;//nullptr;
    }






    template<int k>
    int Node<k>::comparaCajitas(std::vector<float>& val){
        /**
         *      CÓMO SE PODRÍA HACER: **ASUMIENDO DE  QUE NINGÚN HIJO ES NULO**
         *  1- Se debe cumplir con que quede al menos una dimensión disjunta.
         *  2- Por lo tanto, se ajusta una de las dimensiones como si se le agregara el punto. 
         *  3- Si cumple con que son disjuntos, se ve qué caja quedaría más pequeña.
         *  4- Si no cumple, se usa la otra.
         */
        int res[2];
        //Si pertenece completamente en la cajita de la izquierda, se inserta ahí
        // ////this->left->contenido(val, this->dimension)
        if(this->left != nullptr && this->left->rango[this->dimension][1] >= val[this->dimension]){
            return -1;
        }

        //Si pertenece completamente en la cajita de la derecha, se inserta ahí
        ///   ////this->right->contenido(val, this->dimension)
        if(this->right != nullptr && this->right->rango[this->dimension][0] <= val[this->dimension]){

            return 1;
        }

        //Ahora viene lo bueno: saber qué cajita es mejor extender:
        //      Se comienza verificando qué dimensiones son disjuntas.

        std::vector<int> dimensiones;

        //Variables para calcular las distancias desde el punto a la caja.

        int dimDis = -1;
        float dist = INFINITY, distLeft, distRight;

        for(int i=0 ; i<k ; i++){

            // Si el máximo de un rango es menor que el mínimo del otro rango
            //                         o
            // Si el máximo de el otro rango es menor que el mínimo del primer rango
            //Entonces son disjuntos.
            if(this->right->rango[i][1] < this->left->rango[i][0] ||
                this->left->rango[i][1] < this->right->rango[i][0] ){
                    dimensiones.push_back(i);

                    //Se obtiene la menor distancia entre los rangos máximos y mínimos
                    //  de cada dimensión y se usan para calcular la distancia con pitágoras
                    float auxDist = this->right->rango[i][0] - this->left->rango[i][1];
                    if(auxDist < dist){
                        dist = auxDist;
                        dimDis = i;
                    }

                }
        }

        //Se determina la menor distancia del punto con cada sub árbol en la dimensión
        
        if(val[dimDis] < this->right->rango[dimDis][0]){
            distRight = this->right->rango[dimDis][0] - val[dimDis];
        }else{
            //Entonces está al medio, osea su distancia es 0
            if(val[dimDis] <= this->right->rango[dimDis][0]){
                distRight = 0;

            }else{
                distRight =  val[dimDis] - this->right->rango[dimDis][1];
            }
        }

        if(val[dimDis] > this->left->rango[dimDis][1]){
            distLeft = val[dimDis] - this->left->rango[dimDis][1];
        }else{
            //Entonces está al medio, osea su distancia es 0
            if(val[dimDis] >= this->left->rango[dimDis][0]){
                distLeft = 0;
                
            }else{
                distLeft =  this->left->rango[dimDis][0] - val[dimDis];
            }
        }
        
        if(distLeft < distRight){
            return -1;
        }

        if(distRight < distLeft){
            return 1;
        }

        
        //Si no ha retornado hasta ahora, es porque está justo al medio de ambas.
        return 0;
    }


    template<int k>
    bool Node<k>::compare(std::vector<float>& val){
        for(int i=0 ; i<k ; i++){
            if(punto->point[i] != val[i]){
                return false;
            }
                
        }
        return true;
    }


    template<int k>
    Node<k>* Node<k>::buscarN(std::vector<float> punto){
        Node* actual = this;
        Punto<k>* auxPunto;
        while(actual != nullptr){
            auxPunto = actual->punto;
            
            //Si es el mismo, retornarlo
            if(actual->compare(punto)){
                return actual;
            }
                
            
            //Si está contenido completamente en la caja de la derecha, se sigue por allá.
            if(actual->right && actual->right->contenido(punto)){
                actual = actual->right;
                continue;
            }

            //Si está contenido completamente en la caja de la izquierda, se sigue por allá.
            if(actual->left && actual->left->contenido(punto)){
                actual = actual->left;
                continue;
            }

            return nullptr;
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
    void Node<k>::printRange(){
        for(int i=0 ; i<k ; i++){
            cout << "\t[" << rango[i][0] << ", " << rango[i][1] << "]" << endl;
        }
    }

    template<int k>
    Node<k>* Node<k>::eliminar(std::vector<float> punto){
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
            if( nodoAux != nodo && (nodoL == nullptr || nodoR == nullptr)){

                //Se reemplaza con el hijo izquierdo
                if(nodoR != nullptr){
                    nodo->punto = nodoAux->punto;
                    //hay que averiguar que hijo es
                    if(nodoAux->padre->left == nodoAux){
                        nodoAux->padre->left = nodoR;
                    }else{
                        nodoAux->padre->right = nodoR;
                    }
                    
                    nodoR->padre = nodoAux->padre;

                    return nullptr;
                }

                //Se reemplaza con el hijo derecho
                if(nodoL != nullptr){
                    nodo->punto = nodoAux->punto;

                    if(nodoAux->padre->left == nodoAux){
                        nodoAux->padre->left = nodoL;
                    }else{
                        nodoAux->padre->right = nodoL;
                    }
                    nodoL->padre = nodoAux->padre;

                    return nullptr;
                }

                //Si ninguno es nulo, entonces es un nodo hoja
                nodo->punto = nodoAux->punto;
                if(nodoAux->padre->left == nodoAux){
                    nodoAux->padre->left = nullptr;
                }else{
                    nodoAux->padre->right = nullptr;
                }
                return nullptr;
            }

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
                if(nodo->padre->left == nodo)
                    nodo->padre->left = nullptr;
                else
                    nodo->padre->right = nullptr;
            }
            return nodo;
        }
        //Sino, se reemplaza y se va subiendo y actualizando los rangos.
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
        
        int profundidad = this->profundidad;
        Node<k>* hijo = this;
        Node<k>* otroHijo = this;
        
        Node<k>* aux = this;
        //Se asume que es un nodo no raiz
        bool esHijoDerecho = (aux->padre->right == this);

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
    void Node<k>::imprime(Node<k>* node, ofstream& file){
        file << "{ "<<endl;
		file << "\ttext: {\n";
        file << "name: \"" << node->strPunto() << "\",\n";
        file << "dimension: \"" << node->dimension << "\",\n";
        for(int i=0 ; i<k ; i++){
            file << "rango" << i <<": \"[" << node->rango[i][0] << ", " << node->rango[i][1] << "]\"";
            if(i < k-1){
                file << ",";
            }
            file << "\n";
        }
        file << "},\n";
        


		if(node->children()){
			file << "\tchildren: [" << endl;

			if(node->left != nullptr){
                imprime(node->left, file);
            }
                
            if(node->right != nullptr){
                if(node->left != nullptr)
                    file << ",";
                imprime(node->right, file);
            }
                
            
			file << "]";
		}
		file << "}" << endl;
    }

    //Retorna un string que contiene el punto en todas sus dimensiones
    template<int k>
    string Node<k>::strPunto(){
        return punto->strPunto();
    }

    //Retorna un string que contiene el punto del nodo padre en todas sus dimensiones
    //  retorna -1 si no tiene padre.
    template<int k>
    string Node<k>::strPadre(){
        return (this->padre)? this->padre->strPunto():"-1";
    }

    //Retorna un string que tiene, en formato json, todos los rangos que tiene el punto.
    template<int k>
    string Node<k>::strRangos(){
        string str = "\"";
        for(int i=0 ; i<k ; i++){
            str += "[";
            str += to_string(this->rango[i][0]);
            str += ", ";
            str += to_string(this->rango[i][1]);
            str += "]; ";
        }

        str += "\"";
        return str;
    }

    template<int k>
    bool Node<k>::children(){
        if(this->left != nullptr || this->right != nullptr)
            return true;
        return false;
    }


    template<int k>
    void Node<k>::printTreeR(queue<Node<k>*> queue){
        Node<k>* nodo = queue.front();
        if(nodo == nullptr){
            return;
        }

        Punto<k>* punto = nodo->punto;
        
        queue.pop();
        if(nodo->left)
            queue.push(nodo->left);
        if(nodo->right)
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
            string a = (derecha)? "derecha":"izquierda";
            cout << a << endl;

        }
        for(int i=0 ; i<k ; i++){
            cout << "[" << nodo->rango[i][0] << ", " << nodo->rango[i][1] << "]" << endl;
        }
        cout << endl << endl;

        printTreeR(queue);
    }
    
    template<int k>
    bool Node<k>::noDominado(std::vector<float> point){
      for(int i=0; i<k; i++){ 
        if(punto->point[i] < point[i]){
          return true;
        }
      }
      return false;
    }
    
    template<int k>
    bool Node<k>::rangoNoDominado(std::vector<float> point){
      for(int i=0; i<k; i++){ 
        if(rango[i][0] < point[i]){
          return true;
        }
      }
      return false;
    
    }
    

    //Retorna la dimensión en la  que el punto es disjunto con el rango del nodo
    template<int k>
    int Node<k>::esDisjunto(std::vector<float>& val){


        float dist = -9999;
        int dim = -1;
        for(int i=0 ; i<k ; i++){
            //Si el punto no está contenido en el rango, se retorna la dimensión.
            if(rango[i][0] > val[i] || rango[i][1] < val[i])
                if(rango[i][0]-val[i]>dist){
                    dist = rango[i][0]-val[i];
                    dim = i;
                }
                if(val[i]-rango[i][1]>dist){
                    dist = val[i]-rango[i][1];
                    dim = i;
                }
        }
        return dim;

    }

    template<int k>
    bool Node<k>::contenido(std::vector<float>& val, int dim){
        if(dim == -1){
            for(int i=0 ; i<k ; i++){
                //Si el rango está contenido, se retorna la dimensión en la que está.
                if(rango[i][0] > val[i] || rango[i][1] < val[i])
                    return false;
            }
        }else{
            //cout << "||" << dimension << "||";
            //cout << rango[dim][0] << " > "  << val[dim] << " || " << rango[dim][1] << " < "  << val[dim] << endl;
            if(rango[dim][0] > val[dim] || rango[dim][1] < val[dim]){
                //cout << "false" << endl;
                return false;

            }
        }
        
        
        //cout << "true" << endl;
        return true;
    }

    // Retorna la dimensión por la cual se disjuntan los hijos. -1 si no hay rangos disjuntos
    template<int k>
    int Node<k>::dimDisjunta(){
        /*
            Supuesto procedimiento:
                1- obtengo el [ de mayor valor
                2- lo comparo con los [ ] del otro nodo
                3- si está entremedio, el rango está contenido
        */

        if(left == nullptr || right == nullptr)
            return 0;        
        //cout << "valor de k = " << k << endl;
        for(int i=0 ; i<k ; i++){
             
            //ADVERTENCIA: Codigo spaghetti
            //  Me costó mucho entender que hacer en este caso, 
            //      ya que el como separa las dimenciones está un poco roto.
            //TODO: Aumentar legibilidad de esto
            //cout << "" << left->rango[i][0] << " <= " << right->rango[i][0] << endl;
            if(left->rango[i][0] <= right->rango[i][0]){
                if(left->rango[i][1] >= right->rango[i][0]){
                    continue;
                }else{
                    return i;
                }
            } else{
                if(right->rango[i][1] >= left->rango[i][0]){
                    continue;
                } else{
                    return i;
                }
            }

        

        }
        //cout << punto->strPunto() << endl;
        //cout << left->strRangos() << endl;
        //cout << right->strRangos()<< endl;
        return -1;
    }
    
    template<int k>
    bool Node<k>::insideBox(std::vector<float> menor, std::vector<float> mayor){
      for(int i=0;i<k;i++){
        if((punto->point[i] < menor[i]) || (punto->point[i] > mayor[i])){
          return false;
        }
      }
      return true;
    }
    
    template<int k>
    bool Node<k>::rangeInsideBox(std::vector<float> menor, std::vector<float> mayor){
      for(int i=0;i<k;i++){
        if((rango[i][1] < menor[i]) || (rango[i][0] > mayor[i])){
          return false;
        }
      }
      return true;
    }
    
    template<int k>
    bool Node<k>::rangeFullInsideBox(std::vector<float> menor, std::vector<float> mayor){
      for(int i=0;i<k;i++){
        if((rango[i][0] < menor[i]) || (rango[i][1] > mayor[i])){
          return false;
        }
      }
      return true;
    }
    
    template<int k>
    float Node<k>::distancePoint(std::vector<float> ref) const{
      float dist= 0.0f;
      float calc;
      for(int i=0;i<k;i++){
        calc = punto->point[i]-ref[i];
        dist = dist + calc * calc;
      }
      return sqrt(dist);
    }
    
    template<int k>
    float Node<k>::distanceRange(std::vector<float> ref){
      float dist= 0.0f;
      float calc;
      for(int i=0;i<k;i++){
        if(ref[i] > rango[i][1]){
          calc = ref[i]-rango[i][1];
          dist = dist + calc * calc;
        }
        else if(ref[i] < rango[i][0]){
          calc = ref[i]-rango[i][0];
          dist = dist + calc * calc;
        }
      }
      return sqrt(dist);
    }
    
    
    template<int k>
    float Node<k>::distanceDisj(std::vector<float> ref){
      float dist = abs( ref[dimension] - punto->point[dimension]);
      return dist;
    
    }




/////////////////////////////////////////////////////////////////////////////////////////////////////


    template <int k>
    class KDTreeR2{
        private:
            Node<k>* raiz;
        public:        
            KDTreeR2();
            int profundidad();
            Node<k>* insertar(std::vector<float>);
            void mostrarArbol();
            /*Punto<k>* */int buscar(std::vector<float>);
            Node<k>* buscarLazy(std::vector<float>);
            Punto<k>* eliminar(std::vector<float>);
            void toJson();
            list<Node<k>*> puntosNoDominados(std::vector<float>);
            void rangoHijos();
            void actualizaDim();
            list<Node<k>*> puntosInsideBox(std::vector<float>, std::vector<float>);
            void eliminaPuntosInsideBox(std::vector<float>, std::vector<float>);
            Node<k>* vecinoMasCercano(std::vector<float>);
            int vecinosMasCercano(std::vector<float>, int);

    };

    template<int k>
    KDTreeR2<k>::KDTreeR2(){
        std::vector<float> a = { 0 };
        Node<k>* n = new Node<k>(a);
        raiz = nullptr;
    }

    template<int k>
    int KDTreeR2<k>::profundidad(){
        if(raiz == nullptr)
            return 0;
        return raiz->profundidad;
    }

    template<int k>
    Node<k>* KDTreeR2<k>::insertar(std::vector<float> punto){
        if(raiz == nullptr){
            Node<k>* nodo = new Node<k>(punto);
            nodo->updateAllRange(punto);
            nodo->dimension = -1;
            raiz = nodo;
            return nodo;
        }
            
        raiz->insertar(punto);
        return raiz;
    }

    template<int k>
    void KDTreeR2<k>::mostrarArbol(){
        raiz->printTree();
        return;
    }

    template<int k>
    /*Punto<k>* */ int KDTreeR2<k>::buscar(std::vector<float> punto){
        return raiz->buscar(punto);
    }

    template<int k>
    /*Punto<k>* */ Node<k>* KDTreeR2<k>::buscarLazy(std::vector<float> punto){
        return raiz->buscarLazy(punto);
    }



    template<int k>
    Punto<k>* KDTreeR2<k>::eliminar(std::vector<float> punto){
        if(raiz == nullptr)
            return nullptr;
        Node<k>* nodo = raiz->eliminar(punto);
        if(nodo == raiz){
            raiz = nullptr;
        }
        ;
        if(nodo == nullptr)
            return nullptr;
        return nodo->punto;
    }

    template<int k>
    void KDTreeR2<k>::toJson(){
       
        ofstream myfile( "basic-example.js");
        myfile << "var gente = {" << endl;
        myfile << "\tchart: {" << endl;
        myfile << "\t\tcontainer: \"#basic-example\"," << endl;
        myfile << "\t\tconnectors: {" << endl;
        myfile << "\t\t\ttype: 'step'" << endl;
        myfile << "\t\t}," << endl;
        myfile << "\t\tnode: {" << endl;
        myfile << "\t\t\tHTMLclass: 'nodeExample1'" << endl;
        myfile << "\t\t}" << endl;
        myfile << "\t}," << endl;
        myfile << "\tnodeStructure: ";

        raiz->imprime(raiz, myfile);
        myfile << "}\n";

        myfile << "chart_config = gente";
    }
    
    template<int k>
    list<Node<k>*> KDTreeR2<k>::puntosNoDominados(std::vector<float>punto){
      std::queue <Node<k>*> q;
      std::list <Node<k>*> l;
      q.push(raiz);
      while(!q.empty()){
        Node<k>* actual=q.front();
        if(actual->noDominado(punto)){
          l.push_back(actual);
        }
        if(actual->left != nullptr && actual->left->rangoNoDominado(punto))
          q.push(actual->left);
        if(actual->right != nullptr && actual->right->rangoNoDominado(punto))
          q.push(actual->right);
        q.pop();
      }
      
      return l;
    
    }

    template<int k>
    void KDTreeR2<k>::rangoHijos(){
        cout << "Nodo izq:" << endl;
        if(this->raiz->left)
            this->raiz->left->printRange();
        else
        {
            cout << "[]" << endl;
        }

        cout << "Nodo der:" << endl;
        if(this->raiz->right)
            this->raiz->right->printRange();
        else
        {
            cout << "[]" << endl;
        }
    }
    
    template<int k>
    list<Node<k>*> KDTreeR2<k>::puntosInsideBox(std::vector<float> menor, std::vector<float> mayor){
      std::queue <Node<k>*> q;
      std::list <Node<k>*> l;
      q.push(raiz);
      while(!q.empty()){
        Node<k>* actual=q.front();
        if(actual->insideBox(menor,mayor)){
          l.push_back(actual);
        }
        if(actual->left != nullptr && actual->left->rangeInsideBox(menor,mayor))
          q.push(actual->left);
        if(actual->right != nullptr && actual->right->rangeInsideBox(menor,mayor))
          q.push(actual->right);
        q.pop();
      }
      
      return l;
    }
    
    
    template<int k>
    void KDTreeR2<k>::eliminaPuntosInsideBox(std::vector<float> menor, std::vector<float> mayor){
      std::queue<Node<k>*> q;
      q.push(raiz);
      while(!q.empty()){
        Node<k>* actual=q.front();
        if(actual->insideBox(menor,mayor)){
          actual->eliminar(actual->punto->point);
        }
        if(actual->left != nullptr && actual->left->rangeInsideBox(menor,mayor)){
          if(actual->left->rangeFullInsideBox(menor,mayor)){
            actual->left->~Node();
          }
          else{
            q.push(actual->left);
          }
        }
        if(actual->right != nullptr && actual->right->rangeInsideBox(menor,mayor))
          if(actual->right->rangeFullInsideBox(menor,mayor)){
            actual->right->~Node();
          }
          else{
            q.push(actual->right);
          }
        q.pop();
      }
    
    }
    
    template<int k>
    Node<k>* KDTreeR2<k>::vecinoMasCercano(std::vector<float> ref){
       std::queue<Node<k>*> q;
       Node<k>* vecino;
       float distance=999999.9f;
       float distAct;
       Node<k>* actual = raiz;
       while(actual != nullptr){
           distAct=actual->distancePoint(ref);
           //se reemplaza el vecino
           if(distance > distAct){
               vecino = actual;
               distance = distAct;
           }
           //se agregan los subarboles
           distAct=actual->left->distanceRange(ref);
           if(distance > distAct)
               q->instertar(actual->left,distAct);
           
           distAct=actual->right->distanceRange(ref);
           if(distance > distAct)
               q->instertar(actual->right,distAct);
           //se obtiene el siguiente para operar
           actual=(Node<k>*)q->pop();
       }
       return vecino;
    }

    std::vector<float> reff;
    
    template<int k>
    int KDTreeR2<k>::vecinosMasCercano(std::vector<float> ref, int n){
        struct lex_compare_nodo {
            bool operator() (const Node<k>* lhs, const Node<k>* rhs) const {
                std::vector<float> origen = {0,0,0};
                return lhs < rhs;
            }
        }; 

        struct farther_than {
            bool operator() (const Node<k>* lhs, const Node<k>*  rhs) const {
                return lhs->distancePoint(reff) > rhs->distancePoint(reff);
            }
        }; 

        
        reff=ref;
        std::queue<Node<k>*> q;
        std::multiset<Node<k>*, farther_than> neigh; //neighbours
        q.push(raiz);

        int count = 0;

        while(q.size()>0){
            count ++;
            Node<k>* node = q.front(); q.pop();
            int dim = node->dimension;

            neigh.insert(node);
            if(neigh.size() > n) neigh.erase(neigh.begin());
            
            //descarte por distancia en dimension disjunta
             bool discard_left=false, discard_right=false;
            if(!node->left || (neigh.size()==n && ref[dim] - node->left->rango[dim][1] >= (*neigh.begin())->distancePoint(ref) )) discard_left=true;
            if(!node->right || (neigh.size()==n && node->right->rango[dim][0] - ref[dim] >= (*neigh.begin())->distancePoint(ref) )) discard_right=true;

            if(node->left && ref[dim] <= node->left->rango[dim][1]){
                if(!discard_right) q.push(node->right);
                q.push(node->left);
            }else{
                if(!discard_right) q.push(node->right);
                if(!discard_left) q.push(node->left);
            }
        }
        /*
        ofstream results;
        results.open("resultadosKDTR.txt");
        //se imprime por consola el vecindario obtenido y se retorna la cantidad de nodos visitados
        cout << "punto inicial\n";

        for(int j = 0; j < k; j++){
                cout << ref[j] << " ";
            }
        cout << "\n-------------------------\n";
        for(auto nn : neigh){
            for(int j = 0; j < k; j++){
                results << nn->punto->point[j] << " ";
            }
            results << "distancia = " <<  nn->distancePoint(ref) << " \n";
       }
       results << "nodes:" << count << endl;

       results.close();
       */
       
       return count;
    }
    
    

    
}

#endif //KDTreeRange2
