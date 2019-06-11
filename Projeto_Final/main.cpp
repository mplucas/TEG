#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    vector<int> f;
    vector<int> pe;
    vector<int> ps;
    vector<int> l;
    vector<int> father;
  	vector<int> level;
  	vector<int> brother;
  	vector<int> cousin;
  	vector<int> uncle;
    int startNode;
    int i;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readGraph( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe vertice de origem: ";
    cin >> startNode;

    cout << endl << "DFS -------------------------------------------------- " << endl;
    cout << "Vertice:";
    for( i = 1; i <= g->numNodes; i++ ){
      cout << " " << i;
    }
    f = graphDFS( *g, startNode, pe, ps );
    cout << endl << "--------------------------------------------------" << endl;
    cout << "PE(v)  : ";
  	showVector( pe );
  	cout << endl;
  	cout << "PS(v)  : ";
  	showVector( ps );
  	cout << endl;

    cout << endl << "BFS -------------------------------------------------- " << endl;
    cout << "Vertice:";
    for( i = 1; i <= g->numNodes; i++ ){
      cout << " " << i;
    }
    f = graphBFS( *g, startNode, l, father, level, brother, cousin, uncle );
    cout << endl << "--------------------------------------------------" << endl;
    cout << "F      : ";
  	showVector( f );
  	cout << endl;
    cout << "L(v)   : ";
  	showVector( l );
  	cout << endl;
  	cout << "pai    : ";
  	showVector( father );
  	cout << endl;
  	cout << "nivel  : ";
  	showVector( level );
  	cout << endl;
  	cout << "irmao  : ";
  	showVector( brother );
  	cout << endl;
  	cout << "primo  : ";
  	showVector( cousin );
  	cout << endl;
  	cout << "tio    : ";
  	showVector( uncle );
  	cout << endl;

    return 0;

}
