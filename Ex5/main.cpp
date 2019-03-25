#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    int numComponents;
    char cDirected;
    bool bDirected;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readGasp( "grafo.txt" ), bDirected );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraph( *g );
    cout << "------------------------------------------------------ " << endl;
    if( checkEulerianGraph( *g ) ){
        cout << "O grafo eh Euleriano!";
    }else{
        cout << "O grafo nao eh Euleriano!";
    }

    cout << endl;

    return 0;

}
