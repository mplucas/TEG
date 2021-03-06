#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readGraph( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl;
    if( checkEulerianGraph( *g ) ){
        cout << "O grafo eh Euleriano!";
    }else{
        cout << "O grafo nao eh Euleriano!";
    }

    return 0;

}
