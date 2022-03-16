#include "floydwarshall.hpp"

using namespace std;

/*
███████╗██╗   ██╗███╗   ██╗ ██████╗ ██████╗ ███████╗███████╗
██╔════╝██║   ██║████╗  ██║██╔════╝██╔═══██╗██╔════╝██╔════╝
█████╗  ██║   ██║██╔██╗ ██║██║     ██║   ██║█████╗  ███████╗
██╔══╝  ██║   ██║██║╚██╗██║██║     ██║   ██║██╔══╝  ╚════██║
██║     ╚██████╔╝██║ ╚████║╚██████╗╚██████╔╝███████╗███████║
╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚══════╝╚══════╝
*/

void printFinal(Grafo* grafo){
    for (int i = 0; i < grafo->qntd_vertices; i++){
        for (int j = 0; j < grafo->qntd_vertices; j++){
            if (grafo->matriz[i][j].peso == (numeric_limits<double>::max() / 3.0)){
                cout << "-";
                if (j != grafo->qntd_vertices - 1){
                    cout << " ";
                }
            }
            else{
                cout << grafo->matriz[i][j].peso;
                if (j != grafo->qntd_vertices - 1){
                    cout << " ";
                }
            }
        }
        cout << "\n";
    }
}

/*
 █████╗ ██████╗ ███████╗███████╗████████╗ █████╗ 
██╔══██╗██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗
███████║██████╔╝█████╗  ███████╗   ██║   ███████║
██╔══██║██╔══██╗██╔══╝  ╚════██║   ██║   ██╔══██║
██║  ██║██║  ██║███████╗███████║   ██║   ██║  ██║
╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝
*/

Aresta::Aresta(int id, int origem, int destino, double peso){

    this->id = id;
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
}
Aresta::~Aresta(){}

void Aresta::printInfo(){
    cout << "--------- Aresta ---------\n";
    cout << "Id         : " << this->id << "\n" ;
    cout << "Origem     : " << this->origem << "\n" ;
    cout << "Destino    : " << this->destino << "\n" ;
    cout << "Peso       : " << this->peso << "\n\n" ;
}

/*
██╗   ██╗███████╗██████╗ ████████╗██╗ ██████╗███████╗
██║   ██║██╔════╝██╔══██╗╚══██╔══╝██║██╔════╝██╔════╝
██║   ██║█████╗  ██████╔╝   ██║   ██║██║     █████╗  
╚██╗ ██╔╝██╔══╝  ██╔══██╗   ██║   ██║██║     ██╔══╝  
 ╚████╔╝ ███████╗██║  ██║   ██║   ██║╚██████╗███████╗
  ╚═══╝  ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝╚══════╝
*/

Vertice::Vertice(int id){
    this->id = id;
}
Vertice::~Vertice(){}

void Vertice::printInfo(){
    cout << "--------- Vertice ---------\n";
    cout << "Id                            : " << this->id << "\n" ;
}

/*
 ██████╗███████╗██╗     ██╗   ██╗██╗      █████╗ 
██╔════╝██╔════╝██║     ██║   ██║██║     ██╔══██╗
██║     █████╗  ██║     ██║   ██║██║     ███████║
██║     ██╔══╝  ██║     ██║   ██║██║     ██╔══██║
╚██████╗███████╗███████╗╚██████╔╝███████╗██║  ██║
 ╚═════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
*/

Celula::Celula(bool status, double peso):status(status), peso(peso){}
Celula::~Celula(){}

/*
 ██████╗ ██████╗  █████╗ ███████╗ ██████╗ 
██╔════╝ ██╔══██╗██╔══██╗██╔════╝██╔═══██╗
██║  ███╗██████╔╝███████║█████╗  ██║   ██║
██║   ██║██╔══██╗██╔══██║██╔══╝  ██║   ██║
╚██████╔╝██║  ██║██║  ██║██║     ╚██████╔╝
 ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝      ╚═════╝ 
*/

Grafo::Grafo(){}
Grafo::Grafo(int qntd_vertices, int qntd_arestas):qntd_vertices(qntd_vertices), qntd_arestas(qntd_arestas){}
Grafo::~Grafo(){}

void Grafo::inicializaGrafo(){

    // Leitura dos dados iniciais
    int qntd_vertices, qntd_arestas;

    cin >> qntd_vertices >> qntd_arestas;

    this->qntd_vertices = qntd_vertices;
    this->qntd_arestas = qntd_arestas;

    // Lendo vertices
    for (int i = 1; i <= this->qntd_vertices; i++){
        Vertice v(i);

        this->vertices.push_back(v);

        vector<Celula> vet;
        this->matriz.push_back(vet);
        for (int j = 1; j <= this->qntd_vertices; j++){
            this->matriz[i - 1].push_back(Celula());
        }
    }

    // Lendo arestas e criando listas de adjacencia
    int origem, destino;
    double peso;

    for (int i = 1; i <= this->qntd_arestas; i++){
        cin >> origem >> destino >> peso;
        
        Aresta a = Aresta(i, origem, destino, peso);
        this->arestas.push_back(a);

        // Preenchendo matriz com o peso correspondente da aresta
        this->matriz[origem - 1][destino - 1].status = true;
        this->matriz[origem - 1][destino - 1].peso = peso;
    }

    //inicializando matriz de pesos
    for (int i = 1; i <= this->qntd_vertices; i++){
        for (int j = 1; j <= this->qntd_vertices; j++){
            if (i == j){
                this->matriz[i - 1][j - 1].peso = 0.0;
            }
            else{
                if (!this->matriz[i - 1][j - 1].status){
                    this->matriz[i - 1][j - 1].peso = (numeric_limits<double>::max() / 3.0);
                }
            }
        }
    }
}

void Grafo::floydWarshall(){
    for (int k = 0; k < this->qntd_vertices; k++){
        for (int i = 0; i < this->qntd_vertices; i++){
            for (int j = 0; j < this->qntd_vertices; j++){
                if (this->matriz[i][j].peso > this->matriz[i][k].peso + this->matriz[k][j].peso){
                    this->matriz[i][j].peso = this->matriz[i][k].peso + this->matriz[k][j].peso;
                }
            }
        }
    }
}

void Grafo::printInfo(){
    cout << "--------- Grafo ---------\n";
    cout << "Qntd vertices  : " << this->qntd_vertices << "\n" ;
    cout << "Qntd arestas   : " << this->qntd_vertices << "\n\n" ;

    for (int i = 0; i < this->qntd_vertices; i++){
        for (int j = 0; j < this->qntd_vertices; j++){
            if (this->matriz[i][j].peso == numeric_limits<double>::max() / 3.0){
                cout << "- ";
            }
            else{
                cout << this->matriz[i][j].peso << " ";
            }
        }
        cout << endl;
    }
}