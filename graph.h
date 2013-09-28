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

    typedef typename std::unordered_map<I, std::shared_ptr<vertex> >::const_iterator direct_vertex_iterator;
    typedef typename std::map<std::pair<I, I>, std::shared_ptr<edge> >::const_iterator direct_edge_iterator;

private:    
    std::unordered_map<I, std::shared_ptr<vertex> > vertexes;
    std::map<std::pair<I, I>, std::shared_ptr<edge> > edges;    
    void swap(graph<I, V, E> &_G) noexcept;

public:

    graph();
    graph(graph<I, V, E> const &_G);
    graph(graph<I, V, E> &&_G) noexcept;

    ~graph();

    void operator =(graph<I, V, E> const &_G);
    void operator =(graph<I, V, E> &&_G);

    direct_vertex_iterator insertVertex(I const &id, V const &_value);
    direct_edge_iterator insertEdge(I const &id_1, I const &id_2, E const &_value);

    void eraseVertex(I const &id);
    void eraseEdge(I const &id_1, I const &id_2);

    void eraseVertex(direct_vertex_iterator const itr); //не понятно как проверять принадлежность вершины к контейнеру по итератору
    void eraseEdge(direct_edge_iterator const itr); //аналогично с предыдущим пунктом

    graph<I, V, E> transpose() const;

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

    direct_vertex_iterator ver_begin();
    direct_vertex_iterator ver_end();
    direct_edge_iterator ed_begin();
    direct_edge_iterator ed_end();

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

    I getId() const;
    V getValue() const;
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

    E getValue() const;
    std::pair<I, I> getVertexes() const;
    std::pair<std::weak_ptr<my::graph<I, V, E>::vertex>, std::weak_ptr<my::graph<I, V, E>::vertex> > getVertexPointers() const;
};

template<class I, class V, class E>
class my::graph<I, V, E>::iterator_dfs
{
private:
    std::unordered_map<I, int> color;
    std::stack<I> passed;
    my::graph<I, V, E>::direct_vertex_iterator elem;
    my::graph<I, V, E> &G;

    void swap(iterator_dfs &_itr) noexcept;

public:
    friend class graph;

    iterator_dfs(my::graph<I, V, E> &_G);
    iterator_dfs(my::graph<I, V, E>::iterator_dfs const &_itr);
    iterator_dfs(my::graph<I, V, E>::iterator_dfs &&_itr) noexcept;

    void operator =(my::graph<I, V, E>::iterator_dfs const &_itr);
    void operator =(my::graph<I, V, E>::iterator_dfs &&_itr);

    my::graph<I, V, E>::vertex & operator *();
    std::shared_ptr<my::graph<I, V, E>::vertex > operator ->(); //по необъяснимой причине не работает

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
    my::graph<I, V, E>::direct_vertex_iterator elem;
    my::graph<I, V, E> &G;

    void swap(iterator_bfs &_itr) noexcept;

public:
    friend class graph;

    iterator_bfs(my::graph<I, V, E> &_G);
    iterator_bfs(my::graph<I, V, E>::iterator_bfs const &_itr);
    iterator_bfs(my::graph<I, V, E>::iterator_bfs &&_itr) noexcept;

    void operator =(my::graph<I, V, E>::iterator_bfs const &_itr);
    void operator =(my::graph<I, V, E>::iterator_bfs &&_itr);

    my::graph<I, V, E>::vertex & operator *();
    my::graph<I, V, E>::vertex & operator ->();

    iterator_bfs & operator++();
    iterator_bfs operator ++(int);

    bool operator ==(iterator_bfs _itr);
    bool operator !=(iterator_bfs _itr);

    int getColor();
};
\
#include "graph.hpp"
#include "edge.hpp"
#include "vertex.hpp"

#include "iterator.hpp"
#endif // GRAPH_H
