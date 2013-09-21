#include "graph.h"

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I &_id): id(_id), value(), rList(), tList()
{ }

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I &_id, V &_value): id(_id), value(_value), rList(), tList()
{ }

// move-семантика

template <class I, class V, class E>
I my::graph<I, V, E>::vertex::getId()
{
    return id;
}

template <class I, class V, class E>
V my::graph<I, V, E>::vertex::getValue()
{
    return value;
}
