#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>
#include <map>
#include <utility>
#include <iostream>

namespace my{

template<class I, class V, class E>
class graph;

template<class I, class V, class E>
std::istream& operator >> (std::istream &cin, graph<I, V, E> &_graph);

template<class I, class V, class E>
std::ostream& operator <<(std::ostream &cout, graph<I, V, E> const &_graph);

}

template<class I, class V, class E>
class my::graph
{
public:
    class vertex;
    class edge;
private:
    std::unordered_map<I, std::shared_ptr<vertex> > vertexes;
    std::map<std::pair<I, I>, std::shared_ptr<edge> > edges;
public:

    typedef typename std::unordered_map<I, std::shared_ptr<vertex> >::const_iterator direct_vertex_iterator;
    typedef typename std::map<std::pair<I, I>, std::shared_ptr<edge> >::const_iterator direct_edge_iterator;

    graph();
    graph(graph<I, V, E> const &_G);
    graph(graph<I, V, E> &&_G) noexcept;

    ~graph();

    void swap(graph<I, V, E> &_G) noexcept;
    void operator =(graph<I, V, E> const &_G);
    void operator =(graph<I, V, E> &&_G);

    direct_vertex_iterator insertVertex(I const &id, V const &_value);
    direct_edge_iterator insertEdge(I const &id_1, I const &id_2, E const &_value);

    void eraseVertex(I const &id);
    void eraseEdge(I const &id_1, I const &id_2);

    void eraseVertex(direct_vertex_iterator const itr); //не понятно как проверять принадлежность вершины к контейнеру по итератору
    void eraseEdge(direct_edge_iterator const itr); //аналогично с предыдущим пунктом

    graph<I, V, E> transpose();

    std::vector<std::pair<I, E> > getOutEdges(I const &id) const;
    std::vector<std::pair<I, E> > getInEdges(I const &id) const;
    std::vector<std::pair<I, V> > getAccessVertexes(I const &id) const;
    std::vector<std::pair<I, V> > getPreviousVertexes(I const &id) const;
    std::vector<std::pair<I, V> > getVertexes() const;

    void clear();

    friend std::istream& operator >> <I, V, E> (std::istream &cin, graph<I, V, E> &_graph);

    friend std::ostream& operator << <I, V, E> (std::ostream &cout, graph<I, V, E> const &_graph);

    class iterator_dfs;
    class iterator_bfs;

    iterator_dfs begin_dfs();
    iterator_dfs end_dfs();
    iterator_bfs begin_bfs();
    iterator_bfs end_bfs();
};

template<class I, class V, class E>
class my::graph<I, V, E>::vertex
{
private:
    I id;
    V value;
    std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> > rList;
    std::unordered_map<I, std::weak_ptr<my::graph<I, V, E>::edge> > tList;
public:

    friend class graph;
    vertex(I const &_id);
    vertex(I const &_id, V const &_value);
    vertex(I const &_id, V &&_value) noexcept;
    vertex(I &&_id, V const &_value) noexcept;
    vertex(I &&_id, V &&_value) noexcept;
    vertex(my::graph<I, V, E>::vertex &_ver) = delete;
//    vertex(my::graph<I, V, E>::vertex &&_ver) noexcept;

    I getId();
    V getValue();
};

template<class I, class V, class E>
class my::graph<I, V, E>::edge
{
private:
    E value;
    std::pair<std::weak_ptr<my::graph<I, V, E>::vertex>, std::weak_ptr<my::graph<I, V, E>::vertex> > vertexes;
public:

    friend class graph;

    edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1, std::weak_ptr<my::graph<I, V, E>::vertex> v2);
    edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1, std::weak_ptr<my::graph<I, V, E>::vertex> v2, E const &_value);
    edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1, std::weak_ptr<my::graph<I, V, E>::vertex> v2, E &&_value);
    edge(edge const &e) = delete;

    E getValue();
    std::pair<I, I> getVertexes();
    std::pair<std::weak_ptr<my::graph<I, V, E>::vertex>, std::weak_ptr<my::graph<I, V, E>::vertex> > getVertexPointers();
};

template<class I, class V, class E>
class my::graph<I, V, E>::iterator_dfs
{
private:
    std::unordered_map<I, int> color;
    std::stack<I> passed;
    my::graph<I, V, E>::direct_vertex_iterator itr;
    my::graph<I, V, E> &G;
public:
    friend class graph;

    iterator_dfs(my::graph<I, V, E> &_G);
    iterator_dfs(my::graph<I, V, E>::iterator_dfs &_itr);
    iterator_dfs(my::graph<I, V, E>::iterator_dfs &&_itr) noexcept;

    my::graph<I, V, E>::vertex & operator *();
    my::graph<I, V, E>::vertex & operator ->();

    iterator_dfs & operator++();
    iterator_dfs operator ++(int);

    bool operator ==(iterator_dfs _itr);
    bool operator !=(iterator_dfs _itr);

    int getColor();
};

template<class I, class V, class E>
class my::graph<I, V, E>::iterator_bfs
{
private:
    std::unordered_map<I, int> color;
    std::queue<I> passed;
    my::graph<I, V, E>::direct_vertex_iterator itr;
    my::graph<I, V, E> &G;
public:
    friend class graph;

    iterator_bfs(my::graph<I, V, E> &_G);
    iterator_bfs(my::graph<I, V, E>::iterator_bfs &_itr);
    iterator_bfs(my::graph<I, V, E>::iterator_bfs &&_itr) noexcept;

    my::graph<I, V, E>::vertex & operator *();
    my::graph<I, V, E>::vertex & operator ->();

    iterator_bfs & operator++();
    iterator_bfs operator ++(int);

    bool operator ==(iterator_bfs _itr);
    bool operator !=(iterator_bfs _itr);

    int getColor();
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
#include "edge.hpp"
#include "vertex.hpp"

#include "iterator.hpp"
#endif // GRAPH_H
