#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.h main.cpp -w
int main()
{

  Graph* g = NULL;

  cout << "O grafo eh considerado nao direcionado!" << endl;
  g = new Graph( readTEG( "grafo.txt" ), false );

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
