#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

  Graph* g = NULL;
  int numComponents;

  cout << "O grafo eh considerado nao direcionado!" << endl;
  g = new Graph( readGraph( "grafo.txt" ), false );

  cout << "GRAFO ATUAL------------------------------------------- " << endl;
  printGraph( *g );
  cout << "------------------------------------------------------ " << endl;
  if( checkConnectedGraph( *g, numComponents ) ){
    cout << "O grafo eh conexo!";
  }else{
    cout << "O grafo nao eh conexo e possui " << numComponents << " componentes!";
  }

  return 0;
}
