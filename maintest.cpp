
#include "csvRow.hpp"


//using namespace csv;
int main(){
    std::vector<std::vector<float>*>* numeros = csv::cargaNumeros("test.csv");
    for(auto vec : *numeros){
        for(auto numero : *vec){
            std::cout << numero << ", ";
        }
        std::cout << std::endl;
    }
    return 0;
}