#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <memory>

using namespace std;
////////
template<class T>
class vertex
{
    T value;
};

template<class TypeV, class TypeE>
class graph
{
private:
    vector<shared_ptr<vertex<TypeV> > > ver;
    vector<list<pair<weak_ptr<vertex<TypeV> >, TypeE> > > rList;
    vector<list<pair<weak_ptr<vertex<TypeV> >, TypeE> > > tList;
public:
    typedef typename vector<list<pair<weak_ptr<vertex<TypeV> >, TypeE> > >::iterator edges_iterator;
    typedef typename list<pair<weak_ptr<vertex<TypeV> >, TypeE> >::iterator vertex_iterator;

    graph();

    graph<TypeV, TypeE> transpose();
    list<pair<weak_ptr<vertex<TypeV> >, TypeE> > getInEdges(shared_ptr<vertex<TypeV> > v); //список входящих ребер:
                                                                                          //указатель на вершину, вес ребра
    list<pair<weak_ptr<vertex<TypeV> >, TypeE> > getOutEdges(shared_ptr<vertex<TypeV> > v); //список выходящих ребер
//    vector<DataV> getVertex();
//    void InsertV(DataV _data);
//    void InsertE(unsigned int v1, unsigned int v2, DataE _data);

//    class iterator_dfs;
//    class iterator_bfs;

//    template <class T, class U>
//    friend istream& operator >> (istream &cin, graph<T, U>& _graph);

//    template <class T, class U>
//    friend ostream& operator << (ostream &cout, graph<T, U>& _graph);

//    iterator_dfs begin();
//    iterator_dfs end();
//    iterator_bfs begin(int);
//    iterator_bfs end(int);
//};

//template<class DataV, class DataE>
//class graph<DataV, DataE>::iterator_dfs
//{
//private:
//    vector<char> color;
//    typename vector<DataV>::iterator elem;
//    stack<int> passed;
//    graph *G;
//public:
//    iterator_dfs(graph<DataV, DataE> *_G);
//    iterator_dfs(iterator_dfs const &itr);

//    friend class graph;

//    iterator_dfs& operator ++();
//    DataV& operator *();
//    bool operator ==(iterator_dfs const itr);
//    bool operator !=(iterator_dfs const itr);
};

//template<class DataV, class DataE>
//class graph<DataV, DataE>::iterator_bfs
//{
//private:
//    vector<char> color;
//    typename vector<DataV>::iterator elem;
//    queue<int> passed;
//    graph *G;
//public:
//    iterator_bfs(graph<DataV, DataE> *_G);
//    iterator_bfs(iterator_bfs const &itr);

//    friend class graph;

//    iterator_bfs& operator ++();
//    DataV& operator *();
//    bool operator ==(iterator_bfs const itr);
//    bool operator !=(iterator_bfs const itr);
//};

#include "graph.hpp"
#include "iterator.hpp"
#endif // GRAPH_H
