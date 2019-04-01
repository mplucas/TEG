#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    vector<int> f;
    vector<int> pe;
    vector<int> ps;
    vector<int> l;
    int startNode;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readTEG( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe vertice de origem: ";
    cin >> startNode;

    cout << endl << "DFS -------------------------------------------------- " << endl;
    f = graphDFS( *g, startNode, pe, ps );
    cout << "PE(v): ";
  	showVector( pe );
  	cout << endl;
  	cout << "PS(v): ";
  	showVector( ps );
  	cout << endl;

    cout << endl << "BFS -------------------------------------------------- " << endl;
    f = graphBFS( *g, startNode, l );

    return 0;

}
