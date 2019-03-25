#include <bits/stdc++.h>

// Classes

using namespace std;

class Node
{

	public:

	int       id;
	list<int> edges;
	int       degree;

	int getId(){
		return id;
	}

	void setId( int value ){
		id = value;
	}

	list<int> getEdges(){
		return edges;
	}

	void setEdges( list<int> values ){
		edges = values;
	}

};

class Graph
{

    public:

	int                 numNodes;
	int                 numEdges;
	bool                directed;
    list<Node>          nodes;
	vector<vector<int>> adjacentMatrix;
	vector<vector<int>> incidentMatrix;

	Graph(){

		list<Node> nodeList;

		setNodes( nodeList );
		setDirected( false );

	}

	Graph( list<Node> ns, bool d ){

		buildGraph( ns, d );

	}

	void buildGraph( list<Node> ns, bool d ){

		setNodes( ns );
		setDirected( d );

		calcAdjacentMatrix();
		calcIncidentMatrix();
		calcDegreeNodes();

	}

    list<Node> getNodes(){
        return nodes;
    }

    void setNodes( list<Node> ns ){

		list<Node>  :: iterator itNode;

		nodes    = ns;
		numNodes = ns.size();
		numEdges = 0;

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){

			numEdges += itNode->edges.size();

		}

    }

	bool getDirected(){
		return directed;
	}

	void setDirected( bool d ){
		directed = d;
	}

	// Função para retornar matriz dimensionada com todos os valores igual a 0
	vector<vector<int>> resizeMatrix( int lin, int col ){

		vector<vector<int>> auxMatrix;
		int i;

		auxMatrix.resize( lin );
		for ( i = 0 ; i < lin ; i++ )
   			auxMatrix[i].assign( col, 0 );

		return auxMatrix;

	}

	// Função para gerar a matriz adjacencia do grafo
	void calcAdjacentMatrix(){

		int i;

		list<Node> :: iterator itNode;
		list<int>  :: iterator itEdge;

		adjacentMatrix = resizeMatrix( numNodes, numNodes );

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){
			for( itEdge = itNode->edges.begin(); itEdge != itNode->edges.end(); itEdge++ ){

				adjacentMatrix[ itNode->id - 1 ][ *itEdge - 1 ]++;

				if( !directed ){
					adjacentMatrix[ *itEdge - 1 ][ itNode->id - 1 ]++;
				}

			}
		}

	}

	// Função para gerar a matriz incidencia do grafo
	void calcIncidentMatrix(){

		int idEdge = 0;

		list<Node> :: iterator itNode;
		list<int>  :: iterator itEdge;

		incidentMatrix = resizeMatrix( numEdges, numNodes );

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){
			for( itEdge = itNode->edges.begin(); itEdge != itNode->edges.end(); itEdge++ ){

				if( ( directed ) && ( itNode->id != *itEdge ) ){
					incidentMatrix[ idEdge ][ itNode->id - 1 ]--;
				}else{
					incidentMatrix[ idEdge ][ itNode->id - 1 ]++;
				}

				incidentMatrix[ idEdge ][ *itEdge - 1 ]++;
				idEdge++;

			}
		}

	}

	//Função para calcular os graus de cada nó
	void calcDegreeNodes(){

		int idNode;
		list<Node> :: iterator itNode;

		idNode = 0;

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){

			itNode->degree = accumulate( adjacentMatrix[ idNode ].begin(), adjacentMatrix[ idNode ].end(), 0 ) ;
			idNode++;

		}

	}

	//Função para retornar um nó do grafo
	bool getNodeById( int idNode, list<Node> :: iterator& itNode ){

		bool foundNode = false;

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){
			if( itNode->id == idNode ){
				foundNode = true;
				break;
			}
		}

		return foundNode;

	}

	//Função para retirar um nó do grafo
	void removeNodeById( int idNode ){

		list<Node> :: iterator itNode;
		list<int>  :: iterator itEdge;
		bool nodeIsRemoved = false;


		if( this->getNodeById( idNode, itNode ) ){

			nodes.erase( itNode );
			nodeIsRemoved = true;

		}


		// subtrai 1 dos indices de vertices maiores que o retirado para que as matrizes nao sejam afetadas
		if( nodeIsRemoved ){

			for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){

				if( itNode->id > idNode ){
					itNode->id = itNode->id - 1;
				}

				itNode->edges.remove( idNode );

				for( itEdge = itNode->edges.begin(); itEdge != itNode->edges.end(); itEdge++ ){

					if( *itEdge > idNode ){
						*itEdge = *itEdge - 1;
					}

				}

			}

		}

		buildGraph( nodes, directed );

	}

	// Funcao que retorna o complemento de um grafo.
	Graph graphComplement(){

		list<Node> complementNodes;
		list<int>  :: iterator itEdge;
		list<Node> :: iterator itNode;
		Node nodeAux;
		int idEdge;
		Graph* complementGraph = NULL;

		for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){

			nodeAux.id = itNode->id;
			nodeAux.edges.clear();
			itEdge = itNode->edges.begin();

			for( idEdge = 1; idEdge <= numNodes; idEdge++ ){

				if( idEdge != *itEdge ){
					nodeAux.edges.push_back( idEdge );
				}else{
					itEdge++;
				}

			}

			complementNodes.push_back( nodeAux );

		}

		complementGraph = new Graph( complementNodes, directed );

		return *complementGraph;

	}

	// Funçao para remover uma aresta do GRAFO.
	void removeEdge( vector<int> edge ){

		list<Node> :: iterator itNode;
		list<int>  :: iterator itEdge;
		
		this->getNodeById( edge.front(), itNode );

		itEdge = find( itNode->edges.begin(), itNode->edges.end(), edge.back() );

		if ( itEdge != itNode->edges.end() ){
			itNode->edges.remove( edge.back() );
		}else{
			
			this->getNodeById( edge.back(), itNode );
			itNode->edges.remove( edge.front() );

		}

		buildGraph( nodes, directed );

	}

};


