#include <bits/stdc++.h>

#include "libghelli.h"

// Funcao para dividir uma string em uma lista de inteiros, sendo que a string tem seus valores inteiros separados por barra de espaço.
list<int> explodeTEG( string s ){

	list<int>    result;
	stringstream ss( s );
	int          value;

	while( ss >> value ){
		result.push_back( value );
	}

	return result;

}

// função para ambientes com c++ de versão antiga
// int stoi( string s ){

//     // object from the class stringstream
//     stringstream geek(s);

//     // The object has the value 12345 and stream
//     // it to the integer x
//     int x = 0;
//     geek >> x;

//     return x;
// }

// ./a.out < grafo.txt
list<Node> readGraph( string fileName ){

	string     line;
	list<Node> nodes;
	Node       node;
	int        lineCount = 1;
	ifstream   file( fileName );
	istream&   s = file;

	while( getline( s, line ) ){

		node.setEdges( explodeTEG( line ) );
		node.setId( lineCount++ );
		nodes.push_back( node );

	}

	return nodes;

}

void readWE( string v, vector<int>& we ){

	int div;

	we.clear();
	div = v.find( "," );
	we.push_back( stoi( v.substr( 0, div ) ) );
	we.push_back( stoi( v.substr( div + 1 ) ) );

}

void readWeightedEdges( string s, list<int>& edges, list<int>& edgeWeight ){

	list<int>    result;
	stringstream ss( s );
	string       value;
	vector<int>  weightedEdge;

	while( ss >> value ){
		readWE( value, weightedEdge );
		edges.push_back( weightedEdge[0] );
		edgeWeight.push_back( weightedEdge[1] );
	}

}

// ./a.out < grafo.txt
list<Node> readWeightedGraph( string fileName ){

	string     line;
	list<Node> nodes;
	Node       node;
	int        lineCount = 1;
	ifstream   file( fileName );
	istream&   s = file;

	while( getline( s, line ) ){

		readWeightedEdges( line, node.edges, node.edgeWeight );
		node.setId( lineCount++ );
		nodes.push_back( node );
		node.edges.clear();
		node.edgeWeight.clear();

	}

	return nodes;

}

//function for printing the elements in a list
void showList(list <int> g){

    list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << *it << " ";

}

//function for printing the elements in a list
void showVector(vector <int> g){

    vector <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << *it << " ";

}

// Função para printar matriz em tela
void printMatrix( vector<vector<int>> auxMatrix ){

	unsigned int i, j;

	for( i = 0; i < auxMatrix.size(); i++ ){
		for( j = 0; j < auxMatrix[i].size(); j++){

			cout << auxMatrix[i][j] << " ";

		}

		cout << endl;

	}

}

// Função para printar o grafo
void printGraph( Graph g ){

	cout << "Grafo:" << endl;

	for (auto nodeList:g.nodes){

		cout << nodeList.id << " : ";
		for (auto node:nodeList.edges) cout << node << " ";
		cout << endl;

	}

}

// Função para printar o grafo ponderado
void printWeightedGraph( Graph g ){

	unsigned int i;
	list<int> :: iterator itEdge;
	list<int> :: iterator itEdgeWeight;

	cout << "Grafo:" << endl;

	for (auto nodeList:g.nodes){

		itEdge       = nodeList.edges.begin();
		itEdgeWeight = nodeList.edgeWeight.begin();
		cout << nodeList.id << " : ";

		for( i = 0; i < nodeList.edges.size(); i++ ){

				cout << *itEdge << "," << *itEdgeWeight << " ";
				itEdge++;
				itEdgeWeight++;

		}
		cout << endl;

	}

}

// Fução para printar os graus de cada nós
void printNodesDegrees( Graph g ){

	cout << "Graus dos vertices:" << endl;

    for (auto node:g.nodes){

		cout << node.id << " : " << node.degree;
		cout << endl;

	}

}

// Função para mostrar as principais informacoes do Grafo
void printGraphInfo( Graph g ){

	cout << endl;
	printGraph( g );
	cout << endl;
	cout << "Matriz Adjacencia:" << endl;
	printMatrix( g.adjacentMatrix );
	cout << endl;
	cout << "Matriz Incidencia:" << endl;
	printMatrix( g.incidentMatrix );
	cout << endl;
	printNodesDegrees( g );
	cout << endl;

}

