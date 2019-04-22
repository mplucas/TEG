#include "../libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 ../libghelli.cpp main.cpp -Wall
int main()
{

    Graph* g = NULL;
    Graph gComp;
    char cDirected;
    bool bDirected;
    int option = -1;
    int nodeRemoved;

    cout << "O grafo eh direcionado? ( 'S' - Sim | 'N' - Não ): ";
    cin >> cDirected;
    bDirected = ( toupper( cDirected ) == 'S' );
    g = new Graph( readGraph( "grafo.txt" ), bDirected );

    do{

      cout << "GRAFO ATUAL------------------------------------------- " << endl;
      printGraphInfo( *g );
      cout << "------------------------------------------------------ " << endl;

      cout << endl << "O que voce deseja fazer?" << endl;
      cout << "0 - sair" << endl << "1 - remover um vertice" << endl;
      cout << "2 - gerar complemento" << endl;
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

        case 2:

          gComp = g->graphComplement();
          cout << "GRAFO COMPLEMENTAR-------------------------------- " << endl;
          printGraphInfo( gComp );
          cout << "-------------------------------------------------- " << endl;
          break;

        default:
          cout << "Operacao invalida!";
          break;

      }

    }while( option != 0 );

    return 0;
}
