#include "graph.h"

template<class I, class V, class E>
my::edge<I, V, E>::edge(std::weak_ptr<my::vertex<I, V, E> > v1, std::weak_ptr<my::vertex<I, V, E> > v2):
    value(), vertexes(make_pair(v1, v2))
{ }

template<class I, class V, class E>
my::edge<I, V, E>::edge(std::weak_ptr<my::vertex<I, V, E> > v1, std::weak_ptr<my::vertex<I, V, E> > v2, E _value):
    value(_value), vertexes(make_pair(v1, v2))
{ }

template<class I, class V, class E>
E my::edge<I, V, E>::getValue()
{
    return value;
}

template<class I, class V, class E>
std::pair<I, I> my::edge<I, V, E>::getVertexes()
{
    if (!vertexes.first.expired() && !vertexes.second.expired())
        return std::make_pair(vertexes.first.lock()->getId(), vertexes.second.lock()->getId());
    throw "Vertex doesn't exist";
}

template<class I, class V, class E>
std::pair<std::weak_ptr<my::vertex<I, V, E> >, std::weak_ptr<my::vertex<I, V, E> > > my::edge<I, V, E>::getVertexPointers()
{
    if (!vertexes.first.expired() && !vertexes.second.expired())
        return vertexes;
    throw "Vertex doesn't exist";
}