// Função para mostrar as principais informacoes do Grafo ponderado
void printWGraphInfo( Graph g ){

	cout << endl;
	printWeightedGraph( g );
	cout << endl;
	cout << "Matriz Adjacencia:" << endl;
	printMatrix( g.adjacentMatrix );
	cout << endl;
	cout << "Matriz Adjacencia com pesos:" << endl;
	printMatrix( g.weightMatrix );
	cout << endl;
	cout << "Matriz Incidencia:" << endl;
	printMatrix( g.incidentMatrix );
	cout << endl;
	printNodesDegrees( g );
	cout << endl;

}

//Funcao para pintar nós
bool paintNodes( int idNode, Graph g, list<int>& currentColor, list<int>& inverseColor ){

	list<int> :: iterator itColor;
	int i;

	// verifica se o vertice ja foi pintado da cor atual
	itColor = find( currentColor.begin(), currentColor.end(), idNode );
	if ( itColor != currentColor.end() ){
		return true;
	}

	// verifica se o vertice ja não está pintado da cor oposta
	itColor = find( inverseColor.begin(), inverseColor.end(), idNode );

	if ( itColor == inverseColor.end() ){

		currentColor.push_back( idNode );

		for( i = 0; i < g.numNodes; i++ ){

			if( ( g.adjacentMatrix[ idNode ][ i ] != 0 ) && ( idNode != i ) ){
				if( !paintNodes( i, g, inverseColor, currentColor ) ){
					return false;
				}
			}

		}

	}else
		return false;

	return true;

}

// Função para verificar se o grafo é bipartdo ou não
bool check2PartGraph( Graph g ){

	list<int> whiteNodes;
	list<int> blackNodes;

	return paintNodes( 0, g, whiteNodes, blackNodes );

}

// verifica um vertice e retira todos os vertices de seu componente da lista de vertices notCheckedList
void removeComponent( int idNode, Graph g, list<int>& notCheckedList ){

	list<int>  :: iterator itNotChecked;
	bool removedNow = false;
	int i;

	// verifica se o vertice ja foi percorrido, se não foi o remove da lista notCheckedList e acessa outros vertices por suas arestas
	itNotChecked = find( notCheckedList.begin(), notCheckedList.end(), idNode );
	if ( itNotChecked != notCheckedList.end() ){

		notCheckedList.remove( idNode );
		removedNow = true;

	}

	if( removedNow ){

		// verifica se vertices conectados ja foram percorridos
		for( i = 0; i < g.numNodes; i++ ){

			if( ( g.adjacentMatrix[ idNode ][ i ] != 0 ) && ( idNode != i ) ){
				removeComponent( i, g, notCheckedList );
			}

		}

	}

}

// verifica se um grafo é conexo, retorna true ou false e o numero de componentes caso não conexo.
bool checkConnectedGraph( Graph g, int& numComponents ){

	list<int> nodeList;
	bool connected = false;

	numComponents = 0;

	for (auto node:g.nodes){

		// id - 1 para que a matriz adjacente seja acessada corretamente
		nodeList.push_back( node.id - 1 );

	}

	while( !nodeList.empty() ){

		removeComponent( nodeList.front(), g, nodeList );
		numComponents++;

	}

	if( numComponents == 1 ){
		connected = true;
	}

	return connected;

}

// Funcao para verificar se a aresta é uma ponte
bool edgeIsBridge( vector<int> edge, Graph g ){

	int numComponents;

	// retira a aresta e testa se fez o grafo ser desconexo.
	// - 1 para acessar corretamente as posicoes da matriz
	g.adjacentMatrix[ edge.front() - 1 ][ edge.back() - 1 ] = 0;
	g.adjacentMatrix[ edge.back() - 1 ][ edge.front() - 1 ] = 0;

	return !checkConnectedGraph( g, numComponents );

}

// recebe uma linha da matriz incidencia e retorna um vetor com o vertice origem na primeira posicao e o vertice destino na segunda posicao
vector<int> readEdgeIncMatrix( vector<int> incMatrixLine ){

	unsigned int i;
	vector<int> edge;

	for( i = 0; i < incMatrixLine.size(); i++ ){

		if( incMatrixLine[ i ] == 1 ){
			edge.push_back( i + 1 );
		}else if( incMatrixLine[ i ] == 2 ){
			edge.push_back( i + 1 );
			edge.push_back( i + 1 );
			break;
		}

	}

	return edge;

}

