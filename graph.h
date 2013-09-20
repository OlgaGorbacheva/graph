#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <unordered_map>
#include <vector>

namespace my {
template<class I, class V, class E>
class vertex;

template<class I, class V, class E>
class edge;

template<class I, class V, class E>
class graph;
}

//template<class I, class V, class E>
//class my::edge;

template<class I, class V, class E>
class my::vertex
{
private:
    I id;
    V value;
    std::unordered_map<int, std::weak_ptr<my::edge<I, V, E> > > rList;
    std::unordered_map<int, std::weak_ptr<my::edge<I, V, E> > > tList;
public:
    vertex(I &_id);
    vertex(I &_id, V &_value);
    vertex(I &_id, V &&_value);
    vertex(vertex<I, V, E> &_ver) = delete;
    vertex(vertex<I, V, E> &&_ver) noexcept;

    I getId();
    V getValue();
};

template<class I, class V, class E>
class my::edge
{
private:
    E value;
    std::pair<std::weak_ptr<my::vertex<I, V, E> >, std::weak_ptr<my::vertex<I, V, E> > > vertexes;
public:
    edge(std::weak_ptr<my::vertex<I, V, E> > v1, std::weak_ptr<my::vertex<I, V, E> > v2);
    edge(std::weak_ptr<my::vertex<I, V, E> > v1, std::weak_ptr<my::vertex<I, V, E> > v2, E _value);

    E getValue;
    std::pair<I, I> getVertexes();
    std::pair<std::weak_ptr<my::vertex<I, V, E> >, std::weak_ptr<my::vertex<I, V, E> > > getVertexPointers();
};

template<class I, class V, class E>
class my::graph
{
private:
    std::vector<std::shared_ptr<my::vertex<I, V, E> > > vertexes;
    std::vector<std::shared_ptr<my::vertex<I, V, E> > > edges;
public:
};

//#include <list>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//#include <stack>
//#include <queue>
//#include <memory>
//#include <map>
//#include <unordered_map>

//using namespace std;

//template<class V, class E>
//class graph;

//template<class V, class E>
//class vertex
//{
//private:
//    V value;                                                           //значение вершины
//    std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> > rList;  //прямой список смежности для вершины
//    std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> > tList;  //обратный список смежности для вершины
//public:

////    template<class T, class U>
//    friend class graph<V, E>;

//    vertex<V, E>(V _value): value(_value) {}
//    vertex<V, E>(vertex<V, E> const &_v): value(_v.value), rList(_v.rList), tList(_v.tList) {}
//    V get(){return value;}
//    int getNum(){return rList.size();}
//};

//template<class V, class E>
//class graph
//{
//private:
//    std::map<int, std::shared_ptr<vertex<V, E> > > ver;  //список вершин с номерами, c которыми вводим/выводим

//public:
//    friend class vertex<V, E>;

//    typedef typename std::map<int, std::pair<std::weak_ptr<vertex<V, E> >, E> >::iterator edge_iterator;
//    typedef typename std::map<int, std::shared_ptr<vertex<V, E> > >::iterator vertex_iterator;

//    graph();

//    graph<V, E> transpose();

//    std::list<std::pair<int, E> > getInEdges(int v); //список входящих ребер
//    std::list<std::pair<int, E> > getOutEdges(int v); //список выходящих ребер
//    std::list<std::pair<int, V> > getAccessVertexes(int v); //список достижимых вершин
//    std::list<std::pair<int, V> > getPreviousVertexes(int v); //список предыдущих вершин

//    void insertVertex(int v, V _value);
//    void eraseVertex(int v);
//    void insertEdge(int v1, int v2, E _value);
//    void eraseEdge(int v1, int v2);

//    template <class T, class U>
//    friend std::istream& operator >>(std::istream &cin, graph<T, U> &_graph);

//    template <class T, class U>
//    friend std::ostream& operator << (std::ostream &cout, graph<T, U> &_graph);

////    class iterator_dfs;
////    class iterator_bfs;

////    iterator_dfs begin_dfs();
////    iterator_dfs end_dfs();
////    iterator_bfs begin(int);
////    iterator_bfs end(int);
//};

//template<class V, class E>
//class graph<V, E>::iterator_dfs
//{
//private:
//    std::unordered_map<int, char> color;
//    graph<V, E>::vertex_iterator elem;
//    std::stack<int> passed;
//    graph<V, E> &G;
//public:
//    iterator_dfs(graph<V, E> &_G);
//    iterator_dfs(iterator_dfs const &itr);

//    friend class graph;

//    iterator_dfs & operator ++();
////    shared_ptr<vertex<TypeV> >  & operator *();
////    bool operator ==(iterator_dfs const itr);
////    bool operator !=(iterator_dfs const itr);
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