// Functions

list<string> explode( string s, char delim );
list<int> explodeInt( string s, char delim );
list<int> explodeTEG( string s );
list<Node> readFile( string fileName );
list<Node> readTEG();
void showNodes( list <Node> g );
void printMatrix( vector<vector<int>> auxMatrix );
void printGraph( Graph g );
void printNodesDegrees( Graph g );
void printGraphInfo( Graph g );
bool paintNodes( int idNode, Graph g, list<int>& currentColor, list<int>& inverseColor );
bool check2PartGraph( Graph g );
void removeComponent( int idNode, Graph g, list<int>& notCheckedList );
bool checkConnectedGraph( Graph g, int& numComponents );
bool edgeIsBridge( vector<int> edge, Graph g );
vector<int> readEdgeIncMatrix( vector<int> incMatrixLine );
vector<int> pickEdgeFleury( int currentNode, Graph g, int& linMatIncident, bool& deleteNode );
bool checkEulerianGraph( Graph g );
void printEdge( vector<int> edge );

// função para separar uma string a cada ocorrencia de um delimitador
// ex: 1: 1 2 com delimitador ':' irá gerar uma lista com as strings '1' e '1 2'
list<string> explode( string s, char delim ){

	int          posDelim;
	string       value = "";
	list<string> result;

	while( !s.empty() ){

		posDelim = s.find( delim );
		value = s.substr( 0, posDelim );
		s.erase( 0, posDelim + 1 );

		if( !value.empty() ){
			result.push_back( value );
		}

		if( posDelim < 0 ){
			break;
		}

	}

	return result;

}


// função para separar uma string em valores de int a cada ocorrencia de um delimitador
// ex: 1 2 com delimitador ' ' irá gerar uma lista com os valores de int '1' e '2'
list<int> explodeInt( string s, char delim ){

	int       posDelim;
	string    value = "";
	list<int> result;

	while( !s.empty() ){

		posDelim = s.find( delim );
		value = s.substr( 0, posDelim );
		s.erase( 0, posDelim + 1 );

		if( !value.empty() ){
			result.push_back( stoi( value ) );
		}

		if( posDelim < 0 ){
			break;
		}

	}

	return result;

}

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


// le o arquivo grafo.txt e gera uma lista de Nodes
list<Node> readFile( string fileName ){

	string     line;
    list<Node> nodes;
    Node       node;
	ifstream   file( fileName );
	int        lineCount = 0;

	if( file.is_open() ){

    	while ( !file.eof() ){

	    	getline( file, line );

			if( !line.empty() ){

				node.setEdges( explodeTEG( line ) );
				node.setId( ++lineCount );

			}

			nodes.push_back( node );

	    }

	    file.close();

	}else{

		cout << "Nao foi possivel abrir o arquivo.";// função para ambientes com c++ de versão antiga

    }

    return nodes;

}

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
list<Node> readTEG( string fileName ){

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

//function for printing the elements in a list
void showList(list <int> g){

    list <int> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout << *it << " ";

}

// Função para printar matriz em tela
void printMatrix( vector<vector<int>> auxMatrix ){

	int i, j;

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

	int i;
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

	int i;
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

// Funcao para printar a edge
void printEdge( vector<int> edge ){

	cout << edge.front() << " --> " << edge.back() << endl;

}