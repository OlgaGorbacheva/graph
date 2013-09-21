#include "graph.h"

template <class I, class V, class E>
my::vertex<I, V, E>::vertex(I &_id): id(_id), value(), rList(), tList()
{ }

template <class I, class V, class E>
my::vertex<I, V, E>::vertex(I &_id, V &_value): id(_id), value(_value), rList(), tList()
{ }

// move-семантика

template <class I, class V, class E>
I my::vertex<I, V, E>::getId()
{
    return id;
}

template <class I, class V, class E>
V my::vertex<I, V, E>::getValue()
{
    return value;
}
