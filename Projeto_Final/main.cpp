#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    setbuf( stdout, NULL );

    Graph* g = NULL;
    int idNodeOri;
    int idNodeDes;
    list<int> path;

    cout << "O grafo eh considerado nao direcionado!" << endl;
    g = new Graph( readWeightedGraph( "grafo.txt" ), false );

    cout << "GRAFO ATUAL------------------------------------------- " << endl;
    printGraphInfo( *g );
    cout << "------------------------------------------------------ " << endl << endl;
    cout << "Informe vertice de origem: ";
    cin >> idNodeOri;
    cout << "Informe vertice de destino: ";
    cin >> idNodeDes;
    path = findPathBetween( *g, idNodeOri, idNodeDes );

    if( !path.empty() ){
      cout << endl << "Caminho possível:" << endl;
      for( auto n:path ){
        cout << n << " - ";
      }
    }else{
      cout << endl << "Não há caminho!!" << endl;
    }

    return 0;

}
