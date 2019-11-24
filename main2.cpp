#include "KDTreeRange2.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace KDTreeRange2;
int main(int argc, char** argv){

    KDTreeR2<3>* arbol = new KDTreeR2<3>();
    std::vector<float> punto;
    punto.push_back(3);
    punto.push_back(2);
    punto.push_back(1);
    arbol->insertar(punto);

    return 0;
}                                                