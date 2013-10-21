#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include "graph.h"
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <climits>

template<class I, class V, class E>
std::vector<std::vector<I> > Tarjan(my::graph<I, V, E> const &G);

template<class I, class V, class E>
std::map<I, E> Dijkstra(my::graph<I, V, E> const &G, I const &_id);

#include "Tarjan.hpp"
#include "Dijkstra.hpp"

#endif // GRAPH_ALGORITHM_H
