#include <bits/stdc++.h>

// Para compilar todos os programas:
// g++ -std=c++11 libghelli.h Ex1/main.cpp Ex3/main.cpp Ex4/main.cpp Ex5/main.cpp Ex9/main.cpp Ex11/main.cpp -Wall

// Classes

using namespace std;

class Node
{

	public:

	int       id;
	list<int> edges;
	list<int> edgeWeight;
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
	vector<vector<int>> weightMatrix;
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

	bool isWeighted(){

		for( auto itNode:nodes ){

			if( !itNode.edgeWeight.empty() )
				return true;

		}

		return false;

	}

	// Função para gerar a matriz adjacencia do grafo
	void calcAdjacentMatrix(){

		unsigned int i;
		list<Node> :: iterator itNode;
		list<int>  :: iterator itEdge;
		list<int>  :: iterator itEdgeWeight;

		adjacentMatrix = resizeMatrix( numNodes, numNodes );

		if( !this->isWeighted() ){


			for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){
				for( itEdge = itNode->edges.begin(); itEdge != itNode->edges.end(); itEdge++ ){

					adjacentMatrix[ itNode->id - 1 ][ *itEdge - 1 ]++;

					if( !directed )
						adjacentMatrix[ *itEdge - 1 ][ itNode->id - 1 ]++;

				}
			}

		}else{

			weightMatrix = resizeMatrix( numNodes, numNodes );

			for( itNode = nodes.begin(); itNode != nodes.end(); itNode++ ){

				itEdge = itNode->edges.begin();
				itEdgeWeight = itNode->edgeWeight.begin();

				for( i = 0; i < itNode->edges.size(); i++ ){

					adjacentMatrix[ itNode->id - 1 ][ *itEdge - 1 ]++;

					if( ( weightMatrix[ itNode->id - 1 ][ *itEdge - 1 ] > *itEdgeWeight ) || ( weightMatrix[ itNode->id - 1 ][ *itEdge - 1 ] == 0 ) )
						weightMatrix[ itNode->id - 1 ][ *itEdge - 1 ] = *itEdgeWeight;

					if( !directed ){

						adjacentMatrix[ *itEdge - 1 ][ itNode->id - 1 ]++;

						if( ( weightMatrix[ *itEdge - 1 ][ itNode->id - 1 ] > *itEdgeWeight )  || ( weightMatrix[ *itEdge - 1 ][ itNode->id - 1 ] == 0 ) )
							weightMatrix[ *itEdge - 1 ][ itNode->id - 1 ] = *itEdgeWeight;

					}

					itEdge++;
					itEdgeWeight++;

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

list<Node> readGraph( string fileName );
void showVector(vector <int> g);
void printGraph( Graph g );
void printGraphInfo( Graph g );
void printWGraphInfo( Graph g );
bool check2PartGraph( Graph g );
bool checkConnectedGraph( Graph g, int& numComponents );
bool checkEulerianGraph( Graph g );
vector<int> graphDFS( Graph g, int startNode, vector<int>& pe, vector<int>& ps );
vector<int> graphBFS( Graph g, int startNode, vector<int>& l, vector<int>& father, vector<int>& level, vector<int>& brother, vector<int>& cousin, vector<int>& uncle );
void printWeightedGraph( Graph g );
list<Node> readWeightedGraph( string fileName );
vector<vector<int>> dijkstraCalc( Graph g, int idNode );
void printDij( vector<vector<int>> matrixDij );
list<int> findPathBetween( Graph g, int idNodeOri, int idNodeDes );