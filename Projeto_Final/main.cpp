#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    int idNodeOri;
    int idNodeDes;
    int maxFlux;
    list<vector<int>> cutEdges;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readWeightedGraph( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe vertice de origem: ";
    cin >> idNodeOri;
    cout << "Informe vertice de destino: ";
    cin >> idNodeDes;
    maxFlux = calcFordFulkerson( *g, idNodeOri, idNodeDes, cutEdges );

    if( !cutEdges.empty() ){
      
      cout << endl << "Arestas para corte:" << endl;
      for( auto edge:cutEdges ){
        cout << "- " << edge[0] << " --> " << edge[1] << ", peso: " << edge[2] << endl;
      }
      cout << endl << "Fluxo máximo: " << maxFlux << endl;

    }else{
      cout << endl << "Não há arestas para serem cortadas, pois os vértices informados não são conexos!!" << endl;
    }

    return 0;

}
