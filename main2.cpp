#include "KDTreeRange2.hpp"
#include "KDTreeRange.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace KDTreeRange2;
using namespace KDTreeRange;


std::vector<float> generaPunto(int dim){
    
    float num;
    
    std::vector<float> numero;
    for(int i=0 ; i<dim ; i++){
        //Genera un numero aleatorio entre 1 y 10000
        num = rand() % 10000 + 1;
        numero.push_back(num);
    }
    return numero;
} 
int main(int argc, char** argv){

    std::ofstream file;
    KDTreeR2<3>* arbol = new KDTreeR2<3>();
    KDTreeR<3>* arbol2 = new KDTreeR<3>();
    std::vector<float> punto;
    std::vector<std::vector<float>> numeros;
    int MAX_NUM = (argc > 1)? atoi(argv[1]):1000;
    file.open("thegame.txt", std::ios_base::app);
    file << "\n///////////////////////////////////////////" << endl;


    vector<vector<float>> vectorcito {{42, 8468, 6335},
{6501, 9170, 5725},
{1479, 9359, 6963},
{4465, 5706, 8146},
{3282, 6828, 9962},
{492, 2996, 1943},
{4828, 5437, 2392},
{4605, 3903, 154},
{293, 2383, 7422},
{8717, 9719, 9896},
{5448, 1727, 4772},
{1539, 1870, 9913},
{5668, 6300, 7036},
{9895, 8704, 3812},
{1323, 334, 7674},
{4665, 5142, 7712},
{8254, 6869, 5548},
{7645, 2663, 2758},
{38, 2860, 8724},
{9742, 7530, 779},
{2317, 3036, 2191},
{1843, 289, 107},
{9041, 8943, 9265}};



    for(int i=0 ; i<23 ; i++){
        punto = vectorcito[i];
        file << "{" << punto[0] << ", " << punto[1] << ", " << punto[2] << "}," << endl;
        numeros.push_back(punto);
        arbol->insertar(punto);
        arbol->rangoHijos();
        arbol2->insertar(punto);
    }
    //cout << "the game";
    //arbol->toJson();
    //cout << "the game";
    //arbol->mostrarArbol();

    //Se busca el último punto insertado
    for(auto num : vectorcito){
        auto busqueda = arbol->buscar(num);
        if(busqueda == nullptr){
            cout << "1not found (" << num[0] << ", " << num[1] << ", " << num[2] << ")\n"; 
        }
        auto busqueda2 = arbol2->buscar(num);
        if(busqueda2 == nullptr){
            cout << "2not found (" << num[0] << ", " << num[1] << ", " << num[2] << ")\n"; 
        }
    }

    //arbol->mostrarArbol();
    cout << arbol->profundidad() << endl;
    arbol->toJson();
    cout << arbol2->profundidad() << endl;
    
    

    return 0;
}                                                