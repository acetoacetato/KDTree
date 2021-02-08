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
        int dimension;
        //Constructor
        Node(std::vector<float>);

        void actualizarProfundidad();
        void insertar(std::vector<float>);
        /*Punto<k>* */int buscar(std::vector<float>);
        void toJson(ofstream&, int pos = -1);
        string strPunto();
        
        // Retorna la distancia del nodo al nodo recibido por parámetro
        float distancia(std::vector<float>)const;

};




template<int k>
Node<k>::Node(std::vector<float> puntos){

    punto = new Punto<k>(puntos);
    profundidad = 0;
    dimension = 0;
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
                dimension = (dimension + 1) % k;
                aux->dimension = dimension;
                actual->right = aux;
                aux->padre = actual;
                aux->actualizarProfundidad();
                return;
            }
            actual = actual->right;
        } else{

            if(actual->left == nullptr){
                dimension = (dimension + 1) % k;
                aux->dimension = dimension;
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
float Node<k>::distancia(std::vector<float> pto)const{
    float suma = 0;
    float calc;
    for(int i=0 ; i<k ; i++){
        calc = punto->point[i]-pto[i];
        suma = suma + calc * calc;
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

template<int k>
class KDTree{

    private:
        Node<k>* raiz;
    public:
        KDTree();
        void insertar(std::vector<float>);
        //int knn(std::vector<float> , int, Node<k>* );

};

template<int k>
    KDTree<k>::KDTree(){
        std::vector<float> a = { 0 };
        Node<k>* n = new Node<k>(a);
        raiz = nullptr;
    }


template<int k>
    void KDTree<k>::insertar(std::vector<float> punto){
        if(raiz == nullptr){
            Node<k>* nodo = new Node<k>(punto);
            nodo->profundidad = 1;
            raiz = nodo;
        }
            
        raiz->insertar(punto);
    }



    std::vector<float> reff;

// Retorna los K vecinos más cercanos al punto 
template<int k>
int knn(std::vector<float> ref, int n, Node<k>* raiz){
    


    struct farther_than {
            bool operator() (const Node<k>* lhs, const Node<k>*  rhs) const {
                return lhs->distancia(reff) > rhs->distancia(reff);
            }
        }; 
    //TODO: la distancia para los ultimos if es solo de la dim disjunta

    //variables
    int count = 0;

    reff=ref;
    std::queue<Node<k>*> q;
    std::multiset<Node<k>*, farther_than> neigh; //neighbours
    q.push(raiz);

    
    
    while(q.size()>0){
            count ++;
            Node<k>* node = q.front(); q.pop();
            int dim = node->dimension;

            neigh.insert(node);
            if(neigh.size() > n) neigh.erase(neigh.begin());
            
            //descarte por distancia en dimension disjunta
            bool discard_left=false, discard_right=false;
            if(!node->left || (neigh.size()==n && ref[dim] - node->punto->point[dim] >= (*neigh.begin())->distancia(ref) )) discard_left=true;
            if(!node->right || (neigh.size()==n && node->punto->point[dim] - ref[dim] >= (*neigh.begin())->distancia(ref) )) discard_right=true;


            if(node->left && ref[dim] <= node->punto->point[dim]){
                if(!discard_right) q.push(node->right);
                q.push(node->left);
            }else{
                if(!discard_right) q.push(node->right);
                if(!discard_left) q.push(node->left);
            }
        }
        /*
        ofstream results;
        results.open("resultadosKDT.txt");
        
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
            results << "distancia = " <<  nn->distancia(ref) << " \n";
       }
        results << "nodes:" << count << endl;

        results.close();
        */
        
        
        

    

    return count;


  

    }
}