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
	showNodes( g->nodes );
    cout << endl;
    g->adjacentMatrix();
    cout << endl;
    g->incidentMatrix();

    return 0;
}
