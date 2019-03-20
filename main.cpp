#include "libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 libghelli.h main.cpp -w
int main()
{

    Graph* g = NULL;
    char cDirected;
    bool bDirected;
    int option = -1;
    int nodeRemoved;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readGasp( "grafo.txt" ), bDirected );

    do{

      printGraphInfo( *g );

      cout << endl << "O que voce deseja fazer?" << endl;
      cout << "0 - sair" << endl << "1 - remover um vertice" << endl;
      cin >> option;

      switch ( option ) {

        case 0:

          cout << "Programa encerrado";
          break;

        case 1:

          cout << "Informe o nó a ser retirado: ";
          cin >> nodeRemoved;
          g->removeNodeById( nodeRemoved );
          break;

        default:
          cout << "Operacao invalida!";
          break;

      }

    }while( option != 0 );

    return 0;
}
