#include "graph.h"

Graph::Graph( int vertexCount, bool isDirectedGraph ) :
    vertexCount( vertexCount ),
    edgeCount( 0 ),
    isDirectedGraph( isDirectedGraph )
{
    edges.resize( vertexCount );
    for ( int i = 0; i < vertexCount; i++ )
    {
        edges[i].resize( vertexCount );
        edges[i].fill( -1 );
    }
}

int Graph::EdgeCount() const
{
    return edgeCount;
}

int Graph::VertexCount() const
{
    return vertexCount;
}

bool Graph::IsDirected() const
{
    return isDirectedGraph;
}

int Graph::EdgeWeight( int source, int destination )
{
    return edges[source][destination];
}

void Graph::InsertEdge( Edge edge )
{
    int i = edge.source;
    int j = edge.destination ;
    if ( edges[i][j] < 0 ){
        edgeCount++;
    }
    edges[i][j] = edge.weight;
    if ( !isDirectedGraph ){
        edges[j][i] = edge.weight;
    }
}

void Graph::RemoveEdge( Edge edge )
{
    int i = edge.source;
    int j = edge.destination;
    if ( edges[i][j] != -1 ){
        edgeCount--;
    }
    edges[i][j] = -1;
    if ( !isDirectedGraph ){
        edges[j][i] = -1;
    }
}

EdgesIterator::EdgesIterator(const Graph &G, int vertex) :
    G( G ),
    vertex( vertex ),
    i( -1 )
{

}

Edge EdgesIterator::begin()
{
    i = -1;
    return nextItem();
}

Edge EdgesIterator::nextItem()
{
    Edge result;
    for( i++; i < G.vertexCount; i++){
        if ( G.edges[vertex][i] >= 0){
            result.source = vertex;
            result.destination = i;
            result.weight = G.edges[vertex][i];
            return result;
        }
    }
    // возвращается некорректное ребро, но при этом функция end() == true
    return result;
}

bool EdgesIterator::end()
{
    return i >= G.vertexCount;
}


bool Edge::operator <(const Edge &arg){
    return (weight < arg.weight);
}
bool Edge::operator >(const Edge &arg){
    return (weight > arg.weight);
}
bool Edge::operator ==(const Edge &arg){
    return (weight == arg.weight);
}
