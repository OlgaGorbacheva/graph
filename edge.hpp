#include "graph.h"

template<class I, class V, class E>
my::graph<I, V, E>::edge::edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1,
                                        std::weak_ptr<my::graph<I, V, E>::vertex> v2):
    value(), vertexes(make_pair(v1, v2))
{ }

template<class I, class V, class E>
my::graph<I, V, E>::edge::edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1,
                               std::weak_ptr<my::graph<I, V, E>::vertex> v2, E const &_value):
    value(_value), vertexes(make_pair(v1, v2))
{ }

template<class I, class V, class E>
my::graph<I, V, E>::edge::edge(std::weak_ptr<my::graph<I, V, E>::vertex> v1,
                               std::weak_ptr<my::graph<I, V, E>::vertex> v2, E &&_value):
    vertexes(make_pair(v1, v2))
{
    std::swap(value, _value);
}


template<class I, class V, class E>
E my::graph<I, V, E>::edge::getValue() const
{
    return value;
}

template<class I, class V, class E>
std::pair<I, I> my::graph<I, V, E>::edge::getVertexes() const
{
    if (!vertexes.first.expired() && !vertexes.second.expired())
        return std::make_pair(vertexes.first.lock()->getId(), vertexes.second.lock()->getId());
    throw "Vertex doesn't exist";
}

template<class I, class V, class E>
std::pair<std::weak_ptr<typename my::graph<I, V, E>::vertex>, std::weak_ptr<typename my::graph<I, V, E>::vertex> >
            my::graph<I, V, E>::edge::getVertexPointers() const
{
    if (!vertexes.first.expired() && !vertexes.second.expired())
        return vertexes;
    throw "Vertex doesn't exist";
}
