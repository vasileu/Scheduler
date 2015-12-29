#ifndef GRAPH_H
#define GRAPH_H

#include "QVector"

class Edge
{
public:
    int source;
    int destination;
    int weight;
    bool operator> (const Edge &arg);
    bool operator< (const Edge &arg);
    bool operator== (const Edge &arg);
};

class Graph
{
    int vertexCount;
    int edgeCount;
    bool isDirectedGraph;
    QVector < QVector <int> > edges;
public:
    Graph(int vertexCount, bool isDirectedGraph = true);
    int VertexCount() const;
    int EdgeCount() const;
    bool IsDirected() const;
    void InsertEdge(Edge edge);
    void RemoveEdge(Edge edge);
    int EdgeWeight(int source, int destination);

    friend class EdgesIterator;
};

class EdgesIterator
{
    const Graph & G;
    int vertex;
    int i;
public:
    EdgesIterator(const Graph& G, int vertex);
    Edge begin();
    Edge nextItem();
    bool end();
};



#endif // GRAPH_H