// Funcao para escolher a aresta correta para o algoritmo de fleury
vector<int> pickEdgeFleury( int currentNode, Graph g, int& linMatIncident, bool& deleteNode ){

	unsigned int i;
	vector<int> edge;	/* [0] - vertice de origem
						 * [1] - vertice de linMatIncidentdestino
						 * [2] - 0 nao eh ponte, 1 é ponte
						 * [3] - linha da matriz incidencia */
	list<vector<int>> possibleEdges;
	vector<int> choosenEdge;

	// Variavel que retorna se deve ou não retirar o vertice do grafo visto que esse ficara desconexo apos a
	// escolha e remocao da aresta em questao. Necessario retirar o vertice para que a verificacao da funcao
	// de grafo conexo funcione corretamente.
	deleteNode = false;
	choosenEdge.assign( 4, -1 );

	// levanta as arestas possiveis a serem acessadas
	for( i = 0; i < g.incidentMatrix.size(); i++ ){

		edge = readEdgeIncMatrix( g.incidentMatrix[ i ] );

		if( edge.front() == currentNode ){

			// adiciona validacao referente a aresta ser ponte
			if( edgeIsBridge( edge, g ) ){
				edge.push_back( 1 );
			}else{
				edge.push_back( 0 );
			}

			// adiciona linha da matriz incidencia
			edge.push_back( i );
			possibleEdges.push_back( edge );

		}else if( edge.back() == currentNode ){

			reverse( edge.begin(), edge.end() );

			// adiciona validacao referente a aresta ser ponte
			if( edgeIsBridge( edge, g ) ){
				edge.push_back( 1 );
			}else{
				edge.push_back( 0 );
			}

			// adiciona linha da matriz incidencia
			edge.push_back( i );
			possibleEdges.push_back( edge );

		}

	}

	if( possibleEdges.size() == 1 ){

		choosenEdge = possibleEdges.front();

		// altera variavel deleteNode, pois sera necessario remover o node de origem do grafo, visto que ficara desconexo do grafo
		if( choosenEdge[2] == 1 ){
			deleteNode = true;
		}

	}else{

		for ( auto pEdge:possibleEdges ){

			if( pEdge[2] == 0 ){
				choosenEdge = pEdge;
				break;
			}

		}

	}

	// retira linha da matriz incidencia de edge
	linMatIncident = choosenEdge.back();
	choosenEdge.pop_back();

	// retira validacao se é ponte ou nao de edge
	choosenEdge.pop_back();

	return choosenEdge;

}

// Funcao para printar a edge
void printEdge( vector<int> edge ){

	cout << edge.front() << " --> " << edge.back() << endl;

}

// Funcao que verifica se um grafo é euleriano pelo algoritmo Fleury
bool checkEulerianGraph( Graph g ){

	int firstNodeId;
	int lastNodeId;
	int currentNode;
	vector<vector<int>> :: iterator itEdge;
	int numComponents;
	vector<int> edge;
	int linMatIncident;
	bool deleteNode;

	// verifica se o grafo é conexo
	if( !checkConnectedGraph( g, numComponents ) ){
		cout << "Grafo desconexo!" << endl;
		return false;
	}

	// le e remove arestas da matriz incidencia
	firstNodeId = 1;
	currentNode = firstNodeId;

	while( ( currentNode != -1 ) && ( !g.incidentMatrix.empty() ) ){

		cout << "Vertice atual: " << currentNode << endl;
		edge = pickEdgeFleury( currentNode, g, linMatIncident, deleteNode );
		currentNode = edge.back();

		if( currentNode != -1 ){

			g.removeEdge( edge );
			cout << "Aresta escolhida e removida: ";
			printEdge( edge );
			lastNodeId = currentNode;
			//	verifica se a aresta removida nao e um laco
			if( ( deleteNode ) && ( currentNode != firstNodeId ) ){

				g.removeNodeById( edge.front() );
				cout << "Vertice " << edge.front() << " removido pois ficou desconexo.";

                if( edge.front() == firstNodeId ){
					cout << endl << "Vertice inicial desconexo, logo nao ha como retornar a ele." << endl << endl;
					break;
				}

				cout << " Rearranjado ids do grafo." << endl;

				// rearranjo dos ids dos vertices caso um seja deletado
				if( currentNode > edge.front() ){
					currentNode--;
				}

			}

			cout << endl;

		}

		// Para visualizar melhor a mudanca no grafo
		printGraph( g );
		cout << endl;

	}

	cout << "Vertice inicial: " << firstNodeId << endl;
	cout << "Vertice final: " << lastNodeId << endl;
	cout << "Arestas restantes: " << g.incidentMatrix.size() << endl;

	return ( ( lastNodeId == firstNodeId ) && ( g.incidentMatrix.empty() ) );

}

