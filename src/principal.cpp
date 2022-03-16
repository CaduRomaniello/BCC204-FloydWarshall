#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "floydwarshall.hpp"

using namespace std;

int main(){

    // Criacao e inicializacao do grafo
    Grafo grafo = Grafo();
    grafo.inicializaGrafo();

    // FloydWarshall
    grafo.floydWarshall();

    // Print
    printFinal(&grafo);

    return 0;

}