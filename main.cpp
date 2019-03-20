#include "libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 libghelli.h main.cpp -w
int main()
{

    Graph* g = NULL;
    char cDirected;
    bool bDirected;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readGasp( "grafo.txt" ), bDirected );
    
    cout << endl;
	printGraph( *g );
    cout << endl;
	cout << "Matriz Adjacencia:" << endl;
    printMatrix( g->adjacentMatrix );
    cout << endl;
    cout << "Matriz Incidencia:" << endl;
    printMatrix( g->incidentMatrix );
    cout << endl;
    printNodesDegrees( *g );
    cout << endl << "Remove 2" << endl << endl;
    g->removeNode( 2 );
    printGraph( *g );
    cout << endl;
	cout << "Matriz Adjacencia:" << endl;
    printMatrix( g->adjacentMatrix );
    cout << endl;
    cout << "Matriz Incidencia:" << endl;
    printMatrix( g->incidentMatrix );
    cout << endl;
    printNodesDegrees( *g );

    return 0;
}
