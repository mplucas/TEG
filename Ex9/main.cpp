#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    vector<int> f;
    int startNode;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readTEG( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe vertice de origem: ";
    cin >> startNode;
    f = graphBFS( g, startNode );
    cout << endl << "Vetor da árvore geradora: " << endl;
    showVector( f );

    return 0;

}
