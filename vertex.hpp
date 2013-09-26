#include "graph.h"

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I const &_id): id(_id), value(), rList(), tList()
{ }

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I const &_id, V const &_value): id(_id), value(_value), rList(), tList()
{ }

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I const &_id, V &&_value) noexcept: id(_id), rList(), tList()
{
    value = std::move(_value);
}

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I &&_id, V const &_value) noexcept: value(_value), rList(), tList()
{
    id = std::move(_id);
}

template <class I, class V, class E>
my::graph<I, V, E>::vertex::vertex(I &&_id, V &&_value) noexcept: rList(), tList()
{
    id = std::move(_id);
    value = std::move(_value);
}

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
