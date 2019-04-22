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

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readWeightedGraph( "grafo.txt" ), bDirected );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printWGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;

    return 0;

}
