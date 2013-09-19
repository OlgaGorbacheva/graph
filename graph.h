#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <memory>
#include <map>

//using namespace std;

template<class V, class E>
class graph;

template<class V, class E>
class vertex
{
private:
    V value;                                                           //значение вершины
    std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> > rList;  //прямой список смежности для вершины
    std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> > tList;  //обратный список смежности для вершины
public:

//    template<class T, class U>
    friend class graph<V, E>;

    vertex<V, E>(V _value): value(_value) {}
    vertex<V, E>(vertex<V, E> const &_v): value(_v.value), rList(_v.rList), tList(_v.tList) {}
    V get(){return value;}
    int getNum(){return rList.size();}
};

template<class V, class E>
class graph
{
private:
    std::map<int, std::shared_ptr<vertex<V, E> > > ver;  //список вершин с номерами, c которыми вводим/выводим

public:
    friend class vertex<V, E>;

    typedef typename std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> >::iterator edge_iterator;
    typedef typename std::map<int, std::shared_ptr<vertex<V, E> > >::iterator vertex_iterator;

    graph();

    graph<V, E> transpose();

    std::list<std::pair<int, E> > getInEdges(int v); //список входящих ребер
    std::list<std::pair<int, E> > getOutEdges(int v); //список выходящих ребер
    std::list<std::pair<int, V> > getAccessVertexes(int v); //список достижимых ребер
    std::list<std::pair<int, V> > getPreviousVertexes(int v); //список предыдущих вершин

    void insertVertex(int v, V _value);
    void eraseVertex(int v);
    void insertEdge(int v1, int v2, E _value);
    void eraseEdge(int v1, int v2);

    template <class T, class U>
    friend std::istream& operator >>(std::istream &cin, graph<T, U> &_graph);

    template <class T, class U>
    friend std::ostream& operator << (std::ostream &cout, graph<T, U> &_graph);

//    class iterator_dfs;
//    class iterator_bfs;

//    iterator_dfs begin_dfs();
//    iterator_dfs end_dfs();
//    iterator_bfs begin(int);
//    iterator_bfs end(int);
};

//template<class TypeV, class TypeE>
//class graph<TypeV, TypeE>::iterator_dfs
//{
//private:
//    vector<char> color;
//    typename vector<shared_ptr<vertex<TypeV> > >::iterator elem;
//    stack<int> passed;
//    shared_ptr<graph<TypeV, TypeE> > G;
//public:
//    iterator_dfs(graph<TypeV, TypeE> *_G);
//    iterator_dfs(iterator_dfs const &itr);

//    friend class graph;

//    iterator_dfs & operator ++();
//    shared_ptr<vertex<TypeV> >  & operator *();
//    bool operator ==(iterator_dfs const itr);
//    bool operator !=(iterator_dfs const itr);
//};

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
