#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include "graph.h"
#include "sets.h"
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <climits>

template<class I, class V, class E>
std::vector<std::vector<I> > Tarjan(my::graph<I, V, E> const &G);

template<class I, class V, class E>
my::graph<I, V, E> Prim(my::graph<I, V, E> const &G);

template<class I, class V, class E>
my::graph<I, V, E> Kruskal(my::graph<I, V, E> &G);

#include "Tarjan.hpp"
#include "Prim.hpp"
#include "Kruskal.hpp"

#endif // GRAPH_ALGORITHM_H