// Funcao para retornar uma lista com os verices conectados ao vertice idNode, isso porque
// pela estrutura de nodes as vezes nao se consegue rastrear isso se a aresta nao esta
// saindo do vertico idNode.
vector<int> getRealConnections( int idNode, Graph g ){

	vector<int> connections;
	unsigned int i;

	for( i = 0; i < g.adjacentMatrix[ idNode - 1 ].size(); i++ ){
		if( g.adjacentMatrix[ idNode - 1 ][ i ] != 0 ){
			connections.push_back( i + 1 );
		}
	}

	return connections;

}

// Parte recursiva da funcao do DFS
void readDFS( Graph g, int idNode, int& t, vector<int>& pe, vector<int>& ps, vector<int>& f ){

	vector<int> :: iterator itF;
	vector<int> edges;

	itF = find( f.begin(), f.end(), idNode );

	// se nao encontrou idNode em f.
	if ( itF == f.end() ){

		f.push_back( idNode );
		// empilha
		pe[ idNode - 1 ] = ++t;
		edges = getRealConnections( idNode, g );

		for( auto idEdge:edges ){
			readDFS( g, idEdge, t, pe, ps, f );
		}

		// desempilha pela recursividade visto que todos seus filhos ja foram empilhados e processados
		ps[ idNode - 1 ] = ++t;

	}

}

// Funcao para calcular os vetores PE e PS da arvore geradora DFS de um grafo.
// Tambem retorna um vetor f com a ordem dos vertices visitados.
vector<int> graphDFS( Graph g, int startNode, vector<int>& pe, vector<int>& ps ){

	vector<int> f;
	int t = 0;

	pe.assign( g.numNodes, 0 );
	ps.assign( g.numNodes, 0 );
	readDFS( g, startNode, t, pe, ps, f );

	return f;

}

// Parte recursiva da funcao do BFS
void readBFS( Graph g, int& t, vector<int>& l, list<int>& f, vector<int>& fshow, vector<int>& father, vector<int>& level, vector<int>& brother, vector<int>& cousin, vector<int>& uncle ){

	vector<int> edges;
	int idNode;

	// marca vertice como processado
	idNode = f.front();
	fshow.push_back( idNode );
	f.pop_front();

	edges = getRealConnections( idNode, g );

	for( auto idEdge:edges ){

		if( l[ idEdge - 1 ] == 0 ){

			father[ idEdge - 1 ] = idNode;
			level[ idEdge - 1 ] = level[ idNode - 1 ] + 1;
			f.push_back( idEdge );
			l[ idEdge - 1 ] = ++t;

		}else if( level[ idEdge - 1 ] == level[ idNode - 1 ] ){

			if( father[ idEdge - 1 ] == father[ idNode - 1 ] ){
				brother[ idEdge - 1 ] = idNode;
				brother[ idNode - 1 ] = idEdge;
			}else{
				cousin[ idEdge - 1 ] = idNode;
				cousin[ idNode - 1 ] = idEdge;
			}

		}else if( level[ idEdge - 1 ] == level[ idNode - 1 ] + 1 ){
			uncle[ idEdge - 1 ] = idNode;
			uncle[ idNode - 1 ] = idEdge;
		}

	}

}

// Funcao para calcular os vetor L da arvore geradora DFS de um grafo.
// Tambem retorna um vetor f com a ordem dos vertices visitados.
vector<int> graphBFS( Graph g, int startNode, vector<int>& l, vector<int>& father, vector<int>& level, vector<int>& brother, vector<int>& cousin, vector<int>& uncle ){

	list<int> f;
	vector<int> fshow;
	int t = 0;

	l.assign( g.numNodes, 0 );
	father.assign( g.numNodes, 0 );
	level.assign( g.numNodes, 0 );
	brother.assign( g.numNodes, 0 );
	cousin.assign( g.numNodes, 0 );
	uncle.assign( g.numNodes, 0 );
	// Vertice father
	f.push_back( startNode );
	l[ startNode - 1 ] = ++t;

	while( !f.empty() ){
		readBFS( g, t, l, f, fshow, father, level, brother, cousin, uncle );
	}

	return fshow;

}

// Algoritmo de DIJKSTRA
vector<vector<int>> dijkstraCalc( Graph g, int idNode ){



}
