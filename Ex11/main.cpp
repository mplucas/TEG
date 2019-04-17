#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;

    cout << "O grafo eh considerado direcionado!" << endl;
    g = new Graph( readWeightedGraph( "grafo.txt" ), true );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printWeightedGraph( *g );
    cout << "------------------------------------------------------ " << endl << endl;

    return 0;

}
