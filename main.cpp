#include "libghelli.h"
#include <bits/stdc++.h>
using namespace std;

//compilar: g++ -std=c++11 libghelli.h main.cpp -w
int main()
{

    Graph g;

	g.setNodes( readGasp() );

	showNodes( g.nodes );

    cout << endl;

    g.adjacentMatrix();

    cout << endl;

    g.incidentMatrix();

    return 0;
}
