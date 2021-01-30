#include <iostream>
#include<vector>
#include <fstream>
#include<list>
#include <cmath>
#include<stack>
#include <set>

using namespace std;
namespace KDTree{

template<int k>
class Punto{
    public:
        std::vector<float> point;

        //Retorna el valor de la n-esima dimensión dado un iterador.
        float getVal(int);
        bool compare(std::vector<float>&);
        Punto(std::vector<float>);
        string strPunto();
        
};

template<int k>
float Punto<k>::getVal(int dim){
    return point[dim];
}

template<int k>
bool Punto<k>::compare(std::vector<float>& punto){
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
        /*Punto<k>* */int buscar(std::vector<float>);
        void toJson(ofstream&, int pos = -1);
        string strPunto();
        
        // Retorna la distancia del nodo al nodo recibido por parámetro
        float distancia(std::vector<float>);

        // Retorna los K vecinos más cercanos al punto 
        int knn(std::vector<float>, int);
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
/*Punto<k>* */int Node<k>::buscar(std::vector<float> punto){
    int dimension = 0;
    Node<k>* actual = this;
    Punto<k>* auxPunto;
    int recorridos = 1;
    while(actual != nullptr){
        auxPunto = actual->punto;

        if(auxPunto->compare(punto))
            return recorridos;//actual->punto;

        if(auxPunto->getVal(dimension) < punto[dimension]){
            actual = actual->right;
            recorridos++;
        } else{
            actual = actual->left;
            recorridos++;
        }
            
        
        dimension = (dimension + 1) % k;
    }

    return -1;//nullptr;
}

template<int k>
Node<k>* insertar(std::vector<float> puntos, Node<k>* kdtree = nullptr){
    if(kdtree == nullptr)
        return new Node<k>(puntos);
    kdtree->insertar(puntos);
    return kdtree;
}

template<int k>
void toJson(Node<k>* raiz){
    ofstream myfile( "Graficador/basic-example.js");
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

    raiz->toJson(myfile);
    myfile << "}\n";

    myfile << "chart_config = gente";
}

template<int k>
string Node<k>::strPunto(){
    return punto->strPunto();
}

template<int k>
void Node<k>::toJson(ofstream& file, int pos){
        file << "{ "<<endl;
		file << "\ttext: {\n";
        file << "name: \"";

        if(pos != 0)
            file << ((pos == -1)? "L ":"R ");

        file << strPunto() << "\",\n";
        file << "},\n";

        if(left != nullptr || right != nullptr){
			file << "\tchildren: [" << endl;

            if(left != nullptr){
                left->toJson(file, -1);
            }

            if(right != nullptr){
                right->toJson(file, 1);
            }

            file << "]" << endl;
        }

        file << "}" << endl;
}



// Retorna la distancia del nodo al nodo recibido por parámetro
template<int k>
float Node<k>::distancia(std::vector<float> pto){
    float suma = 0;
    for(int i=0 ; i<k ; i++){
        suma += pow(punto->point[i] - pto[i], 2);
    }
    return sqrt(suma);

}

template<int k>
struct nodo{
    Node<k>* nodito;
    float distancia;
};

template<int k>
struct lex_compare {
    bool operator() (const nodo<k>& lhs, const nodo<k>& rhs) const {
        
   
        return lhs.distancia < lhs.distancia ;
    }
};
//////////////////////////////////////////////////////////////////////////

    

// Retorna los K vecinos más cercanos al punto 
template<int k>
int Node<k>::knn(std::vector<float> pto, int cant){

    // Estructura auxiliar para guardar referencia al nodo y su distancia al punto.
    typedef struct par{
        Node<k>* nodo;
        float dist;
    }par;
    
    // Estructura que contiene el comparador para el set de los vecinos cercanos
    //FIXME: cambiar comparación para admitir valores iguales
    struct lex_compare {
        bool operator() (const par& lhs, const par& rhs) const {
            if(lhs.dist == rhs.dist){
                return lhs.nodo != rhs.nodo;
            }
            return lhs.dist < rhs.dist;
        }
    };  


    struct lex_compare_nodo {
        bool operator() (const Node<k>* lhs, const Node<k>* rhs) const {
            std::vector<float> origen = {0,0,0};
            return lhs < rhs;
        }
    };  
    //TODO: la distancia para los ultimos if es solo de la dim disjunta

    bool insertado = false;
    int dimension = 0;
    int cantNodos = 0;
    std::queue<Node<k>*> pendientes;
    std::set<par, lex_compare> nn;
    std::set<Node<k>*, lex_compare_nodo> visitados;
    Node<k> *actual = this;
    Node<k>* mejor = nullptr;
    while(!insertado){
        Punto<k> punto = *actual->punto;
        if( punto.getVal(dimension) < pto[dimension]){
            
            //se llegó a la "hoja"
            if(actual->right == nullptr){
                break;
            }
            actual = actual->right;
        } else{
            // Se llegó a la "hoja"
            if(actual->left == nullptr){
                break;
            }

            actual = actual->left;
        }
            
        
        //Se cicla sobre las dimensiones
        dimension = (dimension + 1) % k;
    }
    par aux;
    aux.nodo = actual;
    aux.dist = actual->distancia(pto);
    nn.insert(aux);
    visitados.insert(actual);

    pendientes.push(actual);
    
    
        


    // Se va subiendo y comparando con los hijos.
    while(!pendientes.empty()){
        cantNodos = cantNodos + 1;
        auto aux = pendientes.front();
        pendientes.pop();
        visitados.insert(aux);

        // Se calcula la distancia del punto parametro al punto aux.
        int dist = aux->distancia(pto);

        // Si está más cerca que el peor vecino 
        //  y aún no se tienen n vecinos cercanos
        if(nn.size() <= cant || (*std::prev(nn.end())).dist < dist ){
            par puntito;
            puntito.dist = dist;
            puntito.nodo = aux;
            nn.insert(puntito);

            // Se elimina el último elemento si se excede la cantidad de vecinos cercanos
            if(nn.size() > cant)
                nn.erase(std::prev(nn.end()));
        }
        //cout << "segundo " << ((*std::prev(nn.end())).dist < abs(pto[dimension] - aux->left->punto->point[dimension]) || nn.size() < cant ) << endl;
        //Me dolió demasiado esta línea:
        //  Si el hijo no ha sido visitado y es un potencial vecino cercano, se inserta para recorrerlo
        if(aux->left != nullptr && visitados.find(aux->left) == visitados.end()){
            if(nn.size() <= cant ||   ((*std::prev(nn.end())).dist < abs(pto[dimension] - aux->left->punto->point[dimension])))   {
                pendientes.push(aux->left);
            }
            
        }

        if(aux->right != nullptr && visitados.find(aux->right) == visitados.end()){
            if(nn.size() <= cant ||   ((*std::prev(nn.end())).dist < abs(pto[dimension] - aux->right->punto->point[dimension])))   {
                pendientes.push(aux->right);
            }
            
        }


        if(aux->padre != nullptr && visitados.find(aux->padre) == visitados.end() ){
            pendientes.push(aux->padre);
        }
    }
    std::list<Node<k>*> retorno;

     for (auto p = nn.begin(); p != nn.end(); ++p)
        retorno.push_back((*p).nodo);

    return cantNodos;


  

    }
}