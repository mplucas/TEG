#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    char cDirected;
    bool bDirected;
    int  startNode;
    vector<vector<int>> vectorsDij;
    list<Node> :: iterator itNode;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readWeightedGraph( "grafo.txt" ), bDirected );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printWGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe o nó de inicio para o algoritmo de DIJKSTRA: ";
    cin >> startNode;

    if( !g->getNodeById( startNode, itNode ) ){
      cout << "O vértice informado não existe no grafo!" << endl;
      return 0;
    }

    vectorsDij = dijkstraCalc( *g, startNode );
    printDij( vectorsDij );

    return 0;

}
