#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include "graph.h"
#include <vector>

template<class I, class V, class E>
std::vector<std::vector<I> > Tarjan(my::graph<I, V, E> &G);

template<class I, class V, class E>
E Dijkstra(I _id);

#include "Tarjan.hpp"
#include "Dijkstra.hpp"

#endif // GRAPH_ALGORITHM_H
