#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <ctime>
#include <fstream>
#include <random>
#define VERSION 1.0
#define FILENAME "test.csv"
#include "Argument_helper/Argument_helper.h"

using namespace std;
using namespace dsr;

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

bool generaDatosDist(string filename, int MAX_NUM, int DIM, float RANGE_MIN, float RANGE_MAX, bool ordenado){
    // Para distribución uniforme
    std::default_random_engine generator(time(NULL));
    std::uniform_real_distribution<double> distribution(RANGE_MIN,RANGE_MAX);
    std::ofstream file;
    std::ofstream filehpp;
    file.open(filename);
    filehpp.open("vars.hpp");

    filehpp <<  "#ifndef NUMERILLOS" << endl;
    filehpp <<  "#include<iostream>" << endl;
    filehpp <<  "#include<vector>" << endl;
    filehpp << "#define MAX_NUM " << MAX_NUM << endl;
    filehpp << "#define DIM " << DIM << endl << endl;
    filehpp << "#endif";
    
    for(int i=0; i<MAX_NUM ; i++){

        bool coma = false;
        for(int j=0 ; j<DIM ; j++){
            double numero = distribution(generator);

            if(coma){
                file << ",";
            }
            file << numero;
            coma = true;
            
        }
        file << endl;
    }

    return true;
}

bool generaDatos3Dist(string filename, int MAX_NUM, bool ordenado){
    // Para distribución uniforme
    std::default_random_engine generator(time(NULL));
    std::uniform_real_distribution<double> distribution(0,0.1f);
    std::uniform_real_distribution<double> distribution2(0,1);
    std::uniform_real_distribution<double> distribution3(0,10);
    std::ofstream file;
    std::ofstream filehpp;
    file.open(filename);
    filehpp.open("vars.hpp");

    filehpp <<  "#ifndef NUMERILLOS" << endl;
    filehpp <<  "#include<iostream>" << endl;
    filehpp <<  "#include<vector>" << endl;
    filehpp << "#define MAX_NUM " << MAX_NUM << endl;
    filehpp << "#define DIM " << 2 << endl << endl;
    filehpp << "#endif";
    
    for(int i=0; i<MAX_NUM ; i++){

        bool coma = false;
        
        double numero = distribution(generator);

        if(coma){
            file << ",";
        }
        file << numero;
        coma = true;
        
        numero = distribution2(generator);

        if(coma){
            file << ",";
        }
        file << numero;
        coma = true;

        numero = distribution3(generator);

        if(coma){
            file << ",";
        }
        file << numero;
        coma = true;
            
        file << endl;
    }

    return true;
}

int main(int argc, char* argv[]){
    int MAX_NUM = 10;
    int DIM = 2;
    double RANGE_MIN = 0;
    double RANGE_MAX = 1;
    string method = "uniform";
    int ordenado = 0;

    dsr::Argument_helper ah;
    ah.new_named_int('m', "maxnum", "MAX_NUM", "Cantidad de puntos a generar", MAX_NUM);
    ah.new_named_int('d', "dim", "DIM", "Cantidad de dimensiones por punto", DIM);
    ah.new_named_string('M', "method", "METHOD", "metodo a usar (uniform)", method);
    ah.new_named_int('o', "ordenado", "ORD", "si se genera ordenado (0 false, 1 true)", ordenado);
    ah.new_named_double('r', "range-min", "RMIN", "valor minimo a generar", RANGE_MIN);
    ah.new_named_double('R', "range-max", "RMAX", "valor maximo a generar", RANGE_MAX);
    ARGUMENT_HELPER_BASICS(ah);
    ah.set_description("Programa para generar puntos");
    ah.set_author("Alen figueroa, Javier peña; alen.figueroa.m@mail.pucv.cl, javier.pena.r@mail.pucv.cl");
    
    ah.process(argc, argv);
    if(method.compare("uniform") == 0){
        generaDatosDist(FILENAME, MAX_NUM, DIM, RANGE_MIN, RANGE_MAX, (ordenado != 0));
        return 0;
    }
    if(method.compare("normal") == 0){
        generaDatosDist(FILENAME, MAX_NUM, DIM, 0.0, 1, (ordenado != 0));
        return 0;
    }
    if(method.compare("3dist") == 0){
        generaDatos3Dist(FILENAME, MAX_NUM, (ordenado != 0));
        return 0;
    }
    cout << "Metodo incorrecto" << endl;
    return 0;
}