#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

    Graph* g = NULL;
    char cDirected;
    bool bDirected;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readGasp( "grafo.txt" ), bDirected );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraph( *g );
    cout << "------------------------------------------------------ " << endl;
    if( check2PartGraph( *g ) ){
      cout << "O grafo eh bipartido!";
    }else{
      cout << "O grafo nao eh bipartido!";
    }

    return 0;
}
