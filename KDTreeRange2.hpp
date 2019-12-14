#ifndef __KDTreeRange2__
#define __KDTreeRange2__

#include <iostream>
#include <queue>
#include <list>
#include <fstream>
#include<array>

#include <math.h>


using namespace std;
namespace KDTreeRange2{

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
            int compareD(std::vector<float>, int);
            Punto(std::vector<float>);
            void imprimePunto();
            string strPunto();
    };


    template<int k>
    float Punto<k>::getVal(int dim){
        return point[dim];
    }

    template<int k>
    int Punto<k>::compareD(std::vector<float> punto, int dimension){
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

            //Convierte todos los rangos del nodo en el punto.
            void updateAllRange(std::vector<float>);

            //Actualiza el rango de una dimensión respecto al punto propio del nodo.
            void updateRange(int);

            //Inserta un punto en el árbol.
            void insertar(std::vector<float>);

            //Actualiza la profundidad y los rangos de los nodos que contienen el nodo ingresado.
            void actualizarProfundidad(Node<k>*);

            //Busca un punto en el árbol.
            Punto<k>* buscar(std::vector<float>);


            //Compara el punto del nodo con el punto ingresado, retorna true si son iguales, false en caso contrario.
            bool compare(std::vector<float>);



            //Compara las cajas de los sub-árboles para saber donde debe ir el punto recibido.
            //      Retorna -1 si debe ir en el sub-árbol de la izquierda.
            //      Retorna 1 si debe ir en el sub-árbol de la derecha.
            //      Retorna 0 el punto se encuentra en el medio de ambas.
            int comparaCajitas(std::vector<float>);

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
            int esDisjunto(std::vector<float>);

            //Retorna true si el punto ingresado está completamente contenido en el
            //  sub árbol, false en caso contrario.
            bool contenido(std::vector<float>);
            

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
    void Node<k>::updateAllRange(std::vector<float> punto){
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


            //Si es nodo hoja, se usa la regla del KD-Tree normal
            if(actual->left == nullptr && actual->right == nullptr){
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


            //Si uno de los nodos es nulo, 
            //  entonces se verifica si tiene al menos un rango disjunto con ese hijo
            if(actual->left == nullptr || actual->right == nullptr){
                Node<k>* comparador = (actual->left == nullptr)? actual->right:actual->left;

                int res = comparador->esDisjunto(punto);

                //Si no es disjunto en ninguna dimensión, se inserta en ese nodo.
                if(comparador->contenido(punto)){
                    actual = comparador;
                    dimension = (dimension + 1) % k;
                    continue;
                }


                //
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
                actualizarProfundidad(aux);
                return;
                
            }



            //Si el nodo tiene los 2 hijos, se ve si el punto a insertar está
            //  contenido en una de las cajitas (en toda dimensión o con la regla de las dimensiones).
            switch(actual->comparaCajitas(punto)){
                //Está entre las 2 cajas.
                case 0: 
                    //Se elige la caja por defecto, osea la derecha.
                    actual = actual->right;                
                    break;
                //Está contenida en la derecha o excede el rango de la derecha.
                case 1:
                    actual = actual->right;
                    break;
                //Está contenida en la izauierda o el rango de la izquierda excede el valor del punto.
                case -1:
                    actual = actual->left;
                    break;
            }



            dimension = (dimension + 1) % k;
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

            aux = aux->padre;
            contador++;
        }
    }

    template<int k>
    Punto<k>* Node<k>::buscar(std::vector<float> punto){
        Node* actual = this;
        Punto<k>* auxPunto;
        while(actual != nullptr){
            auxPunto = actual->punto;
            
            //Si es el mismo, retornarlo
            if(actual->compare(punto)){
                return actual->punto;
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
    int Node<k>::comparaCajitas(std::vector<float> val){
        /**
         *      CÓMO SE PODRÍA HACER: **ASUMIENDO DE  QUE NINGÚN HIJO ES NULO**
         *  1- Se debe cumplir con que quede al menos una dimensión disjunta.
         *  2- Por lo tanto, se ajusta una de las dimensiones como si se le agregara el punto. 
         *  3- Si cumple con que son disjuntos, se ve qué caja quedaría más pequeña.
         *  4- Si no cumple, se usa la otra.
         */
        //Si pertenece completamente en la cajita de la izquierda, se inserta ahí
        if(this->left != nullptr && this->left->contenido(val)){
            return -1;
        }

        //Si pertenece completamente en la cajita de la derecha, se inserta ahí
        if(this->right != nullptr && this->right->contenido(val)){
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
    bool Node<k>::compare(std::vector<float> val){
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
        cout << "adsasad" << endl;
        Node<k>* nodo = buscarN(punto);
        cout << "adsasad" << endl;
        Node<k>* nodoAux = nodo;
        cout << "adsasad" << endl;
        if(nodo == nullptr)
            return nullptr;
        cout << "adsasad" << endl;
        //Se parte del nodo y se va hacia abajo, hasta llegar al nodo más profundo.
        while(nodoAux->left != nullptr || nodoAux->right != nullptr){
            Node<k>* nodoL = nodoAux->left;
            Node<k>* nodoR = nodoAux->right;
            
            //Se va hacia el nodo que no sea nulo
            if( nodoAux != nodo && (nodoL == nullptr || nodoR == nullptr)){

                //Se reemplaza con el hijo izquierdo
                if(nodoR != nullptr){
                    cout << "DER" << endl;
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
                    cout << "IZQ" << endl;
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
                cout << "holi" << endl;
                nodo->punto = nodoAux->punto;
                if(nodoAux->padre->left == nodoAux){
                    nodoAux->padre->left = nullptr;
                }else{
                    nodoAux->padre->right = nullptr;
                }
                return nullptr;
            }

            if(nodoL == nullptr){
                cout << "DER; ";
                nodoAux = nodoR;
                continue;
            }

            if(nodoR == nullptr){
                cout << "IZQ; ";
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
		file << "\ttext: { name: \"" << node->strPunto() << "\"},";


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
    int Node<k>::esDisjunto(std::vector<float> val){
        for(int i=0 ; i<k ; i++){
            //Si el rango está contenido, se retorna la dimensión en la que está.
            if(rango[i][0] > val[i] || rango[i][1] < val[i])
                return i;
        }

        return -1;
    }

    template<int k>
    bool Node<k>::contenido(std::vector<float> val){
        for(int i=0 ; i<k ; i++){
            //Si el rango está contenido, se retorna la dimensión en la que está.
            if(rango[i][0] > val[i] || rango[i][1] < val[i])
                return false;
        }

        return true;
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
            Punto<k>* buscar(std::vector<float>);
            Punto<k>* eliminar(std::vector<float>);
            void toJson();
            list<Node<k>*> puntosNoDominados(std::vector<float>);
            void rangoHijos();

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
            nodo->dimension = 0;
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
    Punto<k>* KDTreeR2<k>::buscar(std::vector<float> punto){
        return raiz->buscar(punto);
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
        ofstream myfile( "arbolito.json");
        myfile << "{" << endl;
        myfile << "\tchart: {" << endl;
        myfile << "\t\tcontainer: \"#tree_simple\"" << endl;
        myfile << "\t}," << endl;
        myfile << "\tnodeStructure: ";

        raiz->imprime(raiz, myfile);
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
    
    
}

#endif //KDTreeRange2