#include <bits/stdc++.h>

// Classes

using namespace std;

class Node
{

	public:

	int  id;
	list<int> edges;

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

	Graph( list<Node> ns, bool d ){

		setNodes( ns );
		setDirected( d );

		calcAdjacentMatrix();
		calcIncidentMatrix();

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



	}

};


// Functions

list<string> explode( string s, char delim );
list<int> explodeInt( string s, char delim );
list<int> explodeGasp( string s );
list<Node> readFile( string fileName );
list<Node> readGasp();
void showNodes( list <Node> g );
void printMatrix(  vector<vector<int>> auxMatrix  );
void printGraph( Graph g );

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


list<int> explodeGasp( string s ){

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

				node.setEdges( explodeGasp( line ) );
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
list<Node> readGasp( string fileName ){

	string     line;
    list<Node> nodes;
    Node       node;
	int        lineCount = 1;
	ifstream   file( fileName );
	istream&   s = file;

	while( getline( s, line ) ){

	    node.setEdges( explodeGasp( line ) );
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
