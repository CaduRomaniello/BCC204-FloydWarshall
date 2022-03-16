#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <limits>

using namespace std;

class Aresta{
    public:

        //Atributos
        int id;
        int origem;
        int destino;
        double peso;

        //Metodos
        Aresta(int id = -1, int origem = -1, int destino = -1, double peso = -1.0);
        ~Aresta();

        void printInfo();
};

class Vertice{
    public:

        //Atributos
        int id;

        //Metodos
        Vertice(int id);
        ~Vertice();

        void printInfo();
};

class Celula{
    public:
        //Atributos
        bool status; // TRUE caso tenha aresta de i para j e FALSE caso nao exista
        double peso;

        //Metodos
        Celula(bool status = false, double peso = 0.0);
        ~Celula();
};

class Grafo{
    public:

        //Atributos
        int qntd_vertices;
        int qntd_arestas;
        vector<Vertice> vertices;
        vector<Aresta> arestas;
        vector<vector<Celula>> matriz;

        //Metodos
        Grafo();
        Grafo(int qntd_vertices, int qntd_arestas);
        ~Grafo();

        void inicializaGrafo();

        void floydWarshall();

        void printInfo();
};

void printFinal(Grafo* grafo);

#endif